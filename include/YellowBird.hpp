#ifndef YELLOWBIRD_HPP
#define YELLOWBIRD_HPP

#include "Birds.hpp"

class YellowBird : public Birds {
public:
    YellowBird();
    void Ability() override;
};

#endif //YELLOWBIRD_HPP