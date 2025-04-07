#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include <string>
#include "Physics2D.hpp"
#include "Util/Logger.hpp"

#include "box2d/box2d.h"
#include "Util/Renderer.hpp"


class PhysicsEngine {
public:
    explicit PhysicsEngine(Util::Renderer *Root);

    std::shared_ptr<Physics2D> CreateObject(const std::string &imagePath, const glm::vec2 &position, const glm::vec2 &size,
                      float scale = 1.f, float rotation = 0.f, bool isAwake = true);

    void UpdateWorld() const;

    void DestroyWorld() const;


    // ~PhysicsEngine() {
    //     b2DestroyWorld(worldId);
    // }

private:
    b2WorldId worldId{};
    Util::Renderer *m_Root;
    std::vector<std::shared_ptr<Physics2D> > objects;

    // offset the box2d world to the screen
    const int X_OFFSET= -450;
    const int Y_OFFSET= -210;
};

#endif //PHYSICSENGINE_HPP
