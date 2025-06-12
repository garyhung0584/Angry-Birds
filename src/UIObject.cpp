#include "UIObject.hpp"
#include "Util/Image.hpp"

UIObject::UIObject(const std::string &ImagePath) {
    SetImage(ImagePath);
    this->SetZIndex(10);
    ResetPosition();
}

void UIObject::SetImage(const std::string &ImagePath) {
    m_Drawable = std::make_shared<Util::Image>(ImagePath);
}
