#ifndef APP_HPP
#define APP_HPP


#include "Util/Renderer.hpp"
#include "pch.hpp"
#include "Button.hpp"
#include "Slingshot.hpp"
#include "PhysicsEngine.hpp"
#include "ResourceManager.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void PhaseManager();

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

    bool isPressed = false;
    bool isPause = false;


    State m_CurrentState = State::START;
    Phase m_Phase = MAIN_MENU;


    Util::Renderer m_Root;

    std::shared_ptr<Button> m_Start;
    std::shared_ptr<Button> m_Restart;
    std::shared_ptr<Button> m_Pause;
    std::vector<std::shared_ptr<Button> > m_Buttons;
    std::shared_ptr<Slingshot> m_slingshot;
    std::vector<std::shared_ptr<Util::GameObject> > m_GameObjects;

    std::shared_ptr<ResourceManager> m_RM;
    std::shared_ptr<PhysicsEngine> m_PE;
};

#endif
