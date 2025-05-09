#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    PhaseManager();

    m_RM = std::make_shared<ResourceManager>();

    m_Root.AddChildren(m_RM->GetChildren());

    m_CurrentState = State::UPDATE;
}
