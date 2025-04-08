#ifndef PHYSICS2D_HPP
#define PHYSICS2D_HPP


#include <string>
#include <box2d/box2d.h>
#include "Util/GameObject.hpp"

class Physics2D : public Util::GameObject {
public:
    explicit Physics2D(const std::string &ImagePath);

    Physics2D(const Physics2D &) = delete;

    Physics2D(Physics2D &&) = delete;

    Physics2D &operator=(const Physics2D &) = delete;

    Physics2D &operator=(Physics2D &&) = delete;

    ~Physics2D() override {
        b2DestroyBody(m_BodyId);
    }

    [[nodiscard]] const std::string &GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] glm::vec2 &GetPosition() { return m_Transform.translation; }

    [[nodiscard]] Util::Transform &GetTransform() { return m_Transform; }

    [[nodiscard]] b2BodyId GetBodyId() const { return m_BodyId; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string &ImagePath);

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

    void SetRotation(const float Rotation) { m_Transform.rotation = Rotation; }

    void SetScale(float Scale) { m_Transform.scale = {Scale, Scale}; }

    void SetBodyId(const b2BodyId bodyId) { m_BodyId = bodyId; };

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;

    b2BodyId m_BodyId{};

    int health;

};

#endif //PHYSICS2D_HPP
