#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP

#include "Util/Logger.hpp"

class ScoreManager {
public:
    ScoreManager() : m_Score(0), m_history(10, 0) {}

    void IncrementScore(int amount) { m_Score += amount; }

    int GetScore() const { return m_Score; }

    void ResetScore() { m_Score = 0; }

    int GetHistory(int level) const { return m_history[level-1]; }

    void AddToHistory(int level);

private:
    int m_Score;
    std::vector<int> m_history; // Store the highest 10 scores in each level
};

#endif //SCOREMANAGER_HPP
