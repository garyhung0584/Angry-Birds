#ifndef BIRDS_HPP
#define BIRDS_HPP

#include <string>
#include "Physics2D.hpp"


class Birds : public Physics2D {
public:
    Birds(const std::string &birdType) : Physics2D(RESOURCE_DIR"/Birds/" + birdType + ".png", 1, BIRD) {
    }

    void init(const glm::vec2 position, glm::vec2 size) {
        SetPosition(position);
    }
    virtual void Ability() = 0;

private:
    static const std::string m_birdType;
    static const std::string birdImagePath;
    static const std::string birdSoundPath;
};


#endif //BIRDS_HPP
