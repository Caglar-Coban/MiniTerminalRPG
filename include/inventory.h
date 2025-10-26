#ifndef INVENTORY_H
#define INVENTORY_H

/**
 * @brief Forward declaration of the 'Player' struct.
 * This allows us to use 'struct Player*' without including player.h,
 */
struct Player;

/**
 * @brief Defines the types of consumable items available in the game.
 * 
 */
typedef enum {
    HEALTH_POTION,
    ITEM_COUNT
} ItemType;

/**
 * @brief Represents the player's inventory.
 * 
 */
typedef struct Inventory { 
    int items[ITEM_COUNT];
} Inventory;

/**
 * @brief Initializes the inventory to its default (empty) state.
 * 
 * @param inventory A pointer to the Inventory struct to be initialized.
 */
void initializeInventory(Inventory* inventory);

/**
 * @brief Adds a specified quantity of an item to the inventory.
 * 
 * @param inventory A pointer to the player's Inventory.
 * @param item The ItemType of the item to add.
 * @param count The number of items to add.
 */
void addToInventory(Inventory* inventory, ItemType item, int count);

/**
 * @brief Displays the current contents of the inventory to the console.
 * 
 * @param inventory A read-only pointer to the Inventory to be displayed.
 */
void displayInventory(const Inventory* inventory);

/**
 * @brief Uses a selected item from the inventory and applies its effect.
 * 
 * @param inventory A pointer to the player's Inventory.
 * @param player A pointer to the Player struct, used to apply item effects (like healing).
 * @return int Returns 1 if an item was successfully used, 0 otherwise
 */
int useItem(Inventory* inventory, struct Player* player);

/**
 * @brief A helper function to get the display name of an item.
 * 
 * @param item The ItemType of the item.
 * @return const char* A read-only string containing the name of the item.
 */
const char* getItemName(ItemType item);

#endif // INVENTORY_H