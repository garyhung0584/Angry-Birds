#include "PhysicsEngine.hpp"

#include "Util/Logger.hpp"

PhysicsEngine::PhysicsEngine(Util::Renderer *Root) {
    m_Root = Root;

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{0.0f, -10.0f};
    worldId = b2CreateWorld(&worldDef);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = b2Vec2{4.5f, -1.0f};
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(6.4f, 1.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);
}

void PhysicsEngine::CreateBird(const glm::vec2 &position, const BirdType birdType) {
    std::string birdName;
    glm::vec2 size;
    const int health = 1;
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
            size = {0.5f, 0.5f};
            break;
        default:
            LOG_ERROR("Invalid bird type");
            return;
    }
    const std::string imagePath = RESOURCE_DIR"/Birds/" + birdName + "Bird.png";
    m_Birds.push_back(CreateObject(imagePath, position, health, BIRD, size, 0.2f, 0));
}

void PhysicsEngine::CreatePig(const glm::vec2 &position, const PigType pigType) {
    std::string pigName;
    glm::vec2 size;
    int health;

    switch (pigType) {
        case NORMAL:
            pigName = "Normal";
            health = 100;
            size = {0.2f, 0.2f};
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
            health = 0;
            LOG_ERROR("Pig type not recognized");
            return;
    }

    const std::string imagePath = RESOURCE_DIR"/Pigs/Pig" + pigName + ".png";
    CreateObject(imagePath, position, health, PIG, size, 0.05f, 0);
}

void PhysicsEngine::CreateStructure(const glm::vec2 &position, const EntityType entityType,
                                    const StructureType structureType, const float rotation) {
    std::string material;
    std::string shape;
    glm::vec2 size;
    float friction;
    float density;
    int health;

    switch (entityType) {
        case WOOD:
            material = "Wood";
            health = 100;
            density = 0.1f;
            friction = 0.3f;
            break;
        case STONE:
            material = "Stone";
            health = 300;
            density = 0.1f;
            friction = 0.3f;
            break;
        case GLASS:
            material = "Glass";
            health = 50;
            density = 0.1f;
            friction = 0.1f;
            break;
        default:
            LOG_ERROR("Structure type not recognized");
            return;
    }

    switch (structureType) {
        case FRAME_BLOCK:
            shape = "A1";
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
            break;
        case BLOCK:
            shape = "F1";
            break;
        case BAR_LONG:
            shape = "G1";
            break;
        case RECTANGLE_SMALL:
            shape = "H1";
            break;
        case BAR:
            shape = "I1";
            break;
        case BLOCK_SMALL:
            shape = "J1";
            break;
        case BAR_SHORT:
            shape = "K1";
            break;
        case DISC_SMALL:
            shape = "L1";
            break;
        default:
            LOG_ERROR("Structure type not recognized");
            return;
    }

    std::string imagePath = RESOURCE_DIR"/" + material + "/" + material + "_" + shape + ".png";
    CreateObject(imagePath, position, health, entityType, size, 0.2f, rotation, density, friction);
}


void PhysicsEngine::Pull(glm::vec2 &pos) {
    b2BodyId bodyId = m_Objects[0]->GetBodyId();
    b2Vec2 force = b2Vec2{pos.x, pos.y};
    ApplyForce(bodyId, force);
}

void PhysicsEngine::Release() {
    b2BodyId bodyId = m_Objects[0]->GetBodyId();
    b2Vec2 force = b2Vec2{0.0f, 0.0f};
    ApplyForce(bodyId, force);
}


void PhysicsEngine::UpdateWorld() const {
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    b2World_Step(worldId, timeStep, subStepCount);
    for (const auto &obj: m_Objects) {
        b2BodyId bodyId = obj->GetBodyId();
        b2Vec2 position = b2Body_GetPosition(bodyId);
        b2Rot rotation = b2Body_GetRotation(bodyId);

        obj->SetPosition({position.x * 100 + X_OFFSET, position.y * 100 + Y_OFFSET});
        obj->SetRotation(b2Rot_GetAngle(rotation));

        LOG_DEBUG("Position: ({}, {}) Rotation: {}", position.x, position.y, b2Rot_GetAngle(rotation));
    }
}

void PhysicsEngine::DestroyWorld() const {
    b2DestroyWorld(worldId);
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

    const b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    shapeDef.friction = friction;

    if (entityType == BIRD || entityType == PIG) {
        const b2Circle dynamicBox = {{0,0}, size.x};
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

void PhysicsEngine::ApplyForce(const b2BodyId &bodyId, const b2Vec2 &force) const {
    if (B2_IS_NULL(worldId) || B2_IS_NULL(bodyId)) {
        LOG_ERROR("World or body is null");
        return;
    }
    b2Body_ApplyForceToCenter(bodyId, force, true);
}
