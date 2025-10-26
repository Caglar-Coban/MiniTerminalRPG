#include "../include/equipment.h"
#include <stddef.h>

/**
 * @brief All Weapons
 * 
 */
const Weapon all_weapons[WEAPON_COUNT] = {
    [WEAPON_RUSTY_DAGGER]    = {WEAPON_RUSTY_DAGGER, "Rusty Dagger", 2, 10},
    [WEAPON_SHORT_SWORD]     = {WEAPON_SHORT_SWORD, "Short Sword", 5, 50},
    [WEAPON_IRON_SWORD]      = {WEAPON_IRON_SWORD, "Iron Sword", 10, 120},
    [WEAPON_STEEL_LONGSWORD] = {WEAPON_STEEL_LONGSWORD, "Steel Longsword", 18, 250}
};

/**
 * @brief All Armors
 * 
 */
const Armor all_armors[ARMOR_COUNT] = {
    [ARMOR_RAGS]         = {ARMOR_RAGS, "Torn Rags", 5, 5},
    [ARMOR_LEATHER_VEST] = {ARMOR_LEATHER_VEST, "Leather Vest", 15, 40},
    [ARMOR_CHAINMAIL]    = {ARMOR_CHAINMAIL, "Chainmail", 30, 100},
    [ARMOR_PLATE_ARMOR]  = {ARMOR_PLATE_ARMOR, "Plate Armor", 50, 220}
};

/**
 * @brief helper function that gets weapon data
 * 
 * @param id  the weapon id
 * @return const Weapon* the weapon name
 */
const Weapon* getWeaponData(WeaponID id) {

    if (id >= 0 && id < WEAPON_COUNT) {

        return &all_weapons[id];
    }
    return NULL;
}

/**
 * @brief helper function that gets armor data
 * 
 * @param id  the armor id
 * @return const Armor* the armor name
 */
const Armor* getArmorData(ArmorID id) {

    if (id >= 0 && id < ARMOR_COUNT) {
        
        return &all_armors[id];
    }
    return NULL;
}