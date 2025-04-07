#include "PhysicsEngine.hpp"

#include "Util/Logger.hpp"

PhysicsEngine::PhysicsEngine() = default;

void PhysicsEngine::CreateWorld() {
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{0.0f, -10.0f};
    worldId = b2CreateWorld(&worldDef);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = b2Vec2{0.0f, -10.0f};
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    // return worldId;
}

void PhysicsEngine::AddObject(const std::shared_ptr<Physics2D> obj) const {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{0.0f, 4.0f};
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);
    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    obj->SetBodyId(bodyId);
}

std::shared_ptr<Physics2D> PhysicsEngine::CreateObject(const std::string &imagePath, const glm::vec2 &position,
                                                       const glm::vec2 &size, const float rotation) {
    auto obj = std::make_shared<Physics2D>(imagePath);

    obj->SetScale(0.5f);


    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{position.x, position.y};
    bodyDef.rotation = b2MakeRot(rotation);

    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

    b2Polygon dynamicBox = b2MakeBox(size.x, size.y);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;

    // Attach the shape to the body
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    // Set the body ID to the object
    obj->SetBodyId(bodyId);

    objects.push_back(obj);
    return obj;
}

void PhysicsEngine::RunWorld() const {
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    for (int i = 0; i < 90; ++i) {
        // Run the simulation for 60 steps
        b2World_Step(worldId, timeStep, subStepCount);

        for (const auto &obj: objects) {
            b2BodyId bodyId = obj->GetBodyId();
            b2Vec2 position = b2Body_GetPosition(bodyId);
            b2Rot rotation = b2Body_GetRotation(bodyId);

            obj->SetPosition({position.x * 10, position.y * 10});
            obj->SetRotation(b2Rot_GetAngle(rotation));

            LOG_DEBUG("Position: ({}, {}) Rotation: {}", position.x, position.y, b2Rot_GetAngle(rotation));
        }
    }
}

void PhysicsEngine::UpdateWorld() const {
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    b2World_Step(worldId, timeStep, subStepCount);
    for (const auto &obj: objects) {
        b2BodyId bodyId = obj->GetBodyId();
        b2Vec2 position = b2Body_GetPosition(bodyId);
        b2Rot rotation = b2Body_GetRotation(bodyId);

        obj->SetPosition({position.x * 10, position.y * 10});
        obj->SetRotation(b2Rot_GetAngle(rotation));

        LOG_DEBUG("Position: ({}, {}) Rotation: {}", position.x, position.y, b2Rot_GetAngle(rotation));
    }
}

void PhysicsEngine::DestroyWorld() const {
    b2DestroyWorld(worldId);
}
