#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"


void App::Update() {
    if (m_Phase == Phase::MAIN_MENU || m_Phase == Phase::LEVEL_SELECT) {
        if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
            auto position = Util::Input::GetCursorPosition();
            if (m_Phase == Phase::MAIN_MENU) {
                if (m_Start->ifButtonClick(position)) {
                    m_RM->EnterLevel(0);
                    m_Phase = Phase::LEVEL_SELECT;
                    PhaseManager();
                }
            } else if (m_Phase == Phase::LEVEL_SELECT) {
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
    if (m_Phase != Phase::LEVEL_SELECT && m_Phase != Phase::MAIN_MENU) {
        bool isPressed = false;
        glm::vec2 posStart;
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
            auto position = Util::Input::GetCursorPosition();
            auto posSlingshot = m_slingshot->GetPosition();
            auto posBias = position - posSlingshot;
            if (posBias.x > -50 && posBias.x < 50 && posBias.y > 0 && posBias.y < 100) {
                isPressed = true;
                posStart = position;
            }
        }
        if (isPressed && Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
            isPressed = false;
        }
        if (isPressed) {
            auto position = Util::Input::GetCursorPosition();
            auto posBias = position - posStart;
        }
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    if (m_Phase != Phase::MAIN_MENU && m_Phase != Phase::LEVEL_SELECT) {
        m_PE->UpdateWorld();
    }
    m_Root.Update();
}
