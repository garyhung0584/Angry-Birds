#include "Structure.hpp"



void Structure::ApplyDamage(int damage) {
    SetHealth(GetHealth() - damage);
    int health = GetHealth();
    if (health > m_MaxHealth*0.75f) {
        SetDamageLevel(NONE);
    } else if (health > m_MaxHealth*0.5f) {
        SetDamageLevel(LIGHT);
    } else if (health > m_MaxHealth*0.25f) {
        SetDamageLevel(MEDIUM);
    } else {
        SetDamageLevel(HEAVY);
    }
}

void Structure::SetDamageLevel(const DamageLevel damageLevel) {
    if (m_DamageLevel == damageLevel) {
        return;
    }
    static const std::unordered_map<StructureType, std::string> StructureString = {
        {FRAME_BLOCK, "A"},
        {FRAME_TRIANGLE, "B"},
        {TRIANGLE, "C"},
        {DISC, "D"},
        {BLOCK, "F"},
        {BAR_LONG, "G"},
        {RECTANGLE_SMALL, "H"},
        {BAR, "I"},
        {BLOCK_SMALL, "J"},
        {BAR_SHORT, "K"},
        {DISC_SMALL, "L"},
    };
    static const std::unordered_map<EntityType, std::string> EntityString = {
        {WOOD, "Wood"},
        {STONE, "Stone"},
        {GLASS, "Glass"},
    };

    const std::string &Structure = StructureString.at(m_StructureType);
    const std::string &entity = EntityString.at(GetEntityType());
    m_DamageLevel = damageLevel;
    switch (m_DamageLevel) {
        case NONE:
            SetImage(RESOURCE_DIR"/" + entity + "/" + entity + "_" + Structure + "1.png");
            break;
        case LIGHT:
            SetImage(RESOURCE_DIR"/" + entity + "/" + entity + "_" + Structure + "2.png");
            break;
        case MEDIUM:
            SetImage(RESOURCE_DIR"/" + entity + "/" + entity + "_" + Structure + "3.png");
            break;
        case HEAVY:
            SetImage(RESOURCE_DIR"/" + entity + "/" + entity + "_" + Structure + "4.png");
            break;
    }
}
