#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP
#include "Physics2D.hpp"


class Structure : public Physics2D {
public:
    Structure(const std::string &ImagePath, int health, EntityType entityType, StructureType structureType) : Physics2D(ImagePath, health, entityType) {
        m_MaxHealth = health;
        m_StructureType = structureType;
        m_DamageLevel = NONE;
    }
    void ApplyDamage(int damage) override;

    void SetDamageLevel(DamageLevel damageLevel);
private:
    int m_MaxHealth;
    DamageLevel m_DamageLevel;
    StructureType m_StructureType;
};



#endif //STRUCTURE_HPP
