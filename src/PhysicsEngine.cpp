#include "PhysicsEngine.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <unordered_map>

PhysicsEngine::PhysicsEngine(Util::Renderer* root,
                             std::shared_ptr<ScoreManager> scoreManager,
                             bool cheat)
    : m_Root(root),
      m_ScoreManager(std::move(scoreManager)),
      m_isCheatMode(cheat),
      m_isFastForward(false),
      m_isLastBirdReleased(false),
      m_Flying(nullptr),
      m_ObjectFactory(nullptr),
      m_WorldId(),
      m_LastBirdReleaseTime()
{
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{0.0f, -9.0f};
    m_WorldId = b2CreateWorld(&worldDef);
    b2World_SetHitEventThreshold(m_WorldId, 0.5f);
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = b2Vec2{4.5f, -1.0f};
    const b2BodyId groundId = b2CreateBody(m_WorldId, &groundBodyDef);
    const b2Polygon groundBox = b2MakeBox(6.4f, 1.0f);
    const b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);
    // Create right wall body
    b2BodyDef rightWallBodyDef = b2DefaultBodyDef();
    rightWallBodyDef.position = b2Vec2{12.0f, 3.5f};
    const b2BodyId rightWallId = b2CreateBody(m_WorldId, &rightWallBodyDef);
    const b2Polygon rightWallBox = b2MakeBox(1.0f, 3.5f);
    const b2ShapeDef rightWallShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(rightWallId, &rightWallShapeDef, &rightWallBox);
    m_ObjectFactory = std::make_shared<ObjectFactory>(m_WorldId);
}

void PhysicsEngine::CreateBird(const BirdType birdType) {
    if (m_isCheatMode && m_Birds.empty()) {
        const auto obj = m_ObjectFactory->CreateBird(BLACK, BIRD_POSITION_0);
        obj->SetPosition(B2Pos2GamePos(BIRD_POSITION_0));
        m_Root->AddChild(obj);
        m_Objects.push_back(obj);
        m_Birds.push(obj);
    }
    const float offset = static_cast<float>(m_Birds.size()) * -0.4f;
    const glm::vec2 position = m_Birds.empty() ? BIRD_POSITION_0 : glm::vec2{offset, 0.2f};
    const auto obj = m_ObjectFactory->CreateBird(birdType, position);
    if (!obj) {
        LOG_ERROR("Failed to create bird");
        return;
    }
    m_Birds.push(obj);
    m_Root->AddChild(obj);
    m_Objects.push_back(obj); // order of push_back matters
}

void PhysicsEngine::CreatePig(const glm::vec2 &position, const PigType pigType) {
    const auto obj = m_ObjectFactory->CreatePig(pigType, position);
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
    const b2BodyId bodyId = m_Birds.front()->GetBodyId();
    const auto b2Pos = GamePos2B2Pos(pos);
    const auto transform = b2Vec2{b2Pos.x, b2Pos.y};

    const b2Rot rot = b2MakeRot(0);
    FindObjectByBodyId(bodyId)->SetPosition({pos.x, pos.y});
    b2Body_SetTransform(bodyId, transform, rot);
}

void PhysicsEngine::Release(const glm::vec2 &posBias) {
    if (m_Birds.empty()) {
        return;
    }
    if (posBias.x > 0) {
        m_Birds.front()->SetPosition(B2Pos2GamePos(BIRD_POSITION_0));
        return;
    }
    b2BodyId bodyId;
    if (m_isCheatMode) {
        const auto obj = m_ObjectFactory->CreateBird(BLACK, BIRD_POSITION_0);
        bodyId = obj->GetBodyId();
        m_Flying = obj;
        m_Objects.push_back(obj);
        m_Root->AddChild(obj);
        m_Birds.front()->SetPosition(B2Pos2GamePos(BIRD_POSITION_0));
    } else {
        bodyId = m_Birds.front()->GetBodyId();
        m_Flying = m_Birds.front();
        m_Birds.pop();
        if (m_Birds.empty()) {
            m_isLastBirdReleased = true;
            m_LastBirdReleaseTime = std::chrono::steady_clock::now();
        }
    }
    const b2Vec2 force = b2Vec2{-posBias.x * 0.01f, -posBias.y * 0.01f} * 12.f;
    b2Body_Enable(bodyId);
    ApplyForce(bodyId, force);
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


GameState PhysicsEngine::GetGameState() const {
    if (m_Pigs.empty()) {
        return WON;
    }
    if (m_isLastBirdReleased) {
        const auto now = std::chrono::steady_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - m_LastBirdReleaseTime);
        if (duration.count() >= 5) {
            return LOST;
        }
    }
    return ONGOING;
}

bool PhysicsEngine::SetCheatMode(const bool enable) {
    m_isCheatMode = enable;
    if (m_Birds.empty()) {
        m_isCheatMode = false;
    }
    if (m_isCheatMode) {
        const auto obj = m_ObjectFactory->CreateBird(BLACK, BIRD_POSITION_0);
        obj->SetPosition(B2Pos2GamePos(BIRD_POSITION_0));
        m_Root->AddChild(obj);
        m_Objects.push_back(obj);
        m_Root->RemoveChild(m_Birds.front());
        m_Birds.front() = obj;
    }
    return m_isCheatMode;
}

//Set up the window with initial positions and rotations of objects in the physics world
void PhysicsEngine::SetUpWorld() const {
    for (const auto &obj: m_Objects) {
        const b2BodyId bodyId = obj->GetBodyId();
        auto [x, y] = b2Body_GetPosition(bodyId);
        const b2Rot rotation = b2Body_GetRotation(bodyId);

        obj->SetPosition(B2Pos2GamePos({x, y}));
        obj->SetRotation(b2Rot_GetAngle(rotation));
    }
}


void PhysicsEngine::UpdateWorld() {
    float timeStep = 1.0f / 60.0f;
    constexpr int subStepCount = 4;
    if (m_isFastForward) {
        timeStep *= 4.0f;
    }

    b2World_Step(m_WorldId, timeStep, subStepCount);

    ProcessEvents();
}


void PhysicsEngine::DestroyWorld() const {
    for (const auto &obj: m_Objects) {
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
        if (!b2Shape_IsValid(hitEvent.shapeIdA) || !b2Shape_IsValid(hitEvent.shapeIdB)) {
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
    auto contact = contactEvents.beginEvents;
    for (int i = 0; i < contactEvents.beginCount; ++i, ++contact) {
        if (!b2Shape_IsValid(contact->shapeIdA) || !b2Shape_IsValid(contact->shapeIdB)) {
            continue;
        }
        const b2BodyId bodyA = b2Shape_GetBody(contact->shapeIdA);
        const b2BodyId bodyB = b2Shape_GetBody(contact->shapeIdB);
        if (B2_IS_NULL(bodyA) || B2_IS_NULL(bodyB)) {
            continue;
        }
        auto objA = FindObjectByBodyId(bodyA);
        auto objB = FindObjectByBodyId(bodyB);
        if (!objA || !objB) {
            continue;
        }
        const auto entityA = objA->GetEntityType();
        const auto entityB = objB->GetEntityType();
        if ((entityA == BIRD && entityB == PIG) || (entityA == PIG && entityB == BIRD)) {
            HitObject(objA, 100.f);
            HitObject(objB, 100.f);
        }
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
        obj->ApplyDamage(static_cast<int>(20 * speed));
        if (obj->GetHealth() <= 0) {
            if (obj->GetEntityType() == PIG) {
                m_ScoreManager->AddScore(5000); // Pig score
            } else {
                m_ScoreManager->AddScore(500); // Structure score
            }
            for (const auto &score: m_ScoreManager->GetScoresObject()) {
                m_Root->RemoveChild(score);
            }
            m_ScoreManager->UpdateScore();
            m_Root->AddChildren(m_ScoreManager->GetScoresObject());
            DeleteObject(obj->GetBodyId());
        }
    } else {
        if (obj == m_Flying) m_Flying = nullptr;
    }
}

glm::vec2 PhysicsEngine::B2Pos2GamePos(const glm::vec2 &pos) {
    return {pos.x * 100.0f + X_OFFSET, pos.y * 100.0f + Y_OFFSET};
}

glm::vec2 PhysicsEngine::GamePos2B2Pos(const glm::vec2 &pos) {
    return {(pos.x - X_OFFSET) * 0.01f, (pos.y - Y_OFFSET) * 0.01f};
}

void PhysicsEngine::DeleteObject(const b2BodyId bodyId) {
    const auto obj = FindObjectByBodyId(bodyId);
    if (obj->GetEntityType() == PIG) {
        m_Pigs.erase(std::remove(m_Pigs.begin(), m_Pigs.end(), obj),
                     m_Pigs.end());
    }
    m_Root->RemoveChild(obj);
    b2DestroyBody(bodyId);
}
