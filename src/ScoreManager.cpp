#include "ScoreManager.hpp"

void ScoreManager::AddToHistory(int level) {
    if (m_history[level-1] > m_Score) {}
    m_history[level-1] = m_Score;
}

void ScoreManager::UpdateScore() {
    auto score = m_Score;
    m_Scores.clear();
    const auto len = std::to_string(m_Score).length();
    for (int i = 0; i < len; i++) {
        const auto digit = score % 10;
        score /= 10;
        auto scoreObj = std::make_shared<UIObject>(RESOURCE_DIR"/GUI/" + std::to_string(digit) + ".png");
        scoreObj->SetPosition({0, 200.0f});
        scoreObj->SetZIndex(10);
        m_Scores.push_back(scoreObj);
    }

}
