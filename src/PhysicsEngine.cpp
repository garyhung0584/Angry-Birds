#include "PhysicsEngine.hpp"

#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include <unordered_map>

#include "Util/Animation.hpp"

PhysicsEngine::PhysicsEngine(Util::Renderer *Root,
                             std::shared_ptr<ScoreManager> scoreManager) {
    m_Root = Root;

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{0.0f, -9.0f};
    m_WorldId = b2CreateWorld(&worldDef);
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = b2Vec2{4.5f, -1.0f};
    b2BodyId groundId = b2CreateBody(m_WorldId, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(6.4f, 1.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    m_ObjectFactory = std::make_shared<ObjectFactory>(m_WorldId);
    m_ScoreManager = scoreManager;
}

void PhysicsEngine::CreateBird(const BirdType birdType) {
    glm::vec2 position = m_Birds.empty() ? glm::vec2{0.f, 1.3f} : glm::vec2{m_Birds.size() * -0.4f, 0.2f};
    auto obj = m_ObjectFactory->CreateBird(birdType, position);
    if (!obj) {
        LOG_ERROR("Failed to create bird");
        return;
    }
    m_Objects.push_back(obj);
    m_Root->AddChild(obj);
    m_Birds.push(obj);
}

void PhysicsEngine::CreatePig(const glm::vec2 &position, const PigType pigType) {
    auto obj = m_ObjectFactory->CreatePig(pigType, position);
    if (!obj) {
        LOG_ERROR("Failed to create pig");
        return;
    }
    m_Objects.push_back(obj);
    m_Root->AddChild(obj);
    m_Pigs.push_back(obj);
}

void PhysicsEngine::CreateStructure(const glm::vec2 &position, const EntityType entityType,
                                    const StructureType structureType, const float rotation) {
    const auto obj = m_ObjectFactory->CreateStructure(entityType, structureType, position, rotation);
    m_Objects.push_back(obj);
    m_Root->AddChild(obj);
}

void PhysicsEngine::Pull(const glm::vec2 &pos) {
    if (m_Birds.empty()) {
        return;
    }
    b2BodyId bodyId = m_Birds.front()->GetBodyId();
    auto transform = b2Vec2{(pos.x - X_OFFSET) * 0.01f, (pos.y - Y_OFFSET) * 0.01f};

    b2Rot rot = b2MakeRot(0);
    FindObjectByBodyId(bodyId)->SetPosition({pos.x, pos.y});
    b2Body_SetTransform(bodyId, transform, rot);
}

void PhysicsEngine::Release(glm::vec2 &posBias) {
    if (m_Birds.empty() ||posBias.x > 0) {
        return;
    }
    b2BodyId bodyId = m_Birds.front()->GetBodyId();
    b2Vec2 force = b2Vec2{-posBias.x * 0.01f, -posBias.y * 0.01f} * 12.f;
    b2Body_Enable(bodyId);
    ApplyForce(bodyId, force);
    m_Flying = m_Birds.front();
    m_Birds.pop();
}

void PhysicsEngine::UseAbility() {
    if (m_Flying) {
        m_Flying->Ability();
        m_Flying = nullptr;
    }
}

bool PhysicsEngine::IsFlying() const {
    if (m_Flying) {
        return true;
    }
    return false;
}


bool PhysicsEngine::IsEnd() {
    if (m_Pigs.empty()) {
        return true;
    }
    if (m_Birds.empty()) {
        return true;
    }
    return false;
}

//Set up the window with initial positions and rotations of objects in physics world
void PhysicsEngine::SetUpWorld() const {
    for (const auto &obj: m_Objects) {
        const b2BodyId bodyId = obj->GetBodyId();
        auto [x, y] = b2Body_GetPosition(bodyId);
        const b2Rot rotation = b2Body_GetRotation(bodyId);

        obj->SetPosition({x * 100 + X_OFFSET, y * 100 + Y_OFFSET});
        obj->SetRotation(b2Rot_GetAngle(rotation));
    }
}


void PhysicsEngine::UpdateWorld() {
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    b2World_Step(m_WorldId, timeStep, subStepCount);

    ProcessEvents();
}


void PhysicsEngine::DestroyWorld() const {
    for (auto obj: m_Objects) {
        m_Root->RemoveChild(obj);
    }
    b2DestroyWorld(m_WorldId);
}

std::shared_ptr<Physics2D> PhysicsEngine::FindObjectByBodyId(const b2BodyId bodyId) const {
    for (auto obj: m_Objects) {
        if (B2_ID_EQUALS(obj->GetBodyId(), bodyId)) {
            return obj;
        }
    }
    return nullptr;
}

void PhysicsEngine::ProcessEvents() {
    const b2ContactEvents contactEvents = b2World_GetContactEvents(m_WorldId);
    for (int i = 0; i < contactEvents.hitCount; ++i) {
        const b2ContactHitEvent &hitEvent = contactEvents.hitEvents[i];
        const auto speed = hitEvent.approachSpeed;
        if (b2Shape_IsValid(hitEvent.shapeIdA) == false or b2Shape_IsValid(hitEvent.shapeIdB) == false) {
            LOG_ERROR("Not valid shape id");
            continue;
        }
        const b2BodyId bodyA = b2Shape_GetBody(hitEvent.shapeIdA);
        const b2BodyId bodyB = b2Shape_GetBody(hitEvent.shapeIdB);
        auto objA = FindObjectByBodyId(bodyA);
        auto objB = FindObjectByBodyId(bodyB);

        if (objA && objB) {
            HitObject(objA, speed);
            HitObject(objB, speed);
        }
    }

    auto [moveEvents, moveCount] = b2World_GetBodyEvents(m_WorldId);
    for (int i = 0; i < moveCount; ++i) {
        const b2BodyMoveEvent &bodyEvent = moveEvents[i];
        const b2BodyId bodyId = bodyEvent.bodyId;
        const auto [x, y] = bodyEvent.transform.p;
        const auto rotation = bodyEvent.transform.q;
        const auto obj = FindObjectByBodyId(bodyId);

        obj->SetPosition({x * 100 + X_OFFSET, y * 100 + Y_OFFSET});
        obj->SetRotation(b2Rot_GetAngle(rotation));
    }
}

void PhysicsEngine::ApplyForce(const b2BodyId &bodyId, const b2Vec2 &force) const {
    if (B2_IS_NULL(m_WorldId) || B2_IS_NULL(bodyId)) {
        LOG_ERROR("World or body is null");
        return;
    }
    b2Body_SetLinearVelocity(bodyId, force);
}

void PhysicsEngine::HitObject(std::shared_ptr<Physics2D> &obj, float speed) {
    if (obj->GetEntityType() != BIRD) {
        obj->ApplyDamage(20 * speed);
        if (obj->GetHealth() <= 0) {
            if (obj->GetEntityType() == PIG) {
                m_ScoreManager->AddScore(5000); // Pig score
            } else {
                m_ScoreManager->AddScore(500); // Structure score
            }
            // for (const auto &score: m_ScoreManager->GetScoresObject()) {
            //     m_Root->RemoveChild(score);
            // }
            m_ScoreManager->UpdateScore();
            m_Root->AddChildren(m_ScoreManager->GetScoresObject());
            DeleteObject(obj->GetBodyId());
        }
    } else {
        m_Flying = nullptr;
    }
}

void PhysicsEngine::DeleteObject(const b2BodyId bodyId) {
    auto obj = FindObjectByBodyId(bodyId);
    if (obj->GetEntityType() == PIG) {
        m_Pigs.erase(std::remove(m_Pigs.begin(), m_Pigs.end(), obj),
                     m_Pigs.end());
    }
    m_Root->RemoveChild(obj);
    b2DestroyBody(bodyId);
}
