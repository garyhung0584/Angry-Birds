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

    int GetHistory(const int level) const { return m_history[level - 1]; }

    std::vector<int> GetHistory() const { return m_history; }

    void UpdateScore();

    void SetOffset(const glm::vec2 &offset) { m_Offset = offset; }

    std::vector<std::shared_ptr<Util::GameObject> > GetScoresObject() { return m_Scores; }

    void ResetScore() { m_Score = 0; }

private:
    void AddToHistory(int level);

    int m_Score;

    glm::vec2 m_Offset{};
    std::vector<int> m_history; // Store the highest 10 scores in each level
    std::vector<std::shared_ptr<Util::GameObject> > m_Scores;
};

#endif //SCOREMANAGER_HPP
