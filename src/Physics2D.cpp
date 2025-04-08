#include "Physics2D.hpp"

#include "Util/Image.hpp"

Physics2D::Physics2D(const std::string &ImagePath, const int health, const EntityType entityType) {
    SetImage(ImagePath);

    m_Health = health;
    m_EntityType = entityType;

    ResetPosition();
}

void Physics2D::SetImage(const std::string &ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}