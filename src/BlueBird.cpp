#include "BlueBird.hpp"
#include "Util/Logger.hpp"

BlueBird::BlueBird() : Birds("BlueBird") {
    SetCenter({0.0f, 0.0f});
    SetDensity(0.1f);
    SetFriction(0.3f);
    SetRadius(0.2f);
    SetScale(0.2f);
}

void BlueBird::Ability() {
    LOG_DEBUG("BlueBird Ability");
}
