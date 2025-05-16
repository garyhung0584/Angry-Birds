#ifndef REDBIRD_HPP
#define REDBIRD_HPP

#include "Birds.hpp"

class RedBird : public Birds {
public:
    RedBird();

    void Ability() override;
};

#endif // REDBIRD_HPP
