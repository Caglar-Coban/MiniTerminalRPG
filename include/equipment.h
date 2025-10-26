#ifndef EQUIPMENT_H
#define EQUIPMENT_H

/**
 * @brief Defines unique identifiers for all weapon types.
 *
 */
typedef enum {
    WEAPON_RUSTY_DAGGER,
    WEAPON_SHORT_SWORD,
    WEAPON_IRON_SWORD,
    WEAPON_STEEL_LONGSWORD,
    WEAPON_COUNT 
} WeaponID;

/**
 * @brief Defines unique identifiers for all armor types.
 *
 */
typedef enum {
    ARMOR_RAGS,
    ARMOR_LEATHER_VEST,
    ARMOR_CHAINMAIL,
    ARMOR_PLATE_ARMOR,
    ARMOR_COUNT 
} ArmorID;

/**
 * @brief Data structure representing a Weapon.
 *
 */
typedef struct {
    WeaponID id;
    const char* name;
    int strength_boost;
    int cost; 
} Weapon;

/**
 * @brief Data structure representing an Armor.
 *
 */
typedef struct {
    ArmorID id;
    const char* name;
    int hp_boost;
    int cost; 
} Armor;

/**
 * @brief Retrieves the static (read-only) data for a weapon based on its ID.
 *
 * @param id The WeaponID of the weapon to retrieve.
 * @return const Weapon* A read-only pointer to the Weapon struct containing the data for the requested ID.
 */
const Weapon* getWeaponData(WeaponID id);

/**
 * @brief Retrieves the static (read-only) data for an armor based on its ID.
 *
 *
 * @param id The ArmorID of the armor to retrieve.
 * @return const Armor* A read-only pointer to the Armor struct containing the data for the requested ID.
 */
const Armor* getArmorData(ArmorID id);

#endif // EQUIPMENT_H