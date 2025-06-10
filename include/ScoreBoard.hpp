#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include "Util/GameObject.hpp"
#include "ScoreManager.hpp"
#include "UIObject.hpp"

class ScoreBoard final : public UIObject {
public:
    explicit ScoreBoard(const std::string &ImagePath): UIObject(ImagePath), m_Score(0) {
    };

    void UpdateScore();

    void SetScore(const int score) { m_Score = score; };

    std::vector<std::shared_ptr<GameObject> > GetScoresObject() const {
        return m_Scores;
    }

private:
    int m_Score;

    std::vector<std::shared_ptr<GameObject> > m_Scores;
};
#endif //SCOREBOARD_HPP
