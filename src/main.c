#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include "../include/combat.h"
#include "../include/save_load.h"
#include "../include/inventory.h"
#include "../include/city.h"
#include "../include/language.h"

/**
 * @brief The main Game Loop for Playing
 * 
 * @param player the Player that is going to play the game
 */
void gameLoop(Player* player) {
    int choice;

    while (1) {
        clearScreen();

        displayPlayerStats(player);

        printf("\n===== %s =====\n", getString(STR_ADVENTURE_MENU_TITLE));
        printf("%s\n\n", getString(STR_WHAT_TO_DO));
        printf("1. %s\n", getString(STR_ADVENTURE_COMBAT));
        printf("2. %s\n", getString(STR_GO_TO_CITY));
        printf("3. %s\n", getString(STR_SAVE_GAME));
        printf("4. %s\n", getString(STR_RETURN_TO_MAIN_MENU));
        printf("%s: ", getString(STR_CHOICE));

        choice = getIntegerInput();

        switch (choice) {
            case 1: {
                Enemy monster;
                if (player->level >= 5 && getRandomNumber(1, 100) <= 25) {
                    monster = createBoss(player->level);
                } 
                else {
                    monster = createEnemy(player->level);
                }

                int combatResult = startCombat(player, &monster);
                if (combatResult == 0) { 
                    printf("\n%s\n", getString(STR_GAME_OVER));
                    addHighScore(player);
                    pressEnterToContinue();
                    return;
                }

                break;
            }
            case 2:
                goldorMenu(player);
                break;

            case 3:
                saveGame(player);
                break;

            case 4:
                printf("%s...\n", getString(STR_SAVING_SCORE));
                addHighScore(player);
                pressEnterToContinue();
                return;

            default:
                printf("%s\n", getString(STR_INVALID_CHOICE));
                pressEnterToContinue();
                break;

        }
    }
}

/**
 * @brief the main menu for playing the game and choose the launguage
 * 
 * @return int returns 1 successful selection
 */
int main() {
    Player player;
    int choice;

    
    while(1) {
        clearScreen();

        printf("Choose your language / Dilinizi secin:\n");
        printf("1. English\n");
        printf("2. Turkce\n");
        printf("Your Choice / Seciminiz: ");
        choice = getIntegerInput();


        if (choice == 1) {
            if (loadLanguage("en")) break; 
        } 
        else if (choice == 2) {
            if (loadLanguage("tr")) break; 
        }
    }

    pressEnterToContinue();
    

    while (1) {
        clearScreen();


        printf("========================\n");
        printf("  %s\n", getString(STR_MAIN_MENU_TITLE));
        printf("========================\n");
        printf("1. %s\n", getString(STR_NEW_GAME));
        printf("2. %s\n", getString(STR_LOAD_GAME));
        printf("3. %s\n", getString(STR_HIGH_SCORES));
        printf("4. %s\n", getString(STR_EXIT));
        printf("========================\n");
        printf("%s: ", getString(STR_CHOICE));

        choice = getIntegerInput();

        switch (choice) {
            case 1:
                player = createPlayer();
                gameLoop(&player);
                break;

            case 2:
                if (loadGame(&player)) {
                    gameLoop(&player);
                }
                break;

            case 3:
                showHighScores();
                break;

            case 4:
                printf("%s...\n", getString(STR_EXITING_GAME));
                return 0;

            default:
                printf("%s\n", getString(STR_INVALID_CHOICE_MENU));
                pressEnterToContinue();
                
        }
    }
    return 0;
}