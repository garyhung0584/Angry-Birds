#ifndef APP_HPP
#define APP_HPP


#include "Util/Renderer.hpp"
#include "pch.hpp" // IWYU pragma: export
#include "Button.hpp"
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
    void ValidTask();

private:
    enum class Phase {
        MAIN_MENU,
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
    };

    State m_CurrentState = State::START;
    Phase m_Phase = Phase::MAIN_MENU;


    Util::Renderer m_Root;

    std::shared_ptr<Button> m_start;

    std::shared_ptr<ResourceManager> m_RM;
};

#endif
