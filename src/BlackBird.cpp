#include "BlackBird.hpp"
#include "Util/Logger.hpp"

// const std::string RedBird::m_birdType = "BlackBird";
// const std::string RedBird::birdImagePath = RESOURCE_DIR"/Birds/RedBird.png";
// const std::string RedBird::birdSoundPath = RESOURCE_DIR"/Sounds/RedBird.wav";

BlackBird::BlackBird() : Birds("BlackBird") {
    // Any additional RedBird initialization here
}

void BlackBird::Ability() {
    LOG_DEBUG("BlackBird Ability");
}
