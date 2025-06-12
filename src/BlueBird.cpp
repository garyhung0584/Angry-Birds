#include "BlueBird.hpp"
#include "Util/Logger.hpp"

BlueBird::BlueBird() : Birds("BlueBird") {
    SetDensity(0.1f);
    SetFriction(0.3f);
    SetCenter({0.0f, 0.0f});
    SetRadius(0.2f);
}

void BlueBird::Ability() {
    LOG_DEBUG("BlueBird Ability");
}
