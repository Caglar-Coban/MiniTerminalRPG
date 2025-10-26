#include <stdio.h>
#include <string.h>
#include "../include/enemy.h"
#include "../include/utils.h"
#include "../include/language.h"

/**
 * @brief Create a RANDOM Enemy 
 * 
 * @param playerLevel takes player level for creating stronger enemy's according to players level
 * @return the created Enemy
 */
Enemy createEnemy(int playerLevel) {
    Enemy newEnemy;
    int enemyType = getRandomNumber(0, 5); 

    switch (enemyType) {
        
        case GOBLIN:
            strcpy(newEnemy.name, "Goblin");
            newEnemy.type = GOBLIN;
            newEnemy.max_hp = 30 + (playerLevel * 5);
            newEnemy.strength = 5 + (playerLevel * 2);
            newEnemy.experience_given = 25 * playerLevel;
            newEnemy.min_gold_given = 5 * playerLevel;
            newEnemy.max_gold_given = 10 * playerLevel;
            break;

        case SLIME:
            strcpy(newEnemy.name, "Slime");
            newEnemy.type = SLIME;
            newEnemy.max_hp = 25 + (playerLevel * 6);
            newEnemy.strength = 4 + (playerLevel * 2);
            newEnemy.experience_given = 20 * playerLevel;
            newEnemy.min_gold_given = 3 * playerLevel;
            newEnemy.max_gold_given = 8 * playerLevel;
            break;

        case SKELETON:
            strcpy(newEnemy.name, "Skeleton");
            newEnemy.type = SKELETON;
            newEnemy.max_hp = 40 + (playerLevel * 7);
            newEnemy.strength = 7 + (playerLevel * 3);
            newEnemy.experience_given = 40 * playerLevel;
            newEnemy.min_gold_given = 10 * playerLevel;
            newEnemy.max_gold_given = 20 * playerLevel;
            break;

        case ORC:
            strcpy(newEnemy.name, "Orc");
            newEnemy.type = ORC;
            newEnemy.max_hp = 50 + (playerLevel * 8);
            newEnemy.strength = 8 + (playerLevel * 3);
            newEnemy.experience_given = 50 * playerLevel;
            newEnemy.min_gold_given = 15 * playerLevel;
            newEnemy.max_gold_given = 25 * playerLevel;
            break;

        case GIANT_SPIDER:
            strcpy(newEnemy.name, "Giant Spider");
            newEnemy.type = GIANT_SPIDER;
            newEnemy.max_hp = 60 + (playerLevel * 9);
            newEnemy.strength = 10 + (playerLevel * 4);
            newEnemy.experience_given = 70 * playerLevel;
            newEnemy.min_gold_given = 25 * playerLevel;
            newEnemy.max_gold_given = 40 * playerLevel;
            break;

        case TROLL:
            strcpy(newEnemy.name, "Troll");
            newEnemy.type = TROLL;
            newEnemy.max_hp = 80 + (playerLevel * 10);
            newEnemy.strength = 12 + (playerLevel * 4);
            newEnemy.experience_given = 80 * playerLevel;
            newEnemy.min_gold_given = 30 * playerLevel;
            newEnemy.max_gold_given = 50 * playerLevel;
            break;

    }

    newEnemy.hp = newEnemy.max_hp;

    return newEnemy;
}

/**
 * @brief Create a Random Boss 
 * 
 * @param playerLevel takes player level for creating stronger Boss's according to players level
 * @return Enemy the Created Boss
 */
Enemy createBoss(int playerLevel) {
    Enemy boss;
    strcpy(boss.name, "GOBLIN KING GORTOK");
    boss.type = GOBLIN_KING;
    boss.max_hp = 150 + (playerLevel * 15);
    boss.strength = 20 + (playerLevel * 5);
    boss.experience_given = 300 * playerLevel;
    boss.min_gold_given = 100 * playerLevel;
    boss.max_gold_given = 200 * playerLevel;
    boss.hp = boss.max_hp;
    return boss;

}

/**
 * @brief Helper Function to displays enemy's stats
 * 
 * @param enemy The Enemy 
 */
void displayEnemyStats(const Enemy* enemy) {


    if (enemy->type == GOBLIN_KING) {
        printf("\n%s\n", getString(STR_BOSS_FIGHT_WARNING));
    }
    
    printf("\n");
    printf(getString(STR_ENEMY_STATUS_HEADER), enemy->name);
    printf("\n");
    printf("%s: %d / %d\n", getString(STR_HP), enemy->hp, enemy->max_hp);
    printf("%s: %d\n", getString(STR_STRENGTH), enemy->strength);
    printf("---------------------\n");
}