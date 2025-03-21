#ifndef PHYSICS2D_HPP
#define PHYSICS2D_HPP


#include <string>

#include "Util/GameObject.hpp"

class Physics2D : public Util::GameObject {
public:
    explicit Physics2D(const std::string &ImagePath);

    Physics2D(const Physics2D &) = delete;

    Physics2D(Physics2D &&) = delete;

    Physics2D &operator=(const Physics2D &) = delete;

    Physics2D &operator=(Physics2D &&) = delete;

    [[nodiscard]] const std::string &GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2 &GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string &ImagePath);

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;

    glm::vec3 velocity = {0, 0, 0};
    glm::vec3 acceleration = {0, 0, 0};

    int mass = 0;
};

#endif //PHYSICS2D_HPP
