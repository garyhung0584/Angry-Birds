#ifndef PHYSICS2D_HPP
#define PHYSICS2D_HPP


#include <string>
#include <box2d/box2d.h>

#include "type.hpp"
#include "Util/GameObject.hpp"

class Physics2D : public Util::GameObject {
public:
    Physics2D(const std::string &ImagePath, int health, EntityType entityType);

    Physics2D &operator=(Physics2D &&) = delete;

    Physics2D &operator=(const Physics2D &) = delete;

    Physics2D(Physics2D &&) = delete;

    Physics2D(const Physics2D &) = delete;

    glm::vec2 &GetPosition() { return m_Transform.translation; }

    [[nodiscard]] b2BodyId GetBodyId() const { return m_BodyId; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    [[nodiscard]] const std::string &GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] int GetHealth() const { return m_Health; }

    [[nodiscard]] EntityType GetEntityType() const { return m_EntityType; }

    void SetBodyId(const b2BodyId bodyId) { m_BodyId = bodyId; }

    void SetImage(const std::string &ImagePath);

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

    void SetRotation(const float Rotation) { m_Transform.rotation = Rotation; }

    void SetScale(float Scale) { m_Transform.scale = {Scale, Scale}; }

    void SetHealth(const int health) { m_Health = health; }

    virtual void ApplyDamage(const int damage) { m_Health -= damage; }

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    EntityType m_EntityType;
    b2BodyId m_BodyId{};
    int m_Health;
    std::string m_ImagePath;
};

#endif //PHYSICS2D_HPP
