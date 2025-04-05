#ifndef PHYSICS2D_HPP
#define PHYSICS2D_HPP


#include <string>
#include <box2d/box2d.h>
#include "Util/GameObject.hpp"

class Physics2D : public Util::GameObject {
public:
    explicit Physics2D(const std::string &ImagePath, glm::vec2& position,  const glm::vec2& dimensions);

    Physics2D(const Physics2D &) = delete;

    Physics2D(Physics2D &&) = delete;

    Physics2D &operator=(const Physics2D &) = delete;

    Physics2D &operator=(Physics2D &&) = delete;

    [[nodiscard]] const std::string &GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2 &GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] const float &GetRotation() const { return m_Transform.rotation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string &ImagePath);

    void SetPosition(glm::vec2 &Position) { m_Transform.translation = Position; }

    void SetRotation(float rotation) { m_Transform.rotation = rotation; }


private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;

    b2BodyId* m_bodyId = nullptr;
    b2BodyDef bodyDef = b2DefaultBodyDef();
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    glm::vec2 m_dimensions{};
};

#endif //PHYSICS2D_HPP
