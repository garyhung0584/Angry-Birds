#ifndef APP_HPP
#define APP_HPP


#include "Util/Renderer.hpp"
#include "pch.hpp"
#include "Button.hpp"
#include "Slingshot.hpp"
#include "PhysicsEngine.hpp"
#include "ResourceManager.hpp"
#include "ScoreManager.hpp"
#include <chrono>

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    [[nodiscard]] State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End();

private:
    void PhaseManager();

    void SetUpGame();

    void SetUpMenu();

    void ExitLevel();

    static void ShowMenu(const std::vector<std::shared_ptr<Util::GameObject> > &menu);

    static void HideMenu(const std::vector<std::shared_ptr<Util::GameObject> > &menu);

    typedef enum Phase {
        MAIN_MENU,
        LEVEL_SELECT,
        LEVEL_1,
        LEVEL_2,
        LEVEL_3,
        LEVEL_4,
        LEVEL_5,
        LEVEL_6,
        LEVEL_7,
        LEVEL_8,
        LEVEL_9,
        LEVEL_10,
    } Phase;

    bool m_isPressed = false;
    bool m_isPause = false;
    bool m_isCheatMode = false;

    State m_CurrentState = State::START;
    Phase m_Phase = MAIN_MENU;


    Util::Renderer m_Root;

    std::shared_ptr<Button> m_Start;
    std::shared_ptr<UIObject> m_Text_Score;
    std::vector<std::shared_ptr<Button> > m_UIButtons;
    std::vector<std::shared_ptr<Util::GameObject> > m_PauseMenu;
    std::vector<std::shared_ptr<Util::GameObject> > m_FinishMenu;
    std::vector<std::shared_ptr<Util::GameObject> > m_LostMenu;
    std::vector<std::shared_ptr<Button> > m_Buttons;
    std::shared_ptr<Slingshot> m_slingshot;

    std::chrono::steady_clock::time_point m_LastIsEndCheck;

    std::shared_ptr<ScoreManager> m_ScoreManager;
    std::shared_ptr<ResourceManager> m_RM;
    std::shared_ptr<PhysicsEngine> m_PE;
};

#endif
