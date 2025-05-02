#ifndef REDBIRD_HPP
#define REDBIRD_HPP

#include "Birds.hpp"

class RedBird : public Birds {
public:
    RedBird();
    // void Ability() override {
    // }


private:
    static const std::string m_birdType;
    static const std::string birdImagePath;
    static const std::string birdSoundPath;
};

#endif // REDBIRD_HPP
