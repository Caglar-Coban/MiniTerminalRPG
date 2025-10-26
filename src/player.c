#include <stdio.h>
#include <string.h>
#include "../include/player.h"
#include "../include/utils.h"
#include "../include/inventory.h"
#include "../include/equipment.h"
#include "../include/language.h"

/**
 * @brief Get the Player Total Strength 
 * 
 * @param player Takes Current Player
 * @return int return's players strength
 */
int getPlayerTotalStrength(const Player* player) {
    const Weapon* weapon = getWeaponData(player->equipped_weapon);

    int weapon_bonus = weapon ? weapon->strength_boost : 0;

    return player->base_strength + weapon_bonus;
}

/**
 * @brief Get the Player Total Max HP
 * 
 * @param player Takes Current Player
 * @return int return's players health
 */
int getPlayerTotalMaxHP(const Player* player) {
    const Armor* armor = getArmorData(player->equipped_armor);
    int armor_bonus = armor ? armor->hp_boost : 0;

    return player->base_max_hp + armor_bonus;
}

/**
 * @brief Create a Player 
 * 
 * @return Player 
 */
Player createPlayer() {
    Player newPlayer;
    clearScreen();

    printf("===== %s =====\n", getString(STR_PLAYER_CREATION_TITLE));

    while (1) {

        printf("%s: ", getString(STR_ENTER_NAME));
        fgets(newPlayer.name, 50, stdin);
        newPlayer.name[strcspn(newPlayer.name, "\n")] = 0;
        if (strchr(newPlayer.name, ' ') != NULL) {
            printf("\n%s\n", getString(STR_NO_SPACES));
            continue;
        }

        if (newPlayer.name[0] == '\0') {
            printf("\n%s\n", getString(STR_NAME_EMPTY));
            continue;
        }
        
        break;
    }

    printf("\n%s:\n", getString(STR_CHOOSE_CLASS));
    printf("1. %s\n", getString(STR_WARRIOR));
    printf("2. %s\n", getString(STR_MAGE));
    printf("3. %s\n", getString(STR_ROGUE));
    printf("%s: ", getString(STR_CHOICE));
    int choice;

    do {
        choice = getIntegerInput();
        if (choice < 1 || choice > 3) {
            printf("%s: ", getString(STR_INVALID_CHOICE));
        }
    } 
    while (choice < 1 || choice > 3);
    
    newPlayer.level = 1;
    newPlayer.experience = 0;
    newPlayer.exp_to_next_level = 100;
    newPlayer.gold = 20;
    switch (choice) {
        case 1: 
        newPlayer.p_class = WARRIOR; 
        newPlayer.base_max_hp = 120; 
        newPlayer.base_strength = 15; 
        break;

        case 2: 
        newPlayer.p_class = MAGE; 
        newPlayer.base_max_hp = 80; 
        newPlayer.base_strength = 10; 
        break;

        case 3: 
        newPlayer.p_class = ROGUE; 
        newPlayer.base_max_hp = 100; 
        newPlayer.base_strength = 12; 
        break;

    }

    newPlayer.equipped_weapon = WEAPON_RUSTY_DAGGER;
    newPlayer.equipped_armor = ARMOR_RAGS;
    newPlayer.hp = getPlayerTotalMaxHP(&newPlayer);
    initializeInventory(&newPlayer.inventory);

    addToInventory(&newPlayer.inventory, HEALTH_POTION, 1);
    

    printf("\n");
    printf(getString(STR_PLAYER_CREATED), newPlayer.name);
    printf("\n");

    pressEnterToContinue();

    return newPlayer;
}

/**
 * @brief Displays Player Stats on terminal
 * 
 * @param player takes player as argument
 */
void displayPlayerStats(const Player* player) {
    const char* className;

    switch (player->p_class) {
        case WARRIOR: 
        className = getString(STR_WARRIOR); 
        break;

        case MAGE:    
        className = getString(STR_MAGE); 
        break;

        case ROGUE:   
        className = getString(STR_ROGUE); 
        break;

        default:      
        className = "Unknown"; 
        break;

    }
    int total_max_hp = getPlayerTotalMaxHP(player);

    int total_strength = getPlayerTotalStrength(player);
    const Weapon* weapon = getWeaponData(player->equipped_weapon);

    const Armor* armor = getArmorData(player->equipped_armor);

    
    printf("\n--- ");
    printf(getString(STR_PLAYER_STATUS_TITLE), player->name);
    printf(" ---\n");

    printf("%s: %s\n", getString(STR_CLASS), className);
    printf("%s: %d\n", getString(STR_LEVEL), player->level);
    printf("%s: %d / %d\n", getString(STR_HP), player->hp, total_max_hp);

    printf("%s: ", getString(STR_STRENGTH));
    printf(getString(STR_STRENGTH_DETAILS), total_strength, player->base_strength, weapon ? weapon->strength_boost : 0);
    printf("\n");

    printf("%s: %d / %d\n", getString(STR_EXPERIENCE), player->experience, player->exp_to_next_level);
    printf("%s: %d\n", getString(STR_GOLD), player->gold);
    printf("--- %s ---\n", getString(STR_EQUIPMENT));
    printf("%s: %s\n", getString(STR_WEAPON), weapon ? weapon->name : getString(STR_NONE));
    printf("%s: %s\n", getString(STR_ARMOR), armor ? armor->name : getString(STR_NONE));
    printf("------------------------\n");
}

/**
 * @brief Level Up the Player and update the players stats
 * 
 * @param player takes player as argument
 */
void levelUp(Player* player) {
    player->level++;
    player->experience = 0;
    player->exp_to_next_level *= 1.5;

    switch (player->p_class) {
        case WARRIOR: player->base_max_hp += 20; 
        player->base_strength += 5; 
        break;

        case MAGE:    player->base_max_hp += 10; 
        player->base_strength += 3; 
        break;

        case ROGUE:   player->base_max_hp += 15; 
        player->base_strength += 4; 
        break;

    }
    player->hp = getPlayerTotalMaxHP(player);

    printf("\n*** %s ***\n", getString(STR_LEVEL_UP));
    printf(getString(STR_NEW_LEVEL), player->level);
    printf("\n%s\n", getString(STR_STATS_INCREASED));

    pressEnterToContinue();
}

/**
 * @brief make player gain experience
 * 
 * @param player the player
 * @param exp the exp amount
 */
void gainExperience(Player* player, int exp) {
    player->experience += exp;

    printf(getString(STR_EXP_GAINED), player->name, exp);

    printf("\n");
    if (player->experience >= player->exp_to_next_level) {
        
        levelUp(player);
    }
}