#ifndef UIOBJECT_HPP
#define UIOBJECT_HPP


#include "Util/GameObject.hpp"

class UIObject : public Util::GameObject {
public:
    explicit UIObject(const std::string &ImagePath);

    UIObject &operator=(UIObject &&) = delete;

    UIObject &operator=(const UIObject &) = delete;

    UIObject(UIObject &&) = delete;

    UIObject(const UIObject &) = delete;

    bool GetVisibility() const { return m_Visible; }

    glm::vec2 &GetPosition() { return m_Transform.translation; }

    void SetImage(const std::string &ImagePath);

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

    void SetRotation(const float Rotation) { m_Transform.rotation = Rotation; }

    void SetScale(float Scale) { m_Transform.scale = {Scale, Scale}; }

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }
};


#endif //UIOBJECT_HPP
