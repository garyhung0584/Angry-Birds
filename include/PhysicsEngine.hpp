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

    void CreateBird(BirdType birdType);

    void CreatePig(const glm::vec2 &position, PigType pigType);

    void CreateStructure(const glm::vec2 &position, EntityType entityType, StructureType structureType, float rotation);

    void Pull(const glm::vec2 &pos, float angle);

    void Release(glm::vec2 &posbias);

    void UpdateWorld();

    void DestroyWorld() const;

    void ProcessContactEvents(b2WorldId worldId);

    // ~PhysicsEngine() {
    //     b2DestroyWorld(worldId);
    // }

private:
    std::shared_ptr<Physics2D> CreateObject(const std::string &imagePath, const glm::vec2 &position, int health,
                                            EntityType entityType, const glm::vec2 &size, float scale = 1.f,
                                            float rotation = 0.f, float density = 0.1f, float friction = 0.3f,
                                            bool isAwake = false);

    void ApplyForce(const b2BodyId &bodyId, const b2Vec2 &force) const;

    void DeleteObject(const std::shared_ptr<Physics2D> &obj) ;

    std::shared_ptr<Physics2D> FindObjectByBodyId(b2BodyId bodyId);

    b2WorldId worldId{};
    Util::Renderer *m_Root;
    std::vector<std::shared_ptr<Physics2D> > m_Objects;
    std::vector<std::shared_ptr<Physics2D> > m_Birds;
    const int X_OFFSET = -450;
    const int Y_OFFSET = -210;
};

#endif //PHYSICSENGINE_HPP
