#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"


void App::Update() {



    if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
        auto position = Util::Input::GetCursorPosition	();

        if (m_start->ifClick(position) && m_Phase == Phase::MAIN_MENU) {
            m_RM->EnterLevel(0);
            m_start->SetVisible(false);
            m_Phase = Phase::LEVEL_SELECT;
            PhaseManager();
        }
        LOG_DEBUG("Mouse position: x: {}, y: {}", position.x, position.y);


    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
        }


    m_Root.Update();
}
