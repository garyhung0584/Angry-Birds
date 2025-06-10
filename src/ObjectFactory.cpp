#include "ObjectFactory.hpp"

#include "Structure.hpp"


std::shared_ptr<Birds> ObjectFactory::CreateBird(const BirdType birdType, const glm::vec2 &position) const {
    // static const std::unordered_map<BirdType, std::pair<std::string, glm::vec2> > birdProperties = {
    // {RED, {"Red", {0.2f, 0.2f}}},
    // {BLUE, {"Blue", {0.2f, 0.2f}}},
    // {YELLOW, {"Yellow", {0.2f, 0.2f}}},
    // {BLACK, {"Black", {0.2f, 0.2f}}},
    // {WHITE, {"White", {0.2f, 0.2f}}},
    // {BIG, {"Big", {0.2f, 0.2f}}}
    // };
    //
    // auto it = birdProperties.find(birdType);
    // if (it == birdProperties.end()) {
    //     LOG_ERROR("Invalid bird type");
    //     return nullptr;
    // }
    //
    // const auto &[birdName, size] = it->second;
    // const std::string imagePath = RESOURCE_DIR"/Birds/" + birdName + "Bird.png";
    // return CreateObject(imagePath, position, 1, BIRD, size, 0.2f, 0, 0.1f, 0.3f, false);
    std::shared_ptr<Birds> bird;

    switch (birdType) {
        case RED: {
            bird = std::make_shared<RedBird>();
            break;
        }
        case YELLOW: {
            bird = std::make_shared<YellowBird>();
            break;
        }
        case BIG: {
            bird = std::make_shared<BigBird>();
            break;
        }
        case BLACK: {
            bird = std::make_shared<BlackBird>();
            break;
        }
        case BLUE: {
            bird = std::make_shared<BlueBird>();
            break;
        }
        case WHITE: {
            bird = std::make_shared<WhiteBird>();
            break;
        }
        default:
            LOG_ERROR("Unknown bird type");
            return nullptr;
    }
    constexpr float rotation = 0.0f;
    constexpr bool isAwake = false;

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{position.x, position.y};
    bodyDef.rotation = b2MakeRot(rotation);
    bodyDef.isAwake = isAwake;

    const b2BodyId bodyId = b2CreateBody(m_WorldId, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.enableHitEvents = true;
    shapeDef.density = bird->GetDensity();
    shapeDef.friction = bird->GetFriction();
    const auto center = bird->GetCenter();
    const b2Circle shape = {{center.x,center.y} , bird->GetRadius()};
    b2CreateCircleShape(bodyId, &shapeDef, &shape);
    b2Body_Disable(bodyId);

    bird->SetBodyId(bodyId);
    bird->SetWorldId(m_WorldId);
    bird->SetScale(0.2f);
    return bird;
}

std::shared_ptr<Physics2D> ObjectFactory::CreatePig(const PigType pigType, const glm::vec2 &position) const {
    // Pig type: { Name, Health, Size }
    static const std::unordered_map<PigType, std::tuple<std::string, int, glm::vec2> > pigProperties = {
        {NORMAL, {"Normal", 90, {0.18f, 0.18f}}},
        {KING, {"King", 1000, {0.3f, 0.3f}}},
        {SOLDIER, {"Soldier", 500, {0.2f, 0.2f}}}
    };

    auto it = pigProperties.find(pigType);
    if (it == pigProperties.end()) {
        LOG_ERROR("Pig type not recognized");
        return nullptr;
    }

    const auto &[pigName, health, size] = it->second;
    const std::string imagePath = RESOURCE_DIR"/Pigs/Pig" + pigName + ".png";
    return CreateObject(imagePath, position, health, PIG, size, 0.05f, 0, 0.1f, 0.3f, true);
}

std::shared_ptr<Physics2D> ObjectFactory::CreateStructure(const EntityType entityType,
                                                          const StructureType structureType,
                                                          const glm::vec2 &position, const float rotation) const {
    // Entity type: { Material, Health, Density, Friction }
    static const std::unordered_map<EntityType, std::tuple<std::string, int, float, float> > entityProperties = {
        {WOOD, {"Wood", 100, 0.1f, 0.3f}},
        {STONE, {"Stone", 120, 0.2f, 0.3f}},
        {GLASS, {"Glass", 50, 0.1f, 0.1f}}
    };

    // Structure type: { Shape, Size }
    static const std::unordered_map<StructureType, std::pair<std::string, glm::vec2> > structureProperties = {
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

    const auto entityIt = entityProperties.find(entityType);
    const auto structureIt = structureProperties.find(structureType);

    if (entityIt == entityProperties.end()) {
        LOG_ERROR("Entity type not recognized");
        return nullptr;
    }
    if (structureIt == structureProperties.end()) {
        LOG_ERROR("Structure type not recognized");
        return nullptr;
    }

    const auto &[material, health, density, friction] = entityIt->second;
    const auto &[shape, size] = structureIt->second;

    auto obj = std::make_shared<Structure>(RESOURCE_DIR"/" + material + "/" + material + "_" + shape + ".png", health, entityType, structureType);
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{position.x, position.y};
    bodyDef.rotation = b2MakeRot(rotation);
    bodyDef.isAwake = false;

    b2BodyId bodyId = b2CreateBody(m_WorldId, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.enableHitEvents = true;
    shapeDef.density = density;
    shapeDef.friction = friction;
    const b2Polygon dynamicBox = b2MakeBox(size.x, size.y);
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    obj->SetBodyId(bodyId);
    obj->SetScale(1.f);
    return obj;
}

std::shared_ptr<Physics2D> ObjectFactory::CreateObject(const std::string &imagePath, const glm::vec2 &position,
                                                       int health, EntityType entityType, const glm::vec2 &size,
                                                       float scale, float rotation, float density, float friction,
                                                       bool isAwake) const {
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
    return obj;
}
