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

void Physics2D::ApplyForce(b2Vec2 force) {
    b2Body_ApplyForceToCenter(m_BodyId, force, true);

}
// void Physics2D::SetBodyId(b2BodyId bodyId) {
    // m_BodyId = bodyId;
    // Util::Transform transform = GetTransform();
    // transform.scale = {100, 100};
    // transform.translation = {b2Body_GetPosition(m_BodyId).x, b2Body_GetPosition(m_BodyId).y};
    // transform.rotation = b2Rot_GetAngle(b2Body_GetRotation(m_BodyId));

// }
// void Physics2D::Update() {

    // Util::Transform transform = GetTransform();
    // transform.scale = {100, 100};
    // transform.translation = {b2Body_GetPosition(m_BodyId).x, b2Body_GetPosition(m_BodyId).y};
    // transform.rotation = b2Rot_GetAngle(b2Body_GetRotation(m_BodyId));
// /
// }

