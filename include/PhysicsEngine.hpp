#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include <string>
#include <queue>
#include <future>
#include "Physics2D.hpp"
#include "Util/Logger.hpp"

#include "box2d/box2d.h"
#include "Util/Renderer.hpp"

inline bool operator<(const b2BodyId &a, const b2BodyId &b) {
    return std::tie(a.index1, a.world0, a.revision) < std::tie(b.index1, b.world0, b.revision);
}

class PhysicsEngine {
public:
    explicit PhysicsEngine(Util::Renderer *Root);

    void CreateBird(BirdType birdType);

    void CreatePig(const glm::vec2 &position, PigType pigType);

    void CreateStructure(const glm::vec2 &position, EntityType entityType, StructureType structureType, float rotation);

    void Pull(const glm::vec2 &pos, float angle);

    void Release(glm::vec2 &posbias);

    bool IsEnd();

    void SetUpWorld();

    void UpdateWorld();

    void DestroyWorld() const;

private:
    std::shared_ptr<Physics2D> CreateObject(const std::string &imagePath, const glm::vec2 &position, int health,
                                            EntityType entityType, const glm::vec2 &size, float scale = 1.f,
                                            float rotation = 0.f, float density = 0.1f, float friction = 0.3f,
                                            bool isAwake = false);

    std::shared_ptr<Physics2D> FindObjectByBodyId(b2BodyId bodyId);

    void ProcessEvents();

    void ApplyForce(const b2BodyId &bodyId, const b2Vec2 &force) const;

    void DeleteObject(b2BodyId bodyId);

    b2WorldId m_WorldId{};
    Util::Renderer *m_Root;


    std::vector<std::shared_ptr<Physics2D> > m_Objects;

    std::queue<std::shared_ptr<Physics2D> > m_Birds;
    std::vector<std::shared_ptr<Physics2D> > m_Pigs;

    const int X_OFFSET = -450;
    const int Y_OFFSET = -210;
};

#endif //PHYSICSENGINE_HPP
