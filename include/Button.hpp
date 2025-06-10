#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

#include "Util/Logger.hpp"

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

    void SetScale(float Scale) { m_Transform.scale = {Scale, Scale}; }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }


    bool ifButtonClick(const glm::vec2 position) const {
        const auto PosButton = GetPosition();
        const auto bias = position- PosButton;
        //LOG_DEBUG("Bias: x: {}, y: {}", bias.x, bias.y);
        return -75 < bias.x && bias.x < 75 && -75 < bias.y && bias.y < 75;
    }

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};

#endif //BUTTON_HPP
