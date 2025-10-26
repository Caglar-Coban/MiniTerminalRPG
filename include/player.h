#ifndef PLAYER_H
#define PLAYER_H
#include "inventory.h"
#include "equipment.h" 


/**
 * @brief Type of classes
 * 
 */
typedef enum {
    WARRIOR,
    MAGE,
    ROGUE
} PlayerClass;

/**
 * @brief Player Stats
 */
typedef struct Player {
    char name[50];
    PlayerClass p_class;
    int level;
    int hp;
    
    
    int base_max_hp;
    int base_strength;
    
    int experience;
    int exp_to_next_level;
    Inventory inventory;
    int gold;

    
    WeaponID equipped_weapon;
    ArmorID equipped_armor;
} Player;

/**
 * @brief Create a Player object
 * @return Player 
 */
Player createPlayer();

/**
 * @brief Displays Player Stats
 * 
 * @param player Current Player stats
 */
void displayPlayerStats(const Player* player);

/**
 * @brief Make Player'S gain experience
 * 
 * @param player Current Player
 * @param exp Amount Of Exp
 */
void gainExperience(Player* player, int exp);

/**
 * @brief Level Up The Player
 * 
 * @param player Current Player
 */
void levelUp(Player* player);

/**
 * Helper function to Get players total HP
 */
int getPlayerTotalMaxHP(const Player* player);

/**
 * @brief Get the Player Total Strength
 * 
 * @param player Current hp
 * @return int return total strength
 */
int getPlayerTotalStrength(const Player* player);

#endif // PLAYER_H