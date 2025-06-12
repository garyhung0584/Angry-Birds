#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    PhaseManager();

    m_RM = std::make_shared<ResourceManager>();
    m_ScoreManager = std::make_shared<ScoreManager>();

    m_Root.AddChildren(m_RM->GetChildren());

    m_CurrentState = State::UPDATE;
}
