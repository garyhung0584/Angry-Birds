#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include "Util/GameObject.hpp"
#include "ScoreManager.hpp"

class ScoreBoard : public Util::GameObject{
public:
    explicit ScoreBoard(const std::string& ImagePath);

    ScoreBoard(const ScoreBoard&) = delete;

    ScoreBoard(ScoreBoard&&) = delete;

    ScoreBoard& operator=(const ScoreBoard&) = delete;

    ScoreBoard& operator=(ScoreBoard&&) = delete;

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

    //void SetScore(int score);

    void UpdateScore();
    std::vector<std::shared_ptr<GameObject>> GetScore() const {
        return m_Scores;
    }

private:

    std::string m_ImagePath;
    int m_Score;

    std::vector<std::shared_ptr<GameObject>> m_Scores;

};
#endif //SCOREBOARD_HPP
