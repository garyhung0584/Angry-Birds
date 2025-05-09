#include "BlueBird.hpp"
#include "BlackBird.hpp"
#include "Util/Logger.hpp"

// const std::string RedBird::m_birdType = "BlueBird";
// const std::string RedBird::birdImagePath = RESOURCE_DIR"/Birds/RedBird.png";
// const std::string RedBird::birdSoundPath = RESOURCE_DIR"/Sounds/RedBird.wav";

BlueBird::BlueBird() : Birds("BlueBird") {
    // Any additional RedBird initialization here
}

void BlueBird::Ability() {
    LOG_DEBUG("BlueBird Ability");
}
