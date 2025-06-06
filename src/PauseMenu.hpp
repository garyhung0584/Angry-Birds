#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include "Util/GameObject.hpp"

class PauseMenu :public Util::GameObject{
public:
    explicit PauseMenu(const std::string& ImagePath);

    PauseMenu(const PauseMenu&) = delete;

    PauseMenu(PauseMenu&&) = delete;

    PauseMenu& operator=(const PauseMenu&) = delete;

    PauseMenu& operator=(PauseMenu&&) = delete;

    void SetImage(const std::string &ImagePath);
private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};



#endif //PAUSEMENU_HPP
