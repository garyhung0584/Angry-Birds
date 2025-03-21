#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include <string>

#include "Util/GameObject.hpp"

class PhysicsEngine : public Util::GameObject {

    PhysicsEngine(const PhysicsEngine &) = delete;

    PhysicsEngine(PhysicsEngine &&) = delete;

    PhysicsEngine &operator=(const PhysicsEngine &) = delete;

    PhysicsEngine &operator=(PhysicsEngine &&) = delete;



};

#endif //PHYSICSENGINE_HPP
