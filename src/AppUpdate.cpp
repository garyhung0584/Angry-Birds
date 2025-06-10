#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"


void App::Update() {
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
                    m_Root.RemoveChild(m_CheatMode);
                    PhaseManager();
                }
            }
            if (m_CheatMode->ifButtonClick({position.x-150, position.y})) {
                isCheatMode = !isCheatMode;
                m_CheatMode->SetImage(isCheatMode ? RESOURCE_DIR"/GUI/CheatTrue.png" : RESOURCE_DIR"/GUI/CheatFalse.png");
            }
        } else {
            if (m_Restart->ifButtonClick(position) || m_Quit->ifButtonClick(position)) {
                m_Root.RemoveChild(m_Pause);
                m_Root.RemoveChild(m_Restart);
                m_Root.RemoveChild(m_Quit);
                m_Root.RemoveChild(m_slingshot->GetSlingshot()[0]);
                m_Root.RemoveChild(m_slingshot->GetSlingshot()[1]);

                m_PE->DestroyWorld();

                if (m_Quit->ifButtonClick(position)) {
                    m_Phase = LEVEL_SELECT;
                    m_RM->EnterLevel(0);
                }

                PhaseManager();
            }
            if (m_Pause->ifButtonClick(position)) {
                isPause = !isPause;
            }
        }
    }
    if (m_Phase != LEVEL_SELECT && m_Phase != MAIN_MENU) {
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
            if (m_PE->IsFlying()) {
                m_PE->UseAbility();
            }
            auto position = Util::Input::GetCursorPosition();
            auto posSlingshot = m_slingshot->GetPosition();
            auto posBias = position - posSlingshot;
            if (posBias.x > -50 && posBias.x < 50 && posBias.y > 0 && posBias.y < 100) {
                isPressed = true;
            }
            // LOG_DEBUG(position);
        }
        if (isPressed) {
            auto position = Util::Input::GetCursorPosition();
            const auto posSlingshot = m_slingshot->GetPosition();
            auto posStart = posSlingshot + glm::vec2(0, 70);
            auto posBias = position - posStart;
            // float angle = atan2(-posBias.y, -posBias.x);
            float len = length(posBias);

            if (len > 80.0f) {
                position = posStart + (posBias / len) * 80.0f;
                posBias = (posBias / len) * 80.0f;
            }
            m_PE->Pull(position);
            m_slingshot->Pull(position);

            if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
                m_PE->Release(posBias);
                m_slingshot->Release();
                isPressed = false;
            }
        }

        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - m_LastIsEndCheck);

        if (duration.count() >= 5) {
            // if (m_PE->IsEnd()) {
            //     m_Root.RemoveChild(m_Pause);
            //     m_Root.RemoveChild(m_Restart);
            //     m_Root.RemoveChild(m_Quit);
            //     m_Root.RemoveChild(m_slingshot->GetSlingshot()[0]);
            //     m_Root.RemoveChild(m_slingshot->GetSlingshot()[1]);
            //
            //     m_PE->DestroyWorld();
            //
            //     m_Phase = LEVEL_SELECT;
            //     m_RM->EnterLevel(0);
            //     PhaseManager();
            // }
            // m_LastIsEndCheck = now;
        }

    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    if (m_Phase != MAIN_MENU && m_Phase != LEVEL_SELECT) {
        m_PE->SetCheatMode(isCheatMode);
        if (!isPause) {
            m_PE->UpdateWorld();
        }
    }


    m_Root.Update();
}
