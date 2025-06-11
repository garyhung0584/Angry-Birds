#include "BlackBird.hpp"
#include "Util/Logger.hpp"

BlackBird::BlackBird() : Birds("BlackBird") {
    SetDensity(0.1f);
    SetFriction(0.3f);
    SetCenter({0.0f, 0.0f});
    SetRadius(0.2f);
}

void BlackBird::Ability() {
    LOG_DEBUG("BlackBird Ability");
    const b2BodyId bodyId = GetBodyId();

    if (B2_IS_NULL(bodyId)) {
        LOG_ERROR("BlackBird body is null");
        return;
    }

    constexpr float explosionRadius = 2.3f;
    constexpr float impulse = 0.03f;

    const b2Vec2 birdPosition = b2Body_GetPosition(bodyId);

    const b2WorldId worldId = GetWorldId();

    b2World_Explode(worldId, birdPosition, explosionRadius, impulse);
}
