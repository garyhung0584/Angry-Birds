#include "YellowBird.hpp"
#include "Util/Logger.hpp"

// const std::string YellowBird::m_birdType = "YellowBird";
// const std::string RedBird::birdImagePath = RESOURCE_DIR"/Birds/RedBird.png";
// const std::string RedBird::birdSoundPath = RESOURCE_DIR"/Sounds/RedBird.wav";

YellowBird::YellowBird() : Birds("YellowBird") {
    // Any additional RedBird initialization here
}

void YellowBird::Ability() {
    LOG_DEBUG("YellowBird Ability");
}

