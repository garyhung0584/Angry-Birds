#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP

#include "Util/Logger.hpp"
#include "UIObject.hpp"

class ScoreManager {
public:
    ScoreManager() : m_Score(0), m_history(10, 0) {
    }

    void AddScore(const int amount) { m_Score += amount; }


    int GetScore() const { return m_Score; }

    void ResetScore() { m_Score = 0; }

    int GetHistory(const int level) const { return m_history[level - 1]; }

    std::vector<int> GetHistory() const { return m_history; }

    void UpdateScore();

    std::vector<std::shared_ptr<Util::GameObject> > GetScoresObject() { return m_Scores; };

private:
    int m_Score;

    std::vector<std::shared_ptr<Util::GameObject> > m_Scores;

    void AddToHistory(int level);


    std::vector<int> m_history; // Store the highest 10 scores in each level
};

#endif //SCOREMANAGER_HPP
