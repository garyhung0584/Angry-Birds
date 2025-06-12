#include "BigBird.hpp"
#include "Util/Logger.hpp"

BigBird::BigBird() : Birds("BigBird") {
    SetCenter({0.0f, 0.0f});
    SetDensity(0.2f);
    SetFriction(0.3f);
    SetRadius(0.25f);
    SetScale(0.2f);
}

void BigBird::Ability() {
    LOG_DEBUG("BigBird Ability");
}