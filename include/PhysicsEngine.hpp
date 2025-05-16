#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include <string>
#include <queue>
#include <future>
#include "Physics2D.hpp"
#include "ObjectFactory.hpp"
#include "Birds.hpp"
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

    bool IsEnd();

    void SetUpWorld();

    void UpdateWorld();

    void DestroyWorld() const;

private:

    std::shared_ptr<Physics2D> FindObjectByBodyId(b2BodyId bodyId);

    void ProcessEvents();

    void ApplyForce(const b2BodyId &bodyId, const b2Vec2 &force) const;

    void HitObject(std::shared_ptr<Physics2D> &obj, b2BodyId bodyId, float speed);

    void DeleteObject(b2BodyId bodyId);

    b2WorldId m_WorldId{};
    Util::Renderer *m_Root;

    std::shared_ptr<ObjectFactory> m_ObjectFactory;


    std::vector<std::shared_ptr<Physics2D> > m_Objects;

    std::queue<std::shared_ptr<Birds> > m_Birds;
    std::shared_ptr<Birds> m_Flying;
    std::vector<std::shared_ptr<Physics2D> > m_Pigs;

    const int X_OFFSET = -450;
    const int Y_OFFSET = -210;
};

#endif //PHYSICSENGINE_HPP
