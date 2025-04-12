#include "AppUtil.hpp"
#include "App.hpp"
#include "Util/Color.hpp"

#include "Util/Logger.hpp"

void App::PhaseManager() {
    switch (m_Phase) {
        case MAIN_MENU:
            m_Start = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_START.png");
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
            m_Restart = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_RESTART.png");
            m_Restart->SetPosition({-400.0f, 250.0f});
            m_Restart->SetZIndex(50);
            m_Root.AddChild(m_Restart);
            m_slingshot = std::make_shared<Slingshot>(glm::vec2(-450.f, -140.f));
            m_Root.AddChildren(m_slingshot->GetSlingshot());

            m_PE = std::make_shared<PhysicsEngine>(&m_Root);

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            for (int i = 0; i < 3; i++) {
                m_PE->CreateStructure({4.f + i * 2.f, 0.4f}, STONE, BAR_SHORT, RAD90);
                m_PE->CreateStructure({4.f + i * 2.f, 1.f}, WOOD, BAR_SHORT, 0);
                m_PE->CreatePig({4.f + i * 2.f, 1.5f}, NORMAL);
            }
            m_PE->SetUpWorld();

            break;
        }
        case LEVEL_2:
            m_Restart = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_RESTART.png");
            m_Restart->SetPosition({-400.0f, 250.0f});
            m_Restart->SetZIndex(50);
            m_Root.AddChild(m_Restart);
            m_slingshot = std::make_shared<Slingshot>(glm::vec2(-450.f, -140.f));
            m_Root.AddChildren(m_slingshot->GetSlingshot());

            m_PE = std::make_shared<PhysicsEngine>(&m_Root);

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            m_PE->CreateStructure({6.6f, 0.4f}, STONE, BAR_SHORT, RAD90);
            m_PE->CreateStructure({5.4f, 0.4f}, STONE, BAR_SHORT, RAD90);
            m_PE->CreateStructure({6.0f, 0.9f}, STONE, BAR, 0);

            m_PE->CreateStructure({7.0f, 0.4f}, WOOD, BAR_SHORT, RAD90);
            m_PE->CreateStructure({5.0f, 0.4f}, WOOD, BAR_SHORT, RAD90);

            m_PE->CreateStructure({5.25f, 1.15f}, WOOD, BAR_SHORT, RAD45);
            m_PE->CreateStructure({6.75f, 1.15f}, WOOD, BAR_SHORT, -RAD45);
            m_PE->CreateStructure({6.0f, 1.2f}, WOOD, RECTANGLE, 0);

            m_PE->CreateStructure({4.7f, 1.0f}, GLASS, BAR_LONG, RAD90);
            m_PE->CreateStructure({7.3f, 1.0f}, GLASS, BAR_LONG, RAD90);
            m_PE->CreateStructure({5.5f, 2.8f}, GLASS, BAR_LONG, RAD45);
            m_PE->CreateStructure({6.5f, 3.0f}, GLASS, BAR_LONG, -RAD45);
            m_PE->CreateStructure({6.0f, 1.8f}, GLASS, BAR_SHORT, RAD90);

            m_PE->CreatePig({6.0f, 0.1f}, NORMAL);

            m_PE->SetUpWorld();
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
