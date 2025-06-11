#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include <string>
#include <queue>
#include <future>
#include "Physics2D.hpp"
#include "ObjectFactory.hpp"
#include "Birds.hpp"
#include "ScoreManager.hpp"
#include "Util/Logger.hpp"

#include "box2d/box2d.h"
#include "Util/Renderer.hpp"


class PhysicsEngine {
public:
    explicit PhysicsEngine(Util::Renderer *Root,
                           std::shared_ptr<ScoreManager> scoreManager);

    void CreateBird(BirdType birdType);

    void CreatePig(const glm::vec2 &position, PigType pigType);

    void CreateStructure(const glm::vec2 &position, EntityType entityType, StructureType structureType, float rotation);

    void Pull(const glm::vec2 &pos) const;

    void Release(const glm::vec2 &posBias);

    void UseAbility();

    bool IsFlying() const;

    bool IsEnd() const;

    bool IsLastBirdReleased() const { return m_isLastBirdReleased; }

    void SetFasForward() { m_isFastForward = true; }

    void SetUpWorld() const;

    void UpdateWorld();

    void DestroyWorld() const;

private:
    std::shared_ptr<Physics2D> FindObjectByBodyId(b2BodyId bodyId) const;

    void ProcessEvents();

    void ApplyForce(const b2BodyId &bodyId, const b2Vec2 &force) const;

    void HitObject(std::shared_ptr<Physics2D> &obj, float speed);

    void DeleteObject(b2BodyId bodyId);

    void SetCheatMode(bool enable);

    void SetNextBird() const;

    bool m_isLastBirdReleased = false;
    bool m_isFastForward = false;

    b2WorldId m_WorldId{};
    Util::Renderer *m_Root;

    std::shared_ptr<ScoreManager> m_ScoreManager;
    std::shared_ptr<ObjectFactory> m_ObjectFactory;

    std::vector<std::shared_ptr<Physics2D> > m_Objects;

    std::queue<std::shared_ptr<Birds> > m_Birds;
    std::vector<std::shared_ptr<Physics2D> > m_Pigs;
    std::vector<std::shared_ptr<Util::GameObject> > m_GuideDots;
    std::shared_ptr<Birds> m_Flying;

    std::chrono::steady_clock::time_point m_LastBirdReleaseTime;


    const int X_OFFSET = -450;
    const int Y_OFFSET = -210;
    bool m_isCheatMode = false;
    const b2Vec2 SLINGSHOT_POSITION = {0.0f, 1.3f};
};

#endif //PHYSICSENGINE_HPP
