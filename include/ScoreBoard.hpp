#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include "Util/GameObject.hpp"
#include "ScoreManager.hpp"

class ScoreBoard : public Util::GameObject {
public:
    explicit ScoreBoard(const std::string &ImagePath);

    ScoreBoard(const ScoreBoard &) = delete;

    ScoreBoard(ScoreBoard &&) = delete;

    ScoreBoard &operator=(const ScoreBoard &) = delete;

    ScoreBoard &operator=(ScoreBoard &&) = delete;

    void SetImage(const std::string &ImagePath);

    void SetScale(float Scale) { m_Transform.scale = {Scale, Scale}; }

    [[nodiscard]] const std::string &GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] glm::vec2 &GetPosition() { return m_Transform.translation; }

    [[nodiscard]] Util::Transform &GetTransform() { return m_Transform; }

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

    //void SetScore(int score);

    void UpdateScore();

    std::vector<std::shared_ptr<GameObject> > GetScore() const {
        return m_Scores;
    }

private:
    std::string m_ImagePath;
    int m_Score;

    std::vector<std::shared_ptr<GameObject> > m_Scores;
};
#endif //SCOREBOARD_HPP
