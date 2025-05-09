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

void BlackBird::Ability() {
    LOG_DEBUG("BlackBird Ability");
}
