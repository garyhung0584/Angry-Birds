#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

#include "Util/GameObject.hpp"

class Button : public Util::GameObject {
public:
    explicit Button(const std::string& ImagePath);

    Button(const Button&) = delete;

    Button(Button&&) = delete;

    Button& operator=(const Button&) = delete;

    Button& operator=(Button&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    // TODO: Implement the collision detection
    [[nodiscard]] bool IfCollides(const std::shared_ptr<Button>& other) const {
        auto myPos = GetPosition();
        auto otherPos = other->GetPosition();
        return !(myPos.x + 30 < otherPos.x ||
             myPos.x > otherPos.x + 30 ||
             myPos.y + 30 < otherPos.y ||
             myPos.y > otherPos.y + 30);
    }

    // TODO: Add and implement more methods and properties as needed to finish Giraffe Adventure.

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};

#endif //BUTTON_HPP
