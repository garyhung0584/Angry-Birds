#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include <string>
#include "Util/GameObject.hpp"
#include "Physics2D.hpp"
#include "Util/Logger.hpp"

#include "box2d/box2d.h"


class PhysicsEngine {
public:
    explicit PhysicsEngine();

    void addObject(const std::shared_ptr<Physics2D> &obj) const;

    PhysicsEngine(const PhysicsEngine &) = delete;

    PhysicsEngine(PhysicsEngine &&) = delete;

    PhysicsEngine &operator=(const PhysicsEngine &) = delete;

    PhysicsEngine &operator=(PhysicsEngine &&) = delete;

    void runWorld() const;

    void stopWorld();


private:
    b2WorldId worldId;


};

#endif //PHYSICSENGINE_HPP
