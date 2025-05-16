#include "YellowBird.hpp"
#include "Util/Logger.hpp"

// const std::string YellowBird::m_birdType = "YellowBird";
// const std::string RedBird::birdImagePath = RESOURCE_DIR"/Birds/RedBird.png";
// const std::string RedBird::birdSoundPath = RESOURCE_DIR"/Sounds/RedBird.wav";

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

    float force = 10.0f;
    b2Vec2 speedBoost = b2Vec2{
        force * cos(rotation),
        force * sin(rotation)
    };

    b2Body_ApplyForceToCenter(bodyId, speedBoost, true);
}
