#include "WhiteBird.hpp"
#include "Util/Logger.hpp"

WhiteBird::WhiteBird() : Birds("WhiteBird") {
    SetDensity(0.1f);
    SetFriction(0.3f);
    SetCenter({0.0f, 0.0f});
    SetRadius(0.2f);
}

void WhiteBird::Ability() {
    LOG_DEBUG("WhiteBird Ability");
}
