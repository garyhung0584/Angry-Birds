#include "AppUtil.hpp"
#include "App.hpp"
#include "Util/Color.hpp"

#include "Util/Logger.hpp"

void App::PhaseManager() {
    switch (m_Phase) {
        case MAIN_MENU:
            m_Start = std::make_shared<Button>(RESOURCE_DIR"/Button_Start.png");
            m_Start->SetPosition({-1.5f, -180.f});
            m_Start->SetZIndex(50);

            m_Root.AddChild(m_Start);
            break;
        case LEVEL_SELECT:
            m_Root.RemoveChild(m_Start);
            if (m_Buttons.empty()) {
                for (int i = 0; i < 10; i++) {
                    m_Buttons.push_back(
                        std::make_shared<Button>(RESOURCE_DIR"/Level/level" + std::to_string(i + 1) + ".png"));
                    m_Buttons[i]->SetPosition({-400.f + 200 * (i % 5), 120.f - 250 * (i / 5)});
                    m_Root.AddChild(m_Buttons[i]);
                }
            } else {
                for (const std::shared_ptr<Button> &button: m_Buttons) {
                    m_Root.AddChild(button);
                }
            }
            break;
        case LEVEL_1: {
            m_slingshot = std::make_shared<Slingshot>(glm::vec2(-450.f, -140.f));
            m_Root.AddChildren(m_slingshot->GetSlingshot());

            m_PE = std::make_shared<PhysicsEngine>(&m_Root);

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            for (int i = 0; i < 3; i++) {
                m_PE->CreateStructure({4.f + i * 2.f, 0.2f}, STONE, BAR_SHORT, RAD90);
                m_PE->CreateStructure({4.f + i * 2.f, 1.f}, WOOD, BAR_SHORT, 0);
                m_PE->CreatePig({4.f + i * 2.f, 2.f}, NORMAL);
            }

            // if (m_PE->Gameover()) {
            //     m_PE->DestroyWorld();
            // }

            break;
        }
        case LEVEL_2:
            m_slingshot = std::make_shared<Slingshot>(glm::vec2(-450.f, -140.f));
            m_Root.AddChildren(m_slingshot->GetSlingshot());

            m_PE = std::make_shared<PhysicsEngine>(&m_Root);

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            m_PE->CreateStructure({6.6f, 0.2f}, STONE, BAR_SHORT, RAD90);
            m_PE->CreateStructure({5.4f, 0.2f}, STONE, BAR_SHORT, RAD90);
            m_PE->CreateStructure({6.0f, 1.0f}, STONE, BAR, 0);

            m_PE->CreateStructure({7.0f, 0.2f}, WOOD, BAR_SHORT, RAD90);
            m_PE->CreateStructure({5.0f, 0.2f}, WOOD, BAR_SHORT, RAD90);

            m_PE->CreateStructure({6.7f, 1.5f}, WOOD, BAR_SHORT, -RAD45);
            m_PE->CreateStructure({5.3f, 1.5f}, WOOD, BAR_SHORT, RAD45);
            m_PE->CreateStructure({6.0f, 1.2f}, WOOD, RECTANGLE, 0);

            m_PE->CreatePig({6.0f, 0.1f}, NORMAL);
            break;
        case LEVEL_3:
            break;
        case LEVEL_4:
            break;
        case LEVEL_5:
            break;
        case LEVEL_6:
            break;
        case LEVEL_7:
            break;
        case LEVEL_8:
            break;
        case LEVEL_9:
            break;
        case LEVEL_10:
            break;
    }
}
