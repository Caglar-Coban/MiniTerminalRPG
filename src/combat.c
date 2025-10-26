#include <stdio.h>
#include "../include/combat.h"
#include "../include/utils.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include "../include/inventory.h"
#include "../include/language.h"

#define COMBAT_RESULT_WIN 1
#define COMBAT_RESULT_LOSS 0
#define COMBAT_RESULT_ESCAPE 2

/**
 * @brief Stars combat 
 * The combat keep going until player or enemy dies or player can successfully run
 * @param player the Player going to fight
 * @param enemy the Enemy going to fight
 * @return int Returns Combat results win or loss
 */
int startCombat(Player* player, Enemy* enemy) {
    clearScreen();
    
    printf(getString(STR_ENEMY_APPEARED), enemy->name);
    printf("\n\n");
    pressEnterToContinue();
    
    int playerTotalStrength = getPlayerTotalStrength(player);

    while (player->hp > 0 && enemy->hp > 0) {
        clearScreen();

        displayPlayerStats(player);
        displayEnemyStats(enemy);

        printf("\n%s:\n", getString(STR_COMBAT_MENU_TITLE));
        printf("1. %s\n", getString(STR_ATTACK));
        printf("2. %s\n", getString(STR_USE_ITEM));
        printf("3. %s\n", getString(STR_FLEE));
        printf("%s: ", getString(STR_CHOICE));

        int choice = getIntegerInput();

        if (choice == 1) {

            int playerDamage = getRandomNumber(playerTotalStrength / 2, playerTotalStrength);
            enemy->hp -= playerDamage;
            printf("\n");
            
            
            printf(getString(STR_PLAYER_DEALT_DAMAGE), enemy->name, playerDamage);
            
            if (enemy->hp < 0) enemy->hp = 0;
            printf("\n");
            printf(getString(STR_ENEMY_HP_REMAINING), enemy->name, enemy->hp);
        } 
        else if (choice == 2) {

            useItem(&player->inventory, player);
        } 
        else if (choice == 3) {

            if (enemy->type == GOBLIN_KING) {
                printf("\n%s\n", getString(STR_CANNOT_FLEE_BOSS));
            } 
            else {
                if (getRandomNumber(1, 100) <= 60) {

                    int gold_lost = getRandomNumber(5, 15) * player->level;
                    if (gold_lost > player->gold) gold_lost = player->gold;
                    player->gold -= gold_lost;
                    printf("\n%s\n", getString(STR_FLEE_SUCCESS));
                    printf(getString(STR_FLEE_GOLD_LOST), gold_lost);
                    printf("\n");
                    pressEnterToContinue();
                    return COMBAT_RESULT_ESCAPE;

                } 
                else {

                    printf("\n%s\n", getString(STR_FLEE_FAIL));
                }
            }
        } 
        else {

             printf("\n%s\n", getString(STR_TURN_SKIPPED));
        }

        if (enemy->hp > 0) {

            int enemyDamage = getRandomNumber(enemy->strength / 2, enemy->strength);
            player->hp -= enemyDamage;
            printf("\n");
            printf(getString(STR_ENEMY_DEALT_DAMAGE), enemy->name, enemyDamage);
            if (player->hp < 0) player->hp = 0;
            printf("\n");
            printf(getString(STR_PLAYER_HP_REMAINING), player->hp);
        }

        printf("\n");
        pressEnterToContinue();
    }

    if (player->hp > 0) {

        printf("\n");
        printf(getString(STR_VICTORY), enemy->name);
        printf("\n");
        gainExperience(player, enemy->experience_given);
        
        int gold_dropped = getRandomNumber(enemy->min_gold_given, enemy->max_gold_given);
        player->gold += gold_dropped;
        printf(getString(STR_GOLD_GAINED), gold_dropped);
        printf("\n");

        if (enemy->type == GOBLIN_KING && getRandomNumber(1, 100) <= 50) {
            
             printf("%s\n", getString(STR_BOSS_LOOT_BONUS));
             addToInventory(&player->inventory, HEALTH_POTION, 1);
        }
        else if (getRandomNumber(1, 100) <= 20) {

            addToInventory(&player->inventory, HEALTH_POTION, 1);
        }
        
        pressEnterToContinue();

        return COMBAT_RESULT_WIN;
    } 
    else {

        printf("\n%s\n", getString(STR_DEFEATED));
        pressEnterToContinue();
        return COMBAT_RESULT_LOSS;
    }
}