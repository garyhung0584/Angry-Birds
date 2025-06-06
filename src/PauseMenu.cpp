#include "PauseMenu.hpp"
#include "Util/Image.hpp"


PauseMenu::PauseMenu(const std::string& ImagePath) {
    SetImage(ImagePath);

    ResetPosition();
}

void PauseMenu::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}
