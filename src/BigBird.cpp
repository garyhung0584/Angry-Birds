#include "BigBird.hpp"
#include "Util/Logger.hpp"

BigBird::BigBird() : Birds("BigBird") {
    SetDensity(0.1f);
    SetFriction(0.3f);
    SetCenter({0.0f, 0.0f});
    SetRadius(0.2f);
}

void BigBird::Ability() {
    LOG_DEBUG("BigBird Ability");
}