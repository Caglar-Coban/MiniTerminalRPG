#ifndef ENEMY_H
#define ENEMY_H


/**
 * @brief Defines the types of Mobs (enemies).
 *
 */
typedef enum {
    GOBLIN,
    SLIME,      
    SKELETON,
    ORC,
    GIANT_SPIDER, 
    TROLL,
    GOBLIN_KING 
} EnemyType;
/**
 * @brief Structure to hold the stats for an Enemy (Mob).
 *
 */
typedef struct {
    char name[50];
    EnemyType type;
    int hp;
    int max_hp;
    int strength;
    int experience_given;
    int min_gold_given;
    int max_gold_given;
} Enemy;

/**
 * @brief Creates a standard Enemy object.
 *
 *
 * @param playerLevel The player's current level, used for scaling stats.
 * @return Enemy The newly created Enemy object.
 */
Enemy createEnemy(int playerLevel);
/**
 * @brief Creates a Boss object.
 *
 * Generates a special boss enemy 
 *
 * @param playerLevel The player's current level, used for scaling stats.
 * @return Enemy The newly created boss (as an Enemy object).
 */
Enemy createBoss(int playerLevel);
/**
 * @brief Displays the stats of a specific enemy.
 *
 *
 * @param enemy A pointer to the Enemy object whose stats will be displayed.
 */
void displayEnemyStats(const Enemy* enemy);

#endif // ENEMY_H