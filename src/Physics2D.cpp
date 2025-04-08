#include "Physics2D.hpp"

#include "Util/Image.hpp"

Physics2D::Physics2D(const std::string &ImagePath) {
    SetImage(ImagePath);

    ResetPosition();
}

void Physics2D::SetImage(const std::string &ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}