#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include "type.hpp"

#include "Util/Logger.hpp"
#include "UIObject.hpp"

class Button final : public UIObject {
public:
    explicit Button(const std::string &ImagePath) : UIObject(ImagePath), m_ButtonType() {
    };

    void SetButtonType(const ButtonType buttonType) { m_ButtonType = buttonType; }

    ButtonType GetButtonType() const { return m_ButtonType; }

    bool IsButtonClick(const glm::vec2 position) {
        const auto PosButton = GetPosition();
        const glm::vec2 halfSize = m_size * 0.5f;
        const glm::vec2 bias = position - PosButton;

        return -halfSize.x < bias.x && bias.x < halfSize.x &&
               -halfSize.y < bias.y && bias.y < halfSize.y;
    }

private:
    ButtonType m_ButtonType;

    glm::vec2 m_size = {150.0f, 150.0f};
};

#endif //BUTTON_HPP
