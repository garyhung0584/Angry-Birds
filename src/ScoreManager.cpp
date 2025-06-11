#include "ScoreManager.hpp"

void ScoreManager::AddToHistory(const int level) {
    if (m_history[level-2] > m_Score) return; // Do not update if the current score is less than the history score
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
        scoreObj->SetPosition({m_Offset.x - 40.0f * i, m_Offset.y});
        scoreObj->SetScale(0.8f);
        scoreObj->SetZIndex(61); // Z-index for score objects
        m_Scores.push_back(scoreObj);
    }

}
