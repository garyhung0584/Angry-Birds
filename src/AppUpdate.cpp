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
            for (int i = 0; i < 10; i++) {
                if (m_buttons[i]->ifButtonClick(position)) {
                    m_RM->EnterLevel(i + 1);
                    m_Phase = static_cast<Phase>(i + 2);
                    for (const std::shared_ptr<Button> &button: m_buttons) {
                        m_Root.RemoveChild(button);
                    };
                    PhaseManager();
                }
            }
        }
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    if (m_Phase == Phase::LEVEL_1) {
        m_PE->UpdateWorld();
    }
    m_Root.Update();
}
