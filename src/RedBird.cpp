#include "RedBird.hpp"
#include "Util/Logger.hpp"

RedBird::RedBird() : Birds("RedBird") {
    SetCenter({0.0f, -0.01f});
    SetDensity(0.1f);
    SetFriction(0.3f);
    SetRadius(0.2f);
    SetScale(0.15f);
}

void RedBird::Ability() {
    LOG_DEBUG("RedBird Ability");
}
