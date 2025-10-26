#ifndef COMBAT_H
#define COMBAT_H
#include "player.h"
#include "enemy.h"

/**
 * @brief Main function that starts and manages the fight
 * 
 * @param player Player data.
 * @param enemy Enemy data
 * @return int, Return value: If 1, the player won, if 0, the player lost
 */
int startCombat(Player* player, Enemy* enemy);

#endif // COMBAT_H