#include "PhysicsEngine.hpp"


#include "box2d/box2d.h"

PhysicsEngine::PhysicsEngine() {
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{0.0f, -10.0f};
    b2WorldId worldId = b2CreateWorld(&worldDef);

}