#ifndef BIRDS_HPP
#define BIRDS_HPP

#include <string>
#include "Physics2D.hpp"


class Birds : public Physics2D {
public:
    Birds(const std::string &birdType) : Physics2D(RESOURCE_DIR"/Birds/" + birdType + ".png") {
    }

    // void init(glm::vec2 position, glm::vec2 size) {
    // }
};


#endif //BIRDS_HPP
