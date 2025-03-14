#ifndef BACKGROUNDIMAGE_HPP
#define BACKGROUNDIMAGE_HPP


#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class BackgroundImage : public Util::GameObject {

public:
    BackgroundImage() : GameObject(
            std::make_unique<Util::Image>(RESOURCE_DIR"/Background/MAIN_MENU.png"), -10) {
    }

    void SetPhase(const int phase) {
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        temp->SetImage(ImagePath(phase));
    }



private:
    inline std::string ImagePath(const int phase) {
        return RESOURCE_DIR"/Background/level" + std::to_string(phase) + ".png";
    }
};


#endif //BACKGROUNDIMAGE_HPP
