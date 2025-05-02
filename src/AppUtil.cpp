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
            isPause = false;
            m_Restart = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_RESTART.png");
            m_Restart->SetPosition({-400.0f, 250.0f});
            m_Restart->SetZIndex(50);
            m_Root.AddChild(m_Restart);
            m_Pause = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_PAUSE.png");
            m_Pause->SetPosition({-550.0f, 250.0f});
            m_Pause->SetZIndex(50);
            m_Root.AddChild(m_Pause);
            m_Quit = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_QUIT.png");
            m_Quit->SetPosition({550.0f, 250.0f});
            m_Quit->SetZIndex(50);
            m_Root.AddChild(m_Quit);
            m_slingshot = std::make_shared<Slingshot>(glm::vec2(-450.f, -135.f));
            m_Root.AddChildren(m_slingshot->GetSlingshot());

            m_PE = std::make_shared<PhysicsEngine>(&m_Root);

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            for (int i = 0; i < 3; i++) {
                m_PE->CreateStructure({4.f + i * 2.f, 0.4f}, STONE, BAR_SHORT, RAD90);
                m_PE->CreateStructure({4.f + i * 2.f, 1.f}, WOOD, BAR_SHORT, 0);
                m_PE->CreatePig({4.0f + i * 2.f, 1.3f}, NORMAL);
            }
            m_PE->SetUpWorld();

            break;
        }
        case LEVEL_2:
            isPause = false;
            m_Restart = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_RESTART.png");
            m_Restart->SetPosition({-400.0f, 250.0f});
            m_Restart->SetZIndex(50);
            m_Root.AddChild(m_Restart);
            m_Pause = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_PAUSE.png");
            m_Pause->SetPosition({-550.0f, 250.0f});
            m_Pause->SetZIndex(50);
            m_Root.AddChild(m_Pause);
            m_Quit = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_QUIT.png");
            m_Quit->SetPosition({550.0f, 250.0f});
            m_Quit->SetZIndex(50);
            m_Root.AddChild(m_Quit);
            m_slingshot = std::make_shared<Slingshot>(glm::vec2(-450.f, -135.f));
            m_Root.AddChildren(m_slingshot->GetSlingshot());

            m_PE = std::make_shared<PhysicsEngine>(&m_Root);

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            m_PE->CreateStructure({6.7f, 0.4f}, STONE, BAR_SHORT, RAD90);
            m_PE->CreateStructure({5.3f, 0.4f}, STONE, BAR_SHORT, RAD90);
            m_PE->CreateStructure({6.0f, 0.9f}, STONE, BAR, 0);

            m_PE->CreateStructure({7.1f, 0.4f}, WOOD, BAR_SHORT, RAD90);
            m_PE->CreateStructure({4.9f, 0.4f}, WOOD, BAR_SHORT, RAD90);

            m_PE->CreateStructure({5.22f, 1.15f}, WOOD, BAR_SHORT, RAD45);
            m_PE->CreateStructure({6.78f, 1.15f}, WOOD, BAR_SHORT, -RAD45);
            m_PE->CreateStructure({6.0f, 1.2f}, WOOD, RECTANGLE, 0);

            m_PE->CreateStructure({4.4f, 0.9f}, GLASS, BAR_LONG, RAD90);
            m_PE->CreateStructure({7.5f, 0.9f}, GLASS, BAR_LONG, RAD90);
            m_PE->CreateStructure({5.15f, 2.4f}, GLASS, BAR_LONG, RAD35);
            m_PE->CreateStructure({6.85f, 2.4f}, GLASS, BAR_LONG, -RAD35);
            m_PE->CreateStructure({6.0f, 2.2f}, GLASS, BAR, RAD90);

            m_PE->CreatePig({6.0f, 0.1f}, NORMAL);

            m_PE->SetUpWorld();
            break;
        case LEVEL_3:
            isPause = false;
            m_Restart = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_RESTART.png");
            m_Restart->SetPosition({-400.0f, 250.0f});
            m_Restart->SetZIndex(50);
            m_Root.AddChild(m_Restart);
            m_Pause = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_PAUSE.png");
            m_Pause->SetPosition({-550.0f, 250.0f});
            m_Pause->SetZIndex(50);
            m_Root.AddChild(m_Pause);
            m_Quit = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_QUIT.png");
            m_Quit->SetPosition({550.0f, 250.0f});
            m_Quit->SetZIndex(50);
            m_Root.AddChild(m_Quit);
            m_slingshot = std::make_shared<Slingshot>(glm::vec2(-450.f, -135.f));
            m_Root.AddChildren(m_slingshot->GetSlingshot());

            m_PE = std::make_shared<PhysicsEngine>(&m_Root);

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            for(int i=0; i<2; i++){
                m_PE->CreateStructure({4.0f + i * 3.0f, 0.2f}, STONE, RECTANGLE, 0);
                m_PE->CreateStructure({4.8f + i * 3.0f, 0.2f}, STONE, RECTANGLE, 0);
                m_PE->CreateStructure({4.4f + i * 3.0f, 0.5f}, STONE, BAR, 0);
                m_PE->CreateStructure({3.8f + i * 3.0f, 1.0f}, GLASS, RECTANGLE, RAD90);
                m_PE->CreateStructure({5.0f + i * 3.0f, 1.0f}, GLASS, RECTANGLE, RAD90);
                m_PE->CreateStructure({4.4f + i * 3.0f, 1.5f}, GLASS, BAR, 0);
                m_PE->CreateStructure({3.8f + i * 3.0f, 1.8f}, WOOD, BLOCK, 0);
                m_PE->CreateStructure({4.4f + i * 3.0f, 1.8f}, WOOD, BLOCK, 0);
                m_PE->CreateStructure({5.0f + i * 3.0f, 1.8f}, WOOD, BLOCK, 0);

                m_PE->CreatePig({4.4f + i * 3.0f, 1.0f}, NORMAL);
            }
            m_PE->SetUpWorld();
            break;
        case LEVEL_4:
            isPause = false;
            m_Restart = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_RESTART.png");
            m_Restart->SetPosition({-400.0f, 250.0f});
            m_Restart->SetZIndex(50);
            m_Root.AddChild(m_Restart);
            m_Pause = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_PAUSE.png");
            m_Pause->SetPosition({-550.0f, 250.0f});
            m_Pause->SetZIndex(50);
            m_Root.AddChild(m_Pause);
            m_Quit = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_QUIT.png");
            m_Quit->SetPosition({550.0f, 250.0f});
            m_Quit->SetZIndex(50);
            m_Root.AddChild(m_Quit);
            m_slingshot = std::make_shared<Slingshot>(glm::vec2(-450.f, -135.f));
            m_Root.AddChildren(m_slingshot->GetSlingshot());

            m_PE = std::make_shared<PhysicsEngine>(&m_Root);

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            m_PE->CreateStructure({5.0f, 0.4f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({6.1f, 0.4f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({5.6f, 0.9f}, WOOD, BAR, 0);
            m_PE->CreateStructure({6.7f, 0.4f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({7.8f, 0.4f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({7.2f, 0.9f}, WOOD, BAR, 0);
            m_PE->CreatePig({6.4f, 1.2f}, NORMAL);

            m_PE->CreateStructure({5.3f, 1.2f}, GLASS, RECTANGLE, 0);
            m_PE->CreateStructure({5.9f, 1.4f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({5.1f, 1.8f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({5.5f, 1.6f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({5.7f, 2.0f}, GLASS, RECTANGLE, 0);

            m_PE->CreateStructure({6.9f, 1.4f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({7.5f, 1.2f}, GLASS, RECTANGLE, 0);
            m_PE->CreateStructure({7.3f, 1.6f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({7.7f, 1.8f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({7.1f, 2.0f}, GLASS, RECTANGLE, 0);

            m_PE->CreateStructure({6.4f, 2.3f}, WOOD, BAR, 0);
            m_PE->CreateStructure({5.0f, 2.3f}, WOOD, RECTANGLE_SMALL, 0);
            m_PE->CreateStructure({5.4f, 2.3f}, WOOD, RECTANGLE_SMALL, 0);
            m_PE->CreateStructure({7.4f, 2.3f}, WOOD, RECTANGLE_SMALL, 0);
            m_PE->CreateStructure({7.8f, 2.3f}, WOOD, RECTANGLE_SMALL, 0);

            m_PE->CreatePig({5.2f, 2.6f}, NORMAL);
            m_PE->CreatePig({7.6f, 2.6f}, NORMAL);

            m_PE->CreateStructure({6.0f, 2.8f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({6.6f, 2.6f}, GLASS, RECTANGLE, 0);
            m_PE->CreateStructure({6.4f, 3.0f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({6.8f, 3.2f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({6.2f, 3.4f}, GLASS, RECTANGLE, 0);
            m_PE->CreateStructure({5.9f, 3.7f}, GLASS, BLOCK_SMALL, 0);
            m_PE->CreateStructure({6.4f, 3.7f}, GLASS, BLOCK_SMALL, 0);
            m_PE->CreateStructure({6.9f, 3.7f}, GLASS, BLOCK_SMALL, 0);
            m_PE->SetUpWorld();
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
