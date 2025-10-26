#include <stdio.h>
#include "../include/city.h"
#include "../include/utils.h"
#include "../include/equipment.h"
#include "../include/inventory.h"
#include "../include/language.h"

/**
 * @brief Shop menu
 * 
 * @param player takes player as argument
 */
void shopMenu(Player* player) {

    int choice;

    while(1) {
        clearScreen();
        printf("===== %s =====\n", getString(STR_SHOP_MENU_TITLE));
        printf(getString(STR_WELCOME_TO_SHOP), player->name);
        printf("\n%s: %d\n\n", getString(STR_GOLD), player->gold);
        printf("1. %s\n", getString(STR_BUY_WEAPON));
        printf("2. %s\n", getString(STR_BUY_ARMOR));
        printf("3. %s\n", getString(STR_SELL_ITEM));
        printf("4. %s\n", getString(STR_LEAVE_SHOP));
        printf("%s: ", getString(STR_CHOICE));
        choice = getIntegerInput();

        if (choice == 1) {
            clearScreen();

            printf("--- %s ---\n", getString(STR_FOR_SALE_WEAPONS));

            for (int i = 0; i < WEAPON_COUNT; i++) {
                const Weapon* w = getWeaponData(i);

                printf("%d. %s ", i + 1, w->name);
                printf(getString(STR_WEAPON_STATS), w->strength_boost, w->cost);
                printf("\n");
            }

            printf("0. %s\n", getString(STR_GO_BACK));
            printf("%s: ", getString(STR_CHOICE));

            int weapon_choice = getIntegerInput();

            if (weapon_choice > 0 && weapon_choice <= WEAPON_COUNT) {

                const Weapon* selected_weapon = getWeaponData(weapon_choice - 1);
                if (player->equipped_weapon == selected_weapon->id) {
                     printf("%s\n", getString(STR_ALREADY_HAVE_WEAPON));
                } 

                else if (player->gold >= selected_weapon->cost) {
                    player->gold -= selected_weapon->cost;
                    player->equipped_weapon = selected_weapon->id;
                    printf(getString(STR_BOUGHT_AND_EQUIPPED), selected_weapon->name);
                    printf("\n");
                } 
                
                else {
                    printf("%s\n", getString(STR_NOT_ENOUGH_GOLD));
                }

                pressEnterToContinue();
            }
        } 
        
        else if (choice == 2) {
            clearScreen();

            printf("--- %s ---\n", getString(STR_FOR_SALE_ARMORS));

            for (int i = 0; i < ARMOR_COUNT; i++) {
                const Armor* a = getArmorData(i);
                printf("%d. %s ", i + 1, a->name);
                printf(getString(STR_ARMOR_STATS), a->hp_boost, a->cost);
                printf("\n");
            }

            printf("0. %s\n", getString(STR_GO_BACK));
            printf("%s: ", getString(STR_CHOICE));
            int armor_choice = getIntegerInput();

            if (armor_choice > 0 && armor_choice <= ARMOR_COUNT) {

                const Armor* selected_armor = getArmorData(armor_choice - 1);

                 if (player->equipped_armor == selected_armor->id) {

                     printf("%s\n", getString(STR_ALREADY_HAVE_ARMOR));
                } 
                else if (player->gold >= selected_armor->cost) {

                    player->gold -= selected_armor->cost;
                    player->equipped_armor = selected_armor->id;
                    player->hp = getPlayerTotalMaxHP(player);
                    printf(getString(STR_BOUGHT_AND_EQUIPPED), selected_armor->name);
                    printf("\n");
                } 
                else {
                    printf("%s\n", getString(STR_NOT_ENOUGH_GOLD));
                }

                pressEnterToContinue();
            }
        }
        else if (choice == 3) {

            if (player->inventory.items[HEALTH_POTION] > 0) {

                int sell_price = 5;

                player->inventory.items[HEALTH_POTION]--;
                player->gold += sell_price;
                printf(getString(STR_SOLD_POTION), sell_price);
                printf("\n");
            } 
            else {
                printf("%s\n", getString(STR_NO_POTIONS_TO_SELL));
            }
            pressEnterToContinue();
        }
        else if (choice == 4) {
            
            break;
        }
    }
}
/**
 * @brief The Goldor's Menu
 * 
 * @param player takes player as argument
 */
void goldorMenu(Player* player) {
    int choice;

    while(1) {
        clearScreen();
        printf("===== %s =====\n", getString(STR_CITY_MENU_TITLE));
        printf(getString(STR_CITY_WELCOME), player->name);
        printf("\n\n");
        printf("1. %s\n", getString(STR_GO_TO_SHOP));
        printf("2. %s\n", getString(STR_RETURN_TO_ADVENTURE));
        printf("%s: ", getString(STR_CHOICE));
        choice = getIntegerInput();
        
        switch(choice) { 
            case 1: 
            shopMenu(player);
            break;

            case 2:
                printf("%s\n", getString(STR_LEAVING_CITY));
                pressEnterToContinue();
                return;

            default:
                printf("%s\n", getString(STR_INVALID_CHOICE));
                pressEnterToContinue();
        }
    }
}