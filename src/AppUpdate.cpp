#include "App.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Update() {
    // Handle global exit
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
        return;
    }

    // Handle mouse up events
    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
        auto position = Util::Input::GetCursorPosition();

        switch (m_Phase) {
            case MAIN_MENU:
                if (m_Start->IsButtonClick(position)) {
                    m_RM->EnterLevel(0);
                    m_Phase = LEVEL_SELECT;
                    PhaseManager();
                }
                break;
            case LEVEL_SELECT:
                for (int i = 0; i < 10; i++) {
                    if (m_Buttons[i]->IsButtonClick(position)) {
                        m_RM->EnterLevel(i + 1);
                        m_Phase = static_cast<Phase>(i + 2);
                        for (const auto &button: m_Buttons) {
                            m_Root.RemoveChild(button);
                        }
                        PhaseManager();
                        break;
                    }
                }
                break;
            default:
                for (const auto &button: m_UIButtons) {
                    if (button->IsButtonClick(position)) {
                        switch (button->GetButtonType()) {
                            case PAUSE_BUTTON:
                                isPause = true;
                                ShowMenu(m_PauseMenu);
                                break;
                            case EXIT_BUTTON:
                            case BACK_BUTTON:
                                ExitLevel();
                                m_PE->DestroyWorld();
                                m_Phase = LEVEL_SELECT;
                                m_RM->EnterLevel(0);
                                PhaseManager();
                                break;
                            case RESTART_BUTTON:
                                LOG_DEBUG("RESTART_BUTTON");
                                ExitLevel();
                                m_PE->DestroyWorld();
                                PhaseManager();
                                break;
                            case RESUME_BUTTON:
                            case NEXT_BUTTON:
                                if (isPause) {
                                    LOG_DEBUG("RESUME_BUTTON");
                                    isPause = false;
                                    HideMenu(m_PauseMenu);
                                } else {
                                    LOG_DEBUG("NEXT_BUTTON");
                                    ExitLevel();
                                    m_PE->DestroyWorld();
                                    m_RM->EnterLevel(static_cast<int>(m_Phase) + 1);
                                    PhaseManager();
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    }
                }
                break;
        }
    }

    // Handle game phases (not menu/select)
    if (m_Phase != MAIN_MENU && m_Phase != LEVEL_SELECT) {
        // Handle slingshot and ability input
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
        }

        if (isPressed) {
            auto position = Util::Input::GetCursorPosition();
            const auto posSlingshot = m_slingshot->GetPosition();
            auto posStart = posSlingshot + glm::vec2(0, 70);
            auto posBias = position - posStart;
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

        // Periodic end check (commented out, can be enabled as needed)
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - m_LastIsEndCheck);
        if (duration.count() >= 5) {
            // if (m_PE->IsEnd()) {
            //     RemoveLevelUI();
            //     m_PE->DestroyWorld();
            //     m_Phase = LEVEL_SELECT;
            //     m_RM->EnterLevel(0);
            //     PhaseManager();
            // }
            // m_LastIsEndCheck = now;
        }

        // Update world if not paused
        if (!isPause) {
            m_PE->UpdateWorld();
        }
    }

    m_Root.Update();
}
