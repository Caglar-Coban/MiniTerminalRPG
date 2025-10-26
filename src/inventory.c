#include <stdio.h>
#include "../include/inventory.h"
#include "../include/player.h"
#include "../include/utils.h"
#include "../include/language.h"

/**
 * @brief Helper Function that Gets the item name
 * 
 * @param item takes item object
 * @return const char* returns items name
 */
const char* getItemName(ItemType item) {
    if (item == HEALTH_POTION) {

        return getString(STR_HEALTH_POTION_NAME);
    }

    return "Unknown Item"; 
}

/**
 * @brief Initialize the players inventory
 * 
 * @param inventory the players inventory
 */
void initializeInventory(Inventory* inventory) {
    for (int i = 0; i < ITEM_COUNT; i++) {
        inventory->items[i] = 0;

    }
}

/**
 * @brief Adds item to the Player's inventory
 * 
 * @param inventory takes player's inventory
 * @param item the item going to added to player's inventory
 * @param count the count of the items
 */
void addToInventory(Inventory* inventory, ItemType item, int count) {


    if (item >= 0 && item < ITEM_COUNT) {
        inventory->items[item] += count;
        printf(getString(STR_ITEM_ADDED_TO_INVENTORY), count, getItemName(item));
        printf("\n");
    }
}

/**
 * @brief Displays Player'S inventory to the terminal
 * 
 * @param inventory The player's inventory
 */
void displayInventory(const Inventory* inventory) {
    printf("\n--- %s ---\n", getString(STR_INVENTORY_TITLE));
    int empty = 1;
    for (int i = 0; i < ITEM_COUNT; i++) {

        if (inventory->items[i] > 0) {
            printf("- %s (%d)\n", getItemName(i), inventory->items[i]);
            empty = 0;
        }
    }

    if (empty) {
        printf("%s\n", getString(STR_INVENTORY_EMPTY));
    }

    printf("----------------\n");
}

/**
 * @brief Use item from players inventory
 * 
 * @param inventory the player's inventory
 * @param player The current player
 * @return int Returns 1 if successful,otherwise 0.
 */
int useItem(Inventory* inventory, struct Player* player) {
    clearScreen();

    displayInventory(inventory);
    printf("\n%s\n", getString(STR_ITEM_USE_PROMPT));
    printf("1. %s\n", getItemName(HEALTH_POTION));
    printf("%s: ", getString(STR_CHOICE));

    int choice = getIntegerInput();
    if (choice == 0) {
        return 0;
    }
    
    int itemIndex = -1;
    if (choice == 1) {
        itemIndex = HEALTH_POTION;
    }

    if (itemIndex == -1 || inventory->items[itemIndex] <= 0) {
        printf("%s\n", getString(STR_INVALID_ITEM_CHOICE));
        pressEnterToContinue();
        return 0;
    }

    switch (itemIndex) {
        case HEALTH_POTION: {
            int total_max_hp = getPlayerTotalMaxHP(player);
            int heal_amount = 25;
            if (player->hp == total_max_hp) {
                printf("%s\n", getString(STR_HP_ALREADY_FULL));
                pressEnterToContinue();
                return 0;
            }

            player->hp += heal_amount;
            if (player->hp > total_max_hp) {
                player->hp = total_max_hp;
            }

            inventory->items[itemIndex]--;
            printf(getString(STR_USED_POTION), heal_amount, player->hp, total_max_hp);
            printf("\n");
            break;

        }
        default:
            printf("%s\n", getString(STR_ITEM_NOT_USABLE));
            pressEnterToContinue();
            return 0;
            
    }

    pressEnterToContinue();
    return 1;
}