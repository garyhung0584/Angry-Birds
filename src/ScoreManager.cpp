#include "ScoreManager.hpp"

void ScoreManager::AddToHistory(int level) {
    if (m_history[level-1] > m_Score) {}
    m_history[level-1] = m_Score;
}
