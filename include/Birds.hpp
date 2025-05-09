#ifndef BIRDS_HPP
#define BIRDS_HPP

#include <string>
#include "Physics2D.hpp"


class Birds : public Physics2D {
public:
    Birds(const std::string &birdType) : Physics2D(RESOURCE_DIR"/Birds/" + birdType + ".png", 1, BIRD) {
    }

    Birds();

    void init(const glm::vec2 position, glm::vec2 size) {
        SetPosition(position);
    }

    virtual void Ability() = 0;

    void SetDensity(float density) {
        m_Density = density;
    }

    void SetFriction(float friction) {
        m_Friction = friction;
    }

    void SetCenter(const glm::vec2 &center) {
        m_Center = center;
    }

    void SetRadius(float radius) {
        m_Radius = radius;
    }

    float GetDensity() const {
        return m_Density;
    }

    float GetFriction() const {
        return m_Friction;
    }

    glm::vec2 GetCenter() const {
        return m_Center;
    }

    float GetRadius() const {
        return m_Radius;
    }

private:
    // static const std::string m_birdType;
    float m_Density = 0.1f;
    float m_Friction = 0.3f;
    glm::vec2 m_Center = {0.0f, 0.0f};
    float m_Radius = 0.2f;
    // static const std::string birdImagePath;
    // static const std::string birdSoundPath;
};


#endif //BIRDS_HPP
