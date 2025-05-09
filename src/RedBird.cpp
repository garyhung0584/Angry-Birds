#include "RedBird.hpp"
#include "Util/Logger.hpp"

// const std::string RedBird::m_birdType = "BigBird";
// const std::string RedBird::birdImagePath = RESOURCE_DIR"/Birds/RedBird.png";
// const std::string RedBird::birdSoundPath = RESOURCE_DIR"/Sounds/RedBird.wav";

RedBird::RedBird() : Birds("RedBird") {
    SetDensity(0.1f);
    SetFriction(0.3f);
    SetCenter({0.0f, 0.0f});
    SetRadius(0.2f);
}

void RedBird::Ability() {
    LOG_DEBUG("RedBird Ability");
}
