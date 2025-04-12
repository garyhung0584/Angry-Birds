#include "PhysicsEngine.hpp"

#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

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
    std::string birdName;
    glm::vec2 size;
    glm::vec2 position;
    const int health = 1;
    int count = m_Birds.size();
    if (count == 0) {
        position = {0.f, 1.3f};
    } else {
        position = {count * -0.4f, 0.2f};
    }
    switch (birdType) {
        case RED:
            birdName = "Red";
            size = {0.2f, 0.2f};
            break;
        case BLUE:
            birdName = "Blue";
            size = {0.2f, 0.2f};
            break;
        case YELLOW:
            birdName = "Yellow";
            size = {0.2f, 0.2f};
            break;
        case BLACK:
            birdName = "Black";
            size = {0.2f, 0.2f};
            break;
        case WHITE:
            birdName = "White";
            size = {0.2f, 0.2f};
            break;
        case BIG:
            birdName = "Big";
            size = {0.2f, 0.2f};
            break;
        default:
            LOG_ERROR("Invalid bird type");
            return;
    }
    const std::string imagePath = RESOURCE_DIR"/Birds/" + birdName + "Bird.png";
    m_Birds.push(CreateObject(imagePath, position, health, BIRD, size, 0.2f, 0, 0.1f, 0.3f, false));
}

void PhysicsEngine::CreatePig(const glm::vec2 &position, const PigType pigType) {
    std::string pigName;
    glm::vec2 size;
    int health;

    switch (pigType) {
        case NORMAL:
            pigName = "Normal";
            health = 100;
            size = {0.18f, 0.18f};
            break;
        case KING:
            pigName = "King";
            health = 1000;
            size = {0.2f, 0.2f};
            break;
        case SOLDIER:
            pigName = "Soldier";
            health = 500;
            size = {0.2f, 0.2f};
            break;
        default:
            LOG_ERROR("Pig type not recognized");
            return;
    }

    const std::string imagePath = RESOURCE_DIR"/Pigs/Pig" + pigName + ".png";
    m_Pigs.push_back(CreateObject(imagePath, position, health, PIG, size, 0.05f, 0, 0.1f, 0.3f, true));
}

void PhysicsEngine::CreateStructure(const glm::vec2 &position, const EntityType entityType,
                                    const StructureType structureType, const float rotation) {
    std::string material;
    std::string shape;
    glm::vec2 size = {0.2f, 0.2f};
    float friction;
    float density;
    int health;

    switch (entityType) {
        case WOOD:
            material = "Wood";
            health = 100;
            density = 0.1f;
            friction = 1.0f;
            break;
        case STONE:
            material = "Stone";
            health = 130;
            density = 0.2f;
            friction = 0.3f;
            break;
        case GLASS:
            material = "Glass";
            health = 50;
            density = 0.2f;
            friction = 0.1f;
            break;
        default:
            LOG_ERROR("Structure type not recognized");
            return;
    }

    switch (structureType) {
        case FRAME_BLOCK:
            shape = "A1";
            size = {0.4f, 0.4f};
            break;
        case FRAME_TRIANGLE:
            shape = "B1";
            break;
        case TRIANGLE:
            shape = "C1";
            break;
        case DISC:
            shape = "D1";
            break;
        case RECTANGLE:
            shape = "E1";
            size = {0.4f, 0.2f};
            break;
        case BLOCK:
            shape = "F1";
            size = {0.2f, 0.2f};
            break;
        case BAR_LONG:
            shape = "G1";
            size = {1.f, 0.1f};
            break;
        case RECTANGLE_SMALL:
            shape = "H1";
            break;
        case BAR:
            shape = "I1";
            size = {0.7f, 0.1f};
            break;
        case BLOCK_SMALL:
            shape = "J1";
            size = {0.1f, 0.1f};
            break;
        case BAR_SHORT:
            shape = "K1";
            size = {0.4f, 0.1f};
            break;
        case DISC_SMALL:
            shape = "L1";
            break;
        default:
            LOG_ERROR("Structure type not recognized");
            return;
    }

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

    // auto fut = std::async( this->ProcessEvents, worldId);
    auto fut = std::async([this]() {
        return this->ProcessEvents();
    });
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
            if (objB->GetEntityType() != BIRD) {
                objB->SetHealth(objB->GetHealth() - (20 * hitEvent.approachSpeed));
                LOG_DEBUG("objB Health: {}", objB->GetHealth());
                if (objB->GetHealth() <= 0) {
                    DeleteObject(bodyB);
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
