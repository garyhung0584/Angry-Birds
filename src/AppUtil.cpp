#include "AppUtil.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"

/**
 * @brief The function to validate the tasks.
 * @warning Do not modify this function.
 * @note See README.md for the task details.
 */
void App::PhaseManager() {
    switch (m_Phase) {
        case Phase::MAIN_MENU:

            m_start = std::make_shared<Button>(RESOURCE_DIR"/Button_Start.png");
            m_start->SetPosition({-1.5f, -180.f});

            m_start->SetZIndex(50);
            m_Root.AddChild(m_start);

            break;
        case Phase::LEVEL_SELECT:
            m_Root.RemoveChild(m_start);
            if (m_buttons.empty()) {
                for (int i = 0; i < 10; i++) {
                    m_buttons.push_back(
                        std::make_shared<Button>(RESOURCE_DIR"/Level/level" + std::to_string(i + 1) + ".png"));
                    m_buttons[i]->SetPosition({-400.f + 200 * (i % 5), 120.f - 250 * (i / 5)});
                    m_Root.AddChild(m_buttons[i]);
                }
            } else {
                for (const std::shared_ptr<Button> &button: m_buttons) {
                    m_Root.AddChild(button);
                }
            }
            break;
        case Phase::LEVEL_1: {
            m_slingshot = std::make_shared<Slingshot>(RESOURCE_DIR"/Slingshot/Slingshot1.png");
            m_slingshot->SetZIndex(5);
            m_slingshot->SetVisible(true);
            m_slingshot->SetPosition({-400.f, -150.f});
            m_Root.AddChild(m_slingshot);
            m_PE = std::make_shared<PhysicsEngine>();
            m_PE->CreateWorld();
            std::shared_ptr<Physics2D> m_bird = m_PE->CreateObject(RESOURCE_DIR"/Birds/RedBird.png",{-30.f, 8.f},{1.f, 1.f},1.6f);
            // m_PE->AddObject(m_bird);
            m_Root.AddChild(m_bird);
            // m_PE->RunWorld();
            break;
        }
        case Phase::LEVEL_2:
            break;
        case Phase::LEVEL_3:
            break;
        case Phase::LEVEL_4:
            break;
        case Phase::LEVEL_5:
            break;
        case Phase::LEVEL_6:
            break;
        case Phase::LEVEL_7:
            break;
        case Phase::LEVEL_8:
            break;
        case Phase::LEVEL_9:
            break;
        case Phase::LEVEL_10:
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
