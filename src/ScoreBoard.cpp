#include "ScoreBoard.hpp"
#include "Util/Image.hpp"


ScoreBoard::ScoreBoard(const std::string& ImagePath) {
    SetImage(ImagePath);
}

void ScoreBoard::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

// void ScoreBoard::SetScore(int score) {
//     // for (int i = 0; i < score.size(); ++i) {
//     //     auto scoreStr = std::to_string(score);
//     //     auto score = std::make_shared<Util::GameObject>(std::to_string(score[i]), 20, Util::Color::WHITE);
//     //     m_Scores.push_back(score);
//     // }
// }

void ScoreBoard::UpdateScore() {

}