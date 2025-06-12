#include "RedBird.hpp"
#include "Util/Logger.hpp"

RedBird::RedBird() : Birds("RedBird") {
    SetDensity(0.1f);
    SetFriction(0.3f);
    SetCenter({0.0f, 0.0f});
    SetRadius(0.2f);
}

void RedBird::Ability() {
    LOG_DEBUG("RedBird Ability");
}
