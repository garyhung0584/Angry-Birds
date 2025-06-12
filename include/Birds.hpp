#ifndef BIRDS_HPP
#define BIRDS_HPP

#include <string>
#include "Physics2D.hpp"


class Birds : public Physics2D {
public:
    explicit Birds(const std::string &birdType) : Physics2D(RESOURCE_DIR"/Birds/" + birdType + ".png", 1, BIRD) {
    }

    virtual void Ability() = 0;

    void SetDensity(const float density) {
        m_Density = density;
    }

    void SetFriction(const float friction) {
        m_Friction = friction;
    }

    void SetCenter(const glm::vec2 &center) {
        m_Center = center;
    }

    void SetRadius(const float radius) {
        m_Radius = radius;
    }

    [[nodiscard]] float GetDensity() const {
        return m_Density;
    }

    [[nodiscard]] float GetFriction() const {
        return m_Friction;
    }

    [[nodiscard]] glm::vec2 GetCenter() const {
        return m_Center;
    }

    [[nodiscard]] float GetRadius() const {
        return m_Radius;
    }

    void SetWorldId(const b2WorldId worldId) {
        m_WorldId = worldId;
    }

    [[nodiscard]] b2WorldId GetWorldId() const {
        return m_WorldId;
    }

private:
    float m_Density = 0.1f;
    float m_Friction = 0.3f;
    glm::vec2 m_Center = {0.0f, 0.0f};
    float m_Radius = 0.2f;
    b2WorldId m_WorldId{};
};


#endif //BIRDS_HPP
