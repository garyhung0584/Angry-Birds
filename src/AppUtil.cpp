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
            SetUpGame();

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
            SetUpGame();

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

            m_PE->CreateStructure({4.5f, 0.9f}, GLASS, BAR_LONG, RAD90);
            m_PE->CreateStructure({7.5f, 0.9f}, GLASS, BAR_LONG, RAD90);
            m_PE->CreateStructure({5.15f, 2.35f}, GLASS, BAR_LONG, RAD35);
            m_PE->CreateStructure({6.85f, 2.35f}, GLASS, BAR_LONG, -RAD35);
            m_PE->CreateStructure({6.0f, 2.2f}, GLASS, BAR, RAD90);

            m_PE->CreatePig({6.0f, 0.1f}, NORMAL);

            m_PE->SetUpWorld();
            break;
        case LEVEL_3:
            SetUpGame();

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            for (int i = 0; i < 2; i++) {
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
            SetUpGame();

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
            SetUpGame();

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            m_PE->CreateStructure({5.0f, 0.2f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({5.8f, 0.2f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({7.6f, 0.2f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({8.4f, 0.2f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({6.7f, 0.5f}, WOOD, BAR, 0);
            for (int i = 0; i < 2; i++) {
                m_PE->CreateStructure({5.1f + 2.8f * i, 0.6f}, WOOD, RECTANGLE, 0);
                m_PE->CreateStructure({5.7f + 2.8f * i, 0.6f}, WOOD, BLOCK, 0);
                m_PE->CreateStructure({4.9f + 2.8f * i, 1.0f}, WOOD, BLOCK, 0);
                m_PE->CreateStructure({5.5f + 2.8f * i, 1.0f}, WOOD, RECTANGLE, 0);
                m_PE->CreateStructure({4.8f + 2.8f * i, 1.6f}, WOOD, BAR_SHORT, RAD90);
                m_PE->CreateStructure({5.8f + 2.8f * i, 1.6f}, WOOD, BAR_SHORT, RAD90);
                m_PE->CreateStructure({5.3f + 2.8f * i, 1.6f}, STONE, RECTANGLE, RAD90);
                m_PE->CreateStructure({5.3f + 2.8f * i, 2.1f}, WOOD, BAR, 0);
                m_PE->CreateStructure({4.7f + 2.8f * i, 2.6f}, WOOD, RECTANGLE, RAD90);
                m_PE->CreateStructure({5.9f + 2.8f * i, 2.6f}, WOOD, RECTANGLE, RAD90);
                m_PE->CreateStructure({5.3f + 2.8f * i, 3.1f}, WOOD, BAR, 0);
                m_PE->CreateStructure({5.0f + 2.8f * i, 2.3f}, GLASS, BLOCK_SMALL, 0);
                m_PE->CreateStructure({5.6f + 2.8f * i, 2.3f}, GLASS, BLOCK_SMALL, 0);
                m_PE->CreateStructure({5.3f + 2.8f * i, 3.4f}, GLASS, RECTANGLE, 0);
                m_PE->CreateStructure({5.3f + 2.8f * i, 4.0f}, GLASS, BAR_SHORT, RAD90);
            }
            m_PE->CreatePig({5.3f, 2.4f}, NORMAL);
            m_PE->CreatePig({8.1f, 2.4f}, NORMAL);
            m_PE->CreatePig({6.7f, 1.0f}, KING);
            m_PE->SetUpWorld();
            break;
        case LEVEL_6:
            SetUpGame();

            m_PE->CreateBird(BLACK);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            m_PE->CreateStructure({5.0f, 0.4f}, STONE, BAR_SHORT, RAD90);
            m_PE->CreateStructure({5.4f, 0.4f}, GLASS, BAR_SHORT, RAD90);
            m_PE->CreateStructure({5.8f, 0.4f}, WOOD, BAR_SHORT, RAD90);
            m_PE->CreateStructure({6.6f, 0.4f}, WOOD, BAR_SHORT, RAD90);
            m_PE->CreateStructure({7.4f, 0.4f}, WOOD, BAR_SHORT, RAD90);
            m_PE->CreateStructure({7.8f, 0.4f}, GLASS, BAR_SHORT, RAD90);
            m_PE->CreateStructure({8.2f, 0.4f}, STONE, BAR_SHORT, RAD90);
            m_PE->CreateStructure({5.4f, 0.9f}, WOOD, BAR_SHORT, 0);
            m_PE->CreateStructure({6.2f, 0.9f}, WOOD, BAR_SHORT, 0);
            m_PE->CreateStructure({7.0f, 0.9f}, WOOD, BAR_SHORT, 0);
            m_PE->CreateStructure({7.8f, 0.9f}, WOOD, BAR_SHORT, 0);

            m_PE->CreateStructure({5.4f, 1.4f}, GLASS, BAR_SHORT, RAD90);
            m_PE->CreateStructure({5.8f, 1.4f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({6.2f, 1.4f}, GLASS, BAR_SHORT, RAD90);
            m_PE->CreateStructure({7.0f, 1.4f}, GLASS, BAR_SHORT, RAD90);
            m_PE->CreateStructure({7.4f, 1.4f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({7.8f, 1.4f}, GLASS, BAR_SHORT, RAD90);
            m_PE->CreateStructure({5.8f, 1.9f}, GLASS, BAR_SHORT, 0);
            m_PE->CreateStructure({6.6f, 1.9f}, GLASS, BAR_SHORT, 0);
            m_PE->CreateStructure({7.4f, 1.9f}, GLASS, BAR_SHORT, 0);

            m_PE->CreateStructure({5.8f, 2.4f}, GLASS, BAR_SHORT, RAD90);
            m_PE->CreateStructure({6.2f, 2.2f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({6.6f, 2.4f}, GLASS, BAR_SHORT, RAD90);
            m_PE->CreateStructure({7.0f, 2.2f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({7.4f, 2.4f}, GLASS, BAR_SHORT, RAD90);
            m_PE->CreateStructure({6.2f, 2.9f}, GLASS, BAR_SHORT, 0);
            m_PE->CreateStructure({7.0f, 2.9f}, GLASS, BAR_SHORT, 0);

            m_PE->CreateStructure({6.2f, 3.4f}, GLASS, BAR_SHORT, RAD90);
            m_PE->CreateStructure({6.6f, 3.2f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({7.0f, 3.4f}, GLASS, BAR_SHORT, RAD90);
            m_PE->CreateStructure({6.6f, 3.9f}, GLASS, BAR_SHORT, 0);

            m_PE->CreatePig({6.2f, 0.4f}, NORMAL);
            m_PE->CreatePig({7.0f, 0.4f}, NORMAL);
            m_PE->CreatePig({6.6f, 1.3f}, NORMAL);

            m_PE->SetUpWorld();
            break;
        case LEVEL_7:
            SetUpGame();

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            m_PE->CreateStructure({5.0f, 0.4f}, WOOD, RECTANGLE, RAD90);
            m_PE->CreateStructure({5.4f, 0.4f}, WOOD, RECTANGLE, RAD90);
            m_PE->CreateStructure({6.4f, 0.4f}, WOOD, RECTANGLE, RAD90);
            m_PE->CreateStructure({7.4f, 0.4f}, WOOD, RECTANGLE, RAD90);
            m_PE->CreateStructure({7.8f, 0.4f}, WOOD, RECTANGLE, RAD90);

            m_PE->CreateStructure({5.2f, 1.0f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({7.6f, 1.0f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({6.4f, 0.9f}, WOOD, BAR, 0);
            m_PE->CreateStructure({6.4f, 1.1f}, WOOD, BAR, 0);
            m_PE->CreateStructure({5.6f, 1.3f}, WOOD, BAR, 0);
            m_PE->CreateStructure({7.2f, 1.3f}, WOOD, BAR, 0);

            m_PE->CreateStructure({5.0f, 1.6f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({5.0f, 2.0f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({6.3f, 1.8f}, WOOD, BAR_SHORT, RAD90);
            m_PE->CreateStructure({6.5f, 1.8f}, WOOD, BAR_SHORT, RAD90);
            m_PE->CreateStructure({7.8f, 1.6f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({7.8f, 2.0f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({5.6f, 2.3f}, WOOD, BAR, 0);
            m_PE->CreateStructure({7.2f, 2.3f}, WOOD, BAR, 0);
            m_PE->CreateStructure({5.6f, 2.5f}, WOOD, BAR, 0);
            m_PE->CreateStructure({7.2f, 2.5f}, WOOD, BAR, 0);

            m_PE->CreateStructure({5.0f, 2.8f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({5.7f, 2.8f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({6.4f, 2.8f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({7.1f, 2.8f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({7.8f, 2.8f}, WOOD, BLOCK, 0);

            m_PE->CreatePig({5.9f, 0.3f}, NORMAL);
            m_PE->CreatePig({6.9f, 0.3f}, NORMAL);
            m_PE->CreatePig({5.6f, 1.8f}, SOLDIER);
            m_PE->CreatePig({7.2f, 1.8f}, SOLDIER);

            m_PE->SetUpWorld();
            break;
        case LEVEL_8:
            SetUpGame();

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            m_PE->CreateStructure({5.0f, 0.4f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({5.6f, 0.4f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({6.6f, 0.4f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({7.2f, 0.4f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({8.2f, 0.4f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({8.8f, 0.4f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({5.3f, 1.0f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({6.9f, 1.0f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({8.5f, 1.0f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({6.1f, 1.3f}, STONE, BAR, 0);
            m_PE->CreateStructure({7.7f, 1.3f}, STONE, BAR, 0);
            m_PE->CreateStructure({5.4f, 2.2f}, WOOD, BAR, RAD90);
            m_PE->CreateStructure({5.6f, 2.2f}, WOOD, BAR, RAD90);
            m_PE->CreateStructure({6.7f, 2.2f}, WOOD, BAR, RAD90);
            m_PE->CreateStructure({6.9f, 2.2f}, WOOD, BAR, RAD90);
            m_PE->CreateStructure({7.1f, 2.2f}, WOOD, BAR, RAD90);
            m_PE->CreateStructure({8.2f, 2.2f}, WOOD, BAR, RAD90);
            m_PE->CreateStructure({8.4f, 2.2f}, WOOD, BAR, RAD90);
            m_PE->CreateStructure({6.2f, 1.6f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({7.6f, 1.6f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({6.1f, 3.1f}, WOOD, BAR, 0);
            m_PE->CreateStructure({7.7f, 3.1f}, WOOD, BAR, 0);
            m_PE->CreateStructure({5.5f, 3.4f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({6.4f, 3.4f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({7.4f, 3.4f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({8.3f, 3.4f}, WOOD, BLOCK, 0);

            m_PE->CreatePig({6.2f, 2.0f}, NORMAL);
            m_PE->CreatePig({7.6f, 2.0f}, NORMAL);

            m_PE->SetUpWorld();
            break;
        case LEVEL_9:
            SetUpGame();

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            m_PE->CreateStructure({5.5f, 0.4f}, WOOD, BAR_SHORT, RAD90);
            m_PE->CreateStructure({6.3f, 0.4f}, WOOD, BAR_SHORT, RAD90);
            m_PE->CreateStructure({4.9f, 0.2f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({6.9f, 0.2f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({5.0f, 0.6f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({6.8f, 0.6f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({5.4f, 0.9f}, WOOD, RECTANGLE_SMALL, 0);
            m_PE->CreateStructure({6.4f, 0.9f}, WOOD, RECTANGLE_SMALL, 0);
            m_PE->CreateStructure({4.9f, 1.0f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({6.9f, 1.0f}, WOOD, BLOCK, 0);
            m_PE->CreateStructure({5.9f, 1.1f}, WOOD, BAR, 0);
            m_PE->CreateStructure({5.1f, 1.4f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({6.7f, 1.4f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({5.9f, 1.4f}, WOOD, RECTANGLE_SMALL, RAD90);
            m_PE->CreateStructure({5.5f, 1.8f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({6.3f, 1.8f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({4.9f, 2.0f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({6.9f, 2.0f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({5.9f, 2.4f}, WOOD, RECTANGLE, RAD90);
            m_PE->CreateStructure({5.3f, 2.4f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({6.5f, 2.4f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({5.9f, 2.9f}, GLASS, BAR, 0);
            m_PE->CreateStructure({5.9f, 3.2f}, WOOD, RECTANGLE, 0);
            m_PE->CreateStructure({5.9f, 3.8f}, WOOD, RECTANGLE, RAD90);
            m_PE->CreateStructure({5.9f, 4.4f}, STONE, BLOCK, 0);
            m_PE->CreateStructure({5.2f, 3.8f}, GLASS, BAR, RAD90);
            m_PE->CreateStructure({6.6f, 3.8f}, GLASS, BAR, RAD90);
            m_PE->CreateStructure({5.9f, 4.7f}, GLASS, BAR, 0);
            m_PE->CreateStructure({5.3f, 5.0f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({5.9f, 5.0f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({6.5f, 5.0f}, GLASS, BLOCK, 0);

            m_PE->CreatePig({5.9f, 0.3f}, SOLDIER);

            m_PE->SetUpWorld();
            break;
        case LEVEL_10:
            SetUpGame();

            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);
            m_PE->CreateBird(RED);

            m_PE->CreateStructure({5.7f, 0.8f}, STONE, BAR, RAD90);
            m_PE->CreateStructure({6.5f, 0.8f}, STONE, BAR, RAD90);
            m_PE->CreateStructure({4.7f, 0.8f}, WOOD, BAR, RAD90);
            m_PE->CreateStructure({4.2f, 1.7f}, WOOD, BAR, 0);
            m_PE->CreateStructure({6.1f, 1.7f}, WOOD, BAR, 0);
            m_PE->CreateStructure({8.0f, 1.7f}, WOOD, BAR, 0);

            m_PE->CreateStructure({3.8f, 0.2f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({3.8f, 0.6f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({3.8f, 1.0f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({3.8f, 1.4f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({8.4f, 0.2f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({8.4f, 0.6f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({8.4f, 1.0f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({8.4f, 1.4f}, STONE, RECTANGLE, 0);

            m_PE->CreateStructure({5.0f, 1.9f}, WOOD, BAR, 0);
            m_PE->CreateStructure({7.2f, 1.9f}, WOOD, BAR, 0);
            m_PE->CreateStructure({6.1f, 2.1f}, WOOD, BAR, 0);
            m_PE->CreateStructure({5.2f, 2.4f}, WOOD, BAR_SHORT, RAD90);
            m_PE->CreateStructure({7.0f, 2.4f}, WOOD, BAR_SHORT, RAD90);
            m_PE->CreateStructure({3.6f, 2.2f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({4.0f, 2.2f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({8.2f, 2.2f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({8.6f, 2.2f}, STONE, RECTANGLE, RAD90);
            m_PE->CreateStructure({4.65f, 2.2f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({7.55f, 2.2f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({4.0f, 2.8f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({8.2f, 2.8f}, STONE, RECTANGLE, 0);
            m_PE->CreateStructure({4.2f, 3.2f}, STONE, BLOCK, 0);
            m_PE->CreateStructure({8.0f, 3.2f}, STONE, BLOCK, 0);

            m_PE->CreateStructure({5.5f, 2.4f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({5.9f, 2.4f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({6.3f, 2.4f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({6.7f, 2.4f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({5.5f, 2.8f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({6.1f, 2.8f}, GLASS, RECTANGLE, 0);
            m_PE->CreateStructure({6.7f, 2.8f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({5.5f, 3.2f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({5.9f, 3.2f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({6.3f, 3.2f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({6.7f, 3.2f}, GLASS, BLOCK, 0);
            m_PE->CreateStructure({6.1f, 3.6f}, GLASS, RECTANGLE, 0);
            m_PE->CreateStructure({5.5f, 3.8f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({6.7f, 3.8f}, GLASS, RECTANGLE, RAD90);
            m_PE->CreateStructure({6.1f, 4.2f}, GLASS, RECTANGLE, RAD90);

            m_PE->CreatePig({5.1f, 0.3f}, KING);
            m_PE->CreatePig({7.1f, 0.3f}, KING);

            m_PE->SetUpWorld();
            break;
    }
}

// Function to set up the in game UI, including buttons and slingshot, also to initialize the physics engine
void App::SetUpGame() {
    m_isPause = false;
    const auto btnRestart = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_RESTART.png");
    btnRestart->SetButtonType(RESTART_BUTTON);
    btnRestart->SetPosition({-400.0f, 250.0f});
    btnRestart->SetZIndex(10); //in game UI:10, Physics2D: 4, slingshot: 3 & 5, pauseMenu 50
    m_UIButtons.push_back(btnRestart);
    m_Root.AddChild(btnRestart);
    const auto btnPause = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_PAUSE.png");
    btnPause->SetButtonType(PAUSE_BUTTON);
    btnPause->SetPosition({-550.0f, 250.0f});
    btnPause->SetZIndex(10);
    m_UIButtons.push_back(btnPause);
    m_Root.AddChild(btnPause);
    const auto btnFastForward = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_NEXT.png");
    btnFastForward->SetButtonType(FASTFORWARD_BUTTON);
    btnFastForward->SetVisible(false);
    btnFastForward->SetPosition({550.0f, -260.0f});
    btnFastForward->SetZIndex(10);
    m_UIButtons.push_back(btnFastForward);
    m_Root.AddChild(btnFastForward);
    // For faster debug, remove on release
    const auto btnQuit = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_QUIT.png");
    btnQuit->SetButtonType(EXIT_BUTTON);
    btnQuit->SetPosition({550.0f, 150.0f});
    btnQuit->SetZIndex(10);
    m_UIButtons.push_back(btnQuit);
    m_Root.AddChild(btnQuit);
    // Until here
    m_Text_Score = std::make_shared<UIObject>(RESOURCE_DIR"/GUI/Score.png");
    m_Text_Score->SetPosition({250.f, 300.f});
    m_Text_Score->SetScale(0.5f);
    m_Text_Score->SetZIndex(10);
    m_Root.AddChild(m_Text_Score);
    m_slingshot = std::make_shared<Slingshot>(glm::vec2(-450.f, -135.f));
    m_Root.AddChildren(m_slingshot->GetSlingshot());
    m_Root.AddChildren(m_slingshot->GetWire());
    m_slingshot->Release(); // Release the slingshot to reset state

    m_ScoreManager->SetOffset({600.f, 300.f});
    m_ScoreManager->ResetScore();

    SetUpMenu();

    m_PE = std::make_shared<PhysicsEngine>(&m_Root, m_ScoreManager, m_isCheatMode);
}

void App::SetUpMenu() {
    const auto scoreBoard = std::make_shared<UIObject>(RESOURCE_DIR"/GUI/ScoreBoard.png");
    scoreBoard->SetPosition({0.f, 50.f});
    scoreBoard->SetZIndex(59);
    m_FinishMenu.push_back(scoreBoard);
    m_LostMenu.push_back(scoreBoard);
    m_PauseMenu.push_back(scoreBoard);
    m_Root.AddChild(scoreBoard);

    const auto textLevelClear = std::make_shared<UIObject>(RESOURCE_DIR"/GUI/LevelCleared.png");
    textLevelClear->SetPosition({-130.f, 140.f});
    textLevelClear->SetScale(0.5f);
    textLevelClear->SetZIndex(60);
    m_FinishMenu.push_back(textLevelClear);
    m_Root.AddChild(textLevelClear);

    const auto textScore = std::make_shared<UIObject>(RESOURCE_DIR"/GUI/Score.png");
    textScore->SetPosition({-250.f, 70.f});
    textScore->SetScale(0.5f);
    textScore->SetZIndex(60);
    m_FinishMenu.push_back(textScore);
    m_PauseMenu.push_back(textScore);
    m_Root.AddChild(textScore);

    const auto textLevelFailed = std::make_shared<UIObject>(RESOURCE_DIR"/GUI/LevelFailed.png");
    textLevelFailed->SetPosition({0, 50.f});
    textLevelFailed->SetZIndex(60);
    m_LostMenu.push_back(textLevelFailed);
    m_Root.AddChild(textLevelFailed);

    const auto btnMenu = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_MENU.png");
    btnMenu->SetButtonType(BACK_BUTTON);
    btnMenu->SetPosition({-200.0f, -125.0f});
    btnMenu->SetZIndex(70);
    m_FinishMenu.push_back(btnMenu);
    m_LostMenu.push_back(btnMenu);
    m_PauseMenu.push_back(btnMenu);
    m_UIButtons.push_back(btnMenu);
    m_Root.AddChild(btnMenu);

    const auto btnRestart = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_RESTART.png");
    btnRestart->SetButtonType(RESTART_BUTTON);
    btnRestart->SetPosition({0.0f, -125.0f});
    btnRestart->SetZIndex(70);
    m_FinishMenu.push_back(btnRestart);
    m_LostMenu.push_back(btnRestart);
    m_PauseMenu.push_back(btnRestart);
    m_UIButtons.push_back(btnRestart);
    m_Root.AddChild(btnRestart);

    const auto btnNext = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_NEXT.png");
    btnNext->SetButtonType(NEXT_BUTTON);
    btnNext->SetPosition({200.0f, -125.0f});
    btnNext->SetZIndex(70);
    m_FinishMenu.push_back(btnNext);
    m_UIButtons.push_back(btnNext);
    m_Root.AddChild(btnNext);

    const auto btnContinue = std::make_shared<Button>(RESOURCE_DIR"/BUTTON_START.png");
    btnContinue->SetButtonType(RESUME_BUTTON);
    btnContinue->SetPosition({200.0f, -125.0f});
    btnContinue->SetZIndex(70);
    m_PauseMenu.push_back(btnContinue);
    m_UIButtons.push_back(btnContinue);
    m_Root.AddChild(btnContinue);

    const auto btnCheatMode = std::make_shared<Button>(
        m_isCheatMode ? RESOURCE_DIR"/GUI/CheatTrue.png" : RESOURCE_DIR"/GUI/CheatFalse.png");
    btnCheatMode->SetButtonType(CHEAT_BUTTON);
    btnCheatMode->SetPosition({400.f, -300.f});
    btnCheatMode->SetSize({300, 80.0f});
    btnCheatMode->SetZIndex(70);
    m_PauseMenu.push_back(btnCheatMode);
    m_UIButtons.push_back(btnCheatMode);
    m_Root.AddChild(btnCheatMode);

    HideMenu(m_FinishMenu);
    HideMenu(m_PauseMenu);
    HideMenu(m_LostMenu);
}

void App::ExitLevel() {
    m_Root.RemoveChild(m_Text_Score);
    m_Root.RemoveChild(m_slingshot->GetSlingshot()[0]);
    m_Root.RemoveChild(m_slingshot->GetSlingshot()[1]);

    for (const auto &object: m_FinishMenu) {
        m_Root.RemoveChild(object);
    }
    for (const auto &object: m_LostMenu) {
        m_Root.RemoveChild(object);
    }
    for (const auto &object: m_PauseMenu) {
        m_Root.RemoveChild(object);
    }
    for (const auto &button: m_UIButtons) {
        m_Root.RemoveChild(button);
    }
    for (const auto &score: m_ScoreManager->GetScoresObject()) {
        m_Root.RemoveChild(score);
    }
    m_FinishMenu.clear();
    m_LostMenu.clear();
    m_PauseMenu.clear();
    m_UIButtons.clear();
    m_ScoreManager->ResetScore();
    m_ScoreManager->GetScoresObject().clear();
}

void App::ShowMenu(const std::vector<std::shared_ptr<Util::GameObject> > &menu) {
    for (const auto &object: menu) {
        object->SetVisible(true);
    }
}

void App::HideMenu(const std::vector<std::shared_ptr<Util::GameObject> > &menu) {
    for (const auto &object: menu) {
        object->SetVisible(false);
    }
}
