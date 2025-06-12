#include "ScoreManager.hpp"

void ScoreManager::AddToHistory(const int level) {
    if (level < 2 || level - 2 >= static_cast<int>(m_history.size())) return;
    if (m_history[level-2] > m_Score) return;
    m_history[level-2] = m_Score;
}

void ScoreManager::UpdateScore() {
    auto score = m_Score;
    m_Scores.clear();
    const auto len = std::to_string(m_Score).length();
    for (int i = 0; i < len; i++) {
        const auto digit = score % 10;
        score /= 10;
        auto scoreObj = std::make_shared<UIObject>(RESOURCE_DIR"/GUI/" + std::to_string(digit) + ".png");
        scoreObj->SetPosition({m_Offset.x - 40.0f * static_cast<float>(i), m_Offset.y});
        scoreObj->SetScale(0.8f);
        scoreObj->SetZIndex(20); //in game UI:10, Physics2D: 4, slingshot: 3 & 5, popMenu 20, score 20
        m_Scores.push_back(scoreObj);
    }
}
