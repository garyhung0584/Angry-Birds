#include "RedBird.hpp"

const std::string RedBird::m_birdType = "RedBird";
const std::string RedBird::birdImagePath = RESOURCE_DIR"/Birds/RedBird.png";
const std::string RedBird::birdSoundPath = RESOURCE_DIR"/Sounds/RedBird.wav";

RedBird::RedBird() : Birds(m_birdType) {
    // Any additional RedBird initialization here
}
