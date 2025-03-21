#include "Slingshot.hpp"
#include "Util/Image.hpp"


Slingshot::Slingshot(const std::string& ImagePath) {
    SetImage(ImagePath);

    ResetPosition();
}

void Slingshot::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

