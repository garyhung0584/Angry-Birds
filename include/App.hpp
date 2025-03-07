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
    State m_CurrentState = State::START;


    Util::Renderer m_Root;

    std::shared_ptr<Button> m_start;

    std::shared_ptr<ResourceManager> m_RM;
};

#endif
