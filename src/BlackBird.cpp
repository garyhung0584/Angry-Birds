#include "BlackBird.hpp"
#include "Util/Logger.hpp"

// const std::string RedBird::m_birdType = "BlackBird";
// const std::string RedBird::birdImagePath = RESOURCE_DIR"/Birds/RedBird.png";
// const std::string RedBird::birdSoundPath = RESOURCE_DIR"/Sounds/RedBird.wav";

BlackBird::BlackBird() : Birds("BlackBird") {
    SetDensity(0.1f);
    SetFriction(0.3f);
    SetCenter({0.0f, 0.0f});
    SetRadius(0.2f);
}

// void BlackBird::Ability() {
//     LOG_DEBUG("BlackBird Ability");
// }
void BlackBird::Ability() {
    LOG_DEBUG("BlackBird Ability");
    b2BodyId bodyId = GetBodyId();

    if (B2_IS_NULL(bodyId)) {
        LOG_ERROR("BlackBird body is null");
        return;
    }

    float explosionRadius = 2.0f;
    b2Vec2 birdPosition = b2Body_GetPosition(bodyId);

    b2WorldId worldId = GetWorldId();

    b2World_Explode(worldId, birdPosition, explosionRadius, 1.0f);
}
