#include "Physics2D.hpp"

#include "Util/Image.hpp"

Physics2D::Physics2D(const std::string &ImagePath, glm::vec2& position,  const glm::vec2& dimensions) {
    SetImage(ImagePath);

    // bodyDef.type = b2_dynamicBody;
    // bodyDef.position = b2Vec2{position.x, position.y};
    // bodyDef.position = b2Vec2{0.0f, 4.0f};
    // b2Polygon dynamicBox = b2MakeBox(dimensions.x, dimensions.y);
    // b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    // shapeDef.density = 1.0f;
    // shapeDef.friction = 0.3f;

    ResetPosition();
}

void Physics2D::SetImage(const std::string &ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}
