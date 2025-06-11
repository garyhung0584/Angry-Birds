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
                           const std::shared_ptr<ScoreManager> &scoreManager, bool cheat);

    [[nodiscard]] bool IsFlying() const;

    [[nodiscard]] bool IsLastBirdReleased() const { return m_isLastBirdReleased; }

    void CreateBird(BirdType birdType);

    void CreatePig(const glm::vec2 &position, PigType pigType);

    void CreateStructure(const glm::vec2 &position, EntityType entityType, StructureType structureType, float rotation);

    void DestroyWorld() const;

    void Pull(const glm::vec2 &pos);

    void Release(const glm::vec2 &posBias);

    [[nodiscard]] GameState GetGameState() const;

    bool SetCheatMode(bool enable);

    void SetFasForward() { m_isFastForward = true; }

    void SetUpWorld() const;

    void UpdateWorld();

    void UseAbility();

private:
    [[nodiscard]] std::shared_ptr<Physics2D> FindObjectByBodyId(b2BodyId bodyId) const;

    void ProcessEvents();

    void ApplyForce(const b2BodyId &bodyId, const b2Vec2 &force) const;

    void HitObject(std::shared_ptr<Physics2D> &obj, float speed);

    [[nodiscard]] glm::vec2 B2Pos2GamePos(const glm::vec2 &pos) const;

    [[nodiscard]] glm::vec2 GamePos2B2Pos(const glm::vec2 &pos) const;

    void DeleteObject(b2BodyId bodyId);

    bool m_isFastForward = false;
    bool m_isLastBirdReleased = false;

    b2WorldId m_WorldId{};
    Util::Renderer *m_Root{};

    std::shared_ptr<ObjectFactory> m_ObjectFactory;
    std::shared_ptr<ScoreManager> m_ScoreManager;

    std::vector<std::shared_ptr<Physics2D> > m_Objects; // All physics objects should be stored here

    std::queue<std::shared_ptr<Birds> > m_Birds;
    std::vector<std::shared_ptr<Physics2D> > m_Pigs;
    // std::vector<std::shared_ptr<Util::GameObject> > m_GuideDots;
    std::shared_ptr<Birds> m_Flying;

    std::chrono::steady_clock::time_point m_LastBirdReleaseTime;


    const float X_OFFSET = -450.0f;
    const float Y_OFFSET = -210;
    const glm::vec2 BIRD_POSITION_0 = {0.f, 1.3f};

    // cheat related
    bool m_isCheatMode = false;
};

#endif //PHYSICSENGINE_HPP
