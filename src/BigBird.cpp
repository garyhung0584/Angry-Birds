#include "BigBird.hpp"
#include "Util/Logger.hpp"

BigBird::BigBird() : Birds("BigBird") {
    // Any additional RedBird initialization here
}

void BigBird::Ability() {
    LOG_DEBUG("BigBird Ability");
}