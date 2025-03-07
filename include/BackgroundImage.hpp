#ifndef BACKGROUNDIMAGE_HPP
#define BACKGROUNDIMAGE_HPP


#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class BackgroundImage : public Util::GameObject {

public:
    BackgroundImage() : GameObject(
            std::make_unique<Util::Image>(RESOURCE_DIR"/MAIN_MENU.png"), -10) {
    }



private:
    inline std::string ImagePath(const int phase) {
        return RESOURCE_DIR"/Image/Background/phase" + std::to_string(phase) + ".png";
    }
};


#endif //BACKGROUNDIMAGE_HPP
