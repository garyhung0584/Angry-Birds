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
            m_PE = std::make_shared<PhysicsEngine>(&m_Root);
            m_slingshot = std::make_shared<Slingshot>(RESOURCE_DIR"/Slingshot/Slingshot.png");
            m_slingshot->SetZIndex(5);
            m_slingshot->SetVisible(true);
            m_slingshot->SetPosition({-450.f, -140.f});
            m_Root.AddChild(m_slingshot);
            std::shared_ptr<Slingshot> m_slingshot1 = std::make_shared<Slingshot>(RESOURCE_DIR"/Slingshot/Slingshot1.png");
            m_slingshot1->SetVisible(true);
            m_slingshot1->SetPosition({-450.f, -140.f});
            m_slingshot1->SetZIndex(0);
            m_Root.AddChild(m_slingshot1);


            m_PE->CreateBird(RED);
            m_PE->CreateBird(BIG);
            m_PE->CreatePig({5.f, 0.3f}, NORMAL);
            m_PE->CreateStructure({10.0f, 1.0f}, WOOD, BLOCK, 0);

            break;
        }
        case LEVEL_2:
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