#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    m_start = std::make_shared<Button>(RESOURCE_DIR"/Button_Start.png");
    m_start->SetPosition({-1.5f, -180.f});

    m_start->SetZIndex(50);
    m_Root.AddChild(m_start);

    m_RM = std::make_shared<ResourceManager>();
    m_Root.AddChildren(m_RM->GetChildren());

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3
    
    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }


    m_Root.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
