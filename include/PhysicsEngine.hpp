#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include <string>
#include "Util/Logger.hpp"

#include "box2d/box2d.h"


class PhysicsEngine {
public:
    PhysicsEngine();

    PhysicsEngine(const PhysicsEngine &) = delete;

    PhysicsEngine(PhysicsEngine &&) = delete;

    PhysicsEngine &operator=(const PhysicsEngine &) = delete;

    PhysicsEngine &operator=(PhysicsEngine &&) = delete;

    void runWorld();
    void stopWorld();
    void addObject(b2BodyDef &bodyDef);

private:
    b2WorldId worldId;

};

#endif //PHYSICSENGINE_HPP
