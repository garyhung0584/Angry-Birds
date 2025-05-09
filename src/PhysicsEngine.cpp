#include "PhysicsEngine.hpp"

#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include <unordered_map>

PhysicsEngine::PhysicsEngine(Util::Renderer *Root) {
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
}
void PhysicsEngine::CreateBird(const BirdType birdType) {
    static const std::unordered_map<BirdType, std::pair<std::string, glm::vec2>> birdProperties = {
        {RED, {"Red", {0.2f, 0.2f}}},
        {BLUE, {"Blue", {0.2f, 0.2f}}},
        {YELLOW, {"Yellow", {0.2f, 0.2f}}},
        {BLACK, {"Black", {0.2f, 0.2f}}},
        {WHITE, {"White", {0.2f, 0.2f}}},
        {BIG, {"Big", {0.2f, 0.2f}}}
    };

    auto it = birdProperties.find(birdType);
    if (it == birdProperties.end()) {
        LOG_ERROR("Invalid bird type");
        return;
    }

    const auto &[birdName, size] = it->second;
    glm::vec2 position = m_Birds.empty() ? glm::vec2{0.f, 1.3f} : glm::vec2{m_Birds.size() * -0.4f, 0.2f};
    const std::string imagePath = RESOURCE_DIR"/Birds/" + birdName + "Bird.png";
    m_Birds.push(CreateObject(imagePath, position, 1, BIRD, size, 0.2f, 0, 0.1f, 0.3f, false));
}

void PhysicsEngine::CreatePig(const glm::vec2 &position, const PigType pigType) {
    static const std::unordered_map<PigType, std::tuple<std::string, int, glm::vec2>> pigProperties = {
        {NORMAL, {"Normal", 100, {0.18f, 0.18f}}},
        {KING, {"King", 1000, {0.3f, 0.3f}}},
        {SOLDIER, {"Soldier", 500, {0.2f, 0.2f}}}
    };

    auto it = pigProperties.find(pigType);
    if (it == pigProperties.end()) {
        LOG_ERROR("Pig type not recognized");
        return;
    }

    const auto &[pigName, health, size] = it->second;
    const std::string imagePath = RESOURCE_DIR"/Pigs/Pig" + pigName + ".png";
    m_Pigs.push_back(CreateObject(imagePath, position, health, PIG, size, 0.05f, 0, 0.1f, 0.3f, true));
}

void PhysicsEngine::CreateStructure(const glm::vec2 &position, const EntityType entityType,
                                    const StructureType structureType, const float rotation) {
    static const std::unordered_map<EntityType, std::tuple<std::string, int, float, float>> entityProperties = {
        {WOOD, {"Wood", 100, 0.1f, 1.0f}},
        {STONE, {"Stone", 130, 0.2f, 0.3f}},
        {GLASS, {"Glass", 50, 0.2f, 0.1f}}
    };

    static const std::unordered_map<StructureType, std::pair<std::string, glm::vec2>> structureProperties = {
        {FRAME_BLOCK, {"A1", {0.4f, 0.4f}}},
        {FRAME_TRIANGLE, {"B1", {0.2f, 0.2f}}},
        {TRIANGLE, {"C1", {0.2f, 0.2f}}},
        {DISC, {"D1", {0.2f, 0.2f}}},
        {RECTANGLE, {"E1", {0.4f, 0.2f}}},
        {BLOCK, {"F1", {0.2f, 0.2f}}},
        {BAR_LONG, {"G1", {0.9f, 0.1f}}},
        {RECTANGLE_SMALL, {"H1", {0.2f, 0.1f}}},
        {BAR, {"I1", {0.8f, 0.1f}}},
        {BLOCK_SMALL, {"J1", {0.1f, 0.1f}}},
        {BAR_SHORT, {"K1", {0.4f, 0.1f}}},
        {DISC_SMALL, {"L1", {0.2f, 0.2f}}}
    };

    auto entityIt = entityProperties.find(entityType);
    auto structureIt = structureProperties.find(structureType);

    if (entityIt == entityProperties.end()) {
        LOG_ERROR("Entity type not recognized");
        return;
    }
    if (structureIt == structureProperties.end()) {
        LOG_ERROR("Structure type not recognized");
        return;
    }

    const auto &[material, health, density, friction] = entityIt->second;
    const auto &[shape, size] = structureIt->second;

    std::string imagePath = RESOURCE_DIR"/" + material + "/" + material + "_" + shape + ".png";
    CreateObject(imagePath, position, health, entityType, size, 1.f, rotation, density, friction, false);
}

void PhysicsEngine::Pull(const glm::vec2 &pos, float angle) {
    if (m_Birds.empty()) {
        return;
    }
    b2BodyId bodyId = m_Birds.front()->GetBodyId();
    auto transform = b2Vec2{(pos.x - X_OFFSET) * 0.01f, (pos.y - Y_OFFSET) * 0.01f};

    b2Rot rot = b2MakeRot(angle);
    FindObjectByBodyId(bodyId)->SetPosition({pos.x, pos.y});
    FindObjectByBodyId(bodyId)->SetRotation(angle);
    b2Body_SetTransform(bodyId, transform, rot);
}

void PhysicsEngine::Release(glm::vec2 &posBias) {
    if (posBias.x > 0 || m_Birds.empty()) {
        return;
    }
    b2BodyId bodyId = m_Birds.front()->GetBodyId();
    b2Vec2 force = b2Vec2{-posBias.x * 0.01f, -posBias.y * 0.01f} * 9.f;
    b2Body_Enable(bodyId);
    ApplyForce(bodyId, force);
    m_Birds.pop();
}

bool PhysicsEngine::IsEnd() {
    if (m_Pigs.empty()) {
        return true;
    } else if (m_Birds.empty()) {
        return true;
    }
    return false;
}


void PhysicsEngine::SetUpWorld() {
    for (const auto &obj: m_Objects) {
        b2BodyId bodyId = obj->GetBodyId();
        b2Vec2 position = b2Body_GetPosition(bodyId);
        b2Rot rotation = b2Body_GetRotation(bodyId);

        obj->SetPosition({position.x * 100 + X_OFFSET, position.y * 100 + Y_OFFSET});
        obj->SetRotation(b2Rot_GetAngle(rotation));
    }
}

void PhysicsEngine::UpdateWorld() {
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    b2World_Step(m_WorldId, timeStep, subStepCount);

    // auto fut = std::async([this]() {
    //     return this->ProcessEvents();
    // });
    ProcessEvents();
}


void PhysicsEngine::DestroyWorld() const {
    for (auto obj: m_Objects) {
        m_Root->RemoveChild(obj);
    }
    b2DestroyWorld(m_WorldId);
}

std::shared_ptr<Physics2D> PhysicsEngine::CreateObject(const std::string &imagePath,
                                                       const glm::vec2 &position,
                                                       int health,
                                                       EntityType entityType,
                                                       const glm::vec2 &size,
                                                       const float scale,
                                                       const float rotation,
                                                       const float density,
                                                       const float friction,
                                                       const bool isAwake) {
    auto obj = std::make_shared<Physics2D>(imagePath, health, entityType);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{position.x, position.y};
    bodyDef.rotation = b2MakeRot(rotation);
    bodyDef.isAwake = isAwake;

    b2BodyId bodyId = b2CreateBody(m_WorldId, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.enableHitEvents = true;
    shapeDef.density = density;
    shapeDef.friction = friction;

    if (entityType == BIRD || entityType == PIG) {
        if (entityType == BIRD) b2Body_Disable(bodyId);
        const b2Circle dynamicBox = {{0, 0}, size.x};
        b2CreateCircleShape(bodyId, &shapeDef, &dynamicBox);
    } else {
        const b2Polygon dynamicBox = b2MakeBox(size.x, size.y);
        b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
    }


    obj->SetBodyId(bodyId);
    obj->SetScale(scale);
    m_Objects.push_back(obj);

    m_Root->AddChild(obj);
    return obj;
}

std::shared_ptr<Physics2D> PhysicsEngine::FindObjectByBodyId(b2BodyId bodyId) {
    for (auto obj: m_Objects) {
        if (B2_ID_EQUALS(obj->GetBodyId(), bodyId)) {
            return obj;
        }
    }
    return nullptr;
}

void PhysicsEngine::ProcessEvents() {
    b2ContactEvents contactEvents = b2World_GetContactEvents(m_WorldId);
    for (int i = 0; i < contactEvents.hitCount; ++i) {
        b2ContactHitEvent &hitEvent = contactEvents.hitEvents[i];
        const b2BodyId bodyA = b2Shape_GetBody(hitEvent.shapeIdA);
        const b2BodyId bodyB = b2Shape_GetBody(hitEvent.shapeIdB);
        auto objA = FindObjectByBodyId(bodyA);
        auto objB = FindObjectByBodyId(bodyB);

        if (objA && objB) {
            //LOG_DEBUG("Hit event: {} {} {}", objA->GetImagePath(), objB->GetImagePath(), hitEvent.approachSpeed);
            if (objA->GetEntityType() != BIRD) {
                objA->SetHealth(objA->GetHealth() - (20 * hitEvent.approachSpeed));
                LOG_DEBUG("objA Health: {}", objA->GetHealth());
                if (objA->GetHealth() <= 0) {
                    DeleteObject(bodyA);
                }
            }
        }
    }

    auto [moveEvents, moveCount] = b2World_GetBodyEvents(m_WorldId);
    for (int i = 0; i < moveCount; ++i) {
        b2BodyMoveEvent &bodyEvent = moveEvents[i];
        const b2BodyId bodyId = bodyEvent.bodyId;
        const auto position = bodyEvent.transform.p;
        const auto rotation = bodyEvent.transform.q;
        auto obj = FindObjectByBodyId(bodyId);

        obj->SetPosition({position.x * 100 + X_OFFSET, position.y * 100 + Y_OFFSET});
        obj->SetRotation(b2Rot_GetAngle(rotation));
    }
}

void PhysicsEngine::ApplyForce(const b2BodyId &bodyId, const b2Vec2 &force) const {
    if (B2_IS_NULL(m_WorldId) || B2_IS_NULL(bodyId)) {
        LOG_ERROR("World or body is null");
        return;
    }
    b2Body_ApplyForceToCenter(bodyId, force, true);
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
