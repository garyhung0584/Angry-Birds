#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"


void App::Update() {
    if (m_Phase == MAIN_MENU || m_Phase == LEVEL_SELECT) {
        if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
            auto position = Util::Input::GetCursorPosition();
            if (m_Phase == MAIN_MENU) {
                if (m_Start->ifButtonClick(position)) {
                    m_RM->EnterLevel(0);
                    m_Phase = LEVEL_SELECT;
                    PhaseManager();
                }
            } else if (m_Phase == LEVEL_SELECT) {
                for (int i = 0; i < 10; i++) {
                    if (m_Buttons[i]->ifButtonClick(position)) {
                        m_RM->EnterLevel(i + 1);
                        m_Phase = static_cast<Phase>(i + 2);
                        for (const std::shared_ptr<Button> &button: m_Buttons) {
                            m_Root.RemoveChild(button);
                        };
                        PhaseManager();
                    }
                }
            }
        }
    }
    if (m_Phase != LEVEL_SELECT && m_Phase != MAIN_MENU) {
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
            auto position = Util::Input::GetCursorPosition();
            auto posSlingshot = m_slingshot->GetPosition();
            auto posBias = position - posSlingshot;
            if (posBias.x > -50 && posBias.x < 50 && posBias.y > 0 && posBias.y < 100) {
                isPressed = true;
            }
        }
        if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
            auto position = Util::Input::GetCursorPosition();
            const auto posSlingshot = m_slingshot->GetPosition();
            auto posStart = posSlingshot + glm::vec2(0, 70);
            auto posBias = position - posStart;
            float len = length(posBias);
            if (len > 80.0f) {
                posBias =(posBias / len) * 80.0f;
            }
            m_PE->Release(posBias);
            isPressed = false;
        }
        if (isPressed) {
            auto position = Util::Input::GetCursorPosition();
            const auto posSlingshot = m_slingshot->GetPosition();
            auto posStart = posSlingshot + glm::vec2(0, 70);
            auto posBias = position - posStart;
            float angle = atan2(-posBias.y, -posBias.x);
            float len = length(posBias);
            if (len > 80.0f) {
                position = posStart + (posBias / len) * 80.0f;
            }
            m_PE->Pull(position, angle);
        }
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    if (m_Phase != MAIN_MENU && m_Phase != LEVEL_SELECT) {
        m_PE->UpdateWorld();
    }
    m_Root.Update();
}
