#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include <string>
#include "Physics2D.hpp"
#include "Util/Logger.hpp"

#include "box2d/box2d.h"


class PhysicsEngine {
public:
    explicit PhysicsEngine();

    void CreateWorld();

    void AddObject(std::shared_ptr<Physics2D> obj) const;

    std::shared_ptr<Physics2D> CreateObject(const std::string &imagePath, const glm::vec2 &position, const glm::vec2 &size, float rotation );

    void RunWorld() const;

    void UpdateWorld() const;

    void DestroyWorld() const;


    // ~PhysicsEngine() {
    //     b2DestroyWorld(worldId);
    // }

private:
    b2WorldId worldId{};
    std::vector<std::shared_ptr<Physics2D> > objects;
};

#endif //PHYSICSENGINE_HPP
