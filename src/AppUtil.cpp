#include "AppUtil.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"

/**
 * @brief The function to validate the tasks.
 * @warning Do not modify this function.
 * @note See README.md for the task details.
 */
void App::PhaseManager() {
    bool isMainMenu;
    bool is;
    LOG_DEBUG("Validating the task {}", static_cast<int>(m_Phase));
    switch (m_Phase) {
        case Phase::MAIN_MENU:

            m_start = std::make_shared<Button>(RESOURCE_DIR"/Button_Start.png");
            m_start->SetPosition({-1.5f, -180.f});

            m_start->SetZIndex(50);
            m_Root.AddChild(m_start);
        break;
        case Phase::LEVEL_SELECT:
            for (int i = 0; i < 10; i++) {
                std::shared_ptr<Button> m_button = std::make_shared<Button>(RESOURCE_DIR"/Level/level" + std::to_string(i + 1) + ".png");
                m_button ->SetPosition({-300.f+50*i, -180.f});
            }

        break;
    }
}
//         case Phase::ABLE_TO_MOVE:
//             if (isInsideTheSquare(*m_Giraffe)) {
//                 m_Phase = Phase::COLLIDE_DETECTION;
//                 m_Giraffe->SetPosition({-112.5f, -140.5f});
//                 m_Chest->SetVisible(true);
//
//                 m_PRM->NextPhase();
//             } else {
//                 LOG_DEBUG("The giraffe is not inside the square");
//             }
//             break;
//
//         case Phase::COLLIDE_DETECTION:
//             if (m_Giraffe->IfCollides(m_Chest)) {
//                 if (m_Chest->GetVisibility()) {
//                     LOG_DEBUG("The giraffe collided with the chest but the chest is still visible");
//                 } else {
//                     m_Phase = Phase::BEE_ANIMATION;
//                     m_Giraffe->SetVisible(false);
//                     m_Bee->SetVisible(true);
//
//                     m_PRM->NextPhase();
//                 }
//             } else {
//                 LOG_DEBUG("The giraffe is not colliding with the chest");
//             }
//             break;
//     }
// }
