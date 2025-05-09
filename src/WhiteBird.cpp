#include "WhiteBird.hpp"
#include "Util/Logger.hpp"

// const std::string RedBird::m_birdType = "WhiteBird";
// const std::string RedBird::birdImagePath = RESOURCE_DIR"/Birds/RedBird.png";
// const std::string RedBird::birdSoundPath = RESOURCE_DIR"/Sounds/RedBird.wav";

WhiteBird::WhiteBird() : Birds("WhiteBird") {
    // Any additional RedBird initialization here
}

void WhiteBird::Ability() {
    LOG_DEBUG("WhiteBird Ability");
}
