#include "YellowBird.hpp"
#include "Util/Logger.hpp"

YellowBird::YellowBird() : Birds("YellowBird") {
    SetDensity(0.1f);
    SetFriction(0.3f);
    SetCenter({0.0f, 0.0f});
    SetRadius(0.2f);
}

void YellowBird::Ability() {
    LOG_DEBUG("YellowBird Ability");
    b2BodyId bodyId = GetBodyId();

    auto rotation = GetTransform().rotation;

    float force = 5.0f;
    b2Vec2 speedBoost = b2Vec2{
        force * cos(rotation),
        force * sin(rotation)
    };

    b2Body_ApplyForceToCenter(bodyId, speedBoost, true);
}
