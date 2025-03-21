#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"


void App::Update() {
    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
        auto position = Util::Input::GetCursorPosition();
        if (m_Phase == Phase::MAIN_MENU) {
            if (m_start->ifButtonClick(position)) {
                m_RM->EnterLevel(0);
                m_Phase = Phase::LEVEL_SELECT;
                PhaseManager();
            }
        } else if (m_Phase == Phase::LEVEL_SELECT) {
            LOG_DEBUG("Mouse position: x: {}, y: {}", position.x, position.y);
            for (int i = 0; i < 10; i++) {
                if (m_buttons[i]->ifButtonClick(position)) {
                    LOG_DEBUG("Mouse button: {}", i+1);
                }
            }
        }
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }


    m_Root.Update();
}
