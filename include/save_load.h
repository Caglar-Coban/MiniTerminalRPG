#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H
#include "player.h"
#define SAVE_FILE "data/savegame.dat"
#define HIGHSCORE_FILE "data/highscores.txt"
#define MAX_HIGH_SCORES 20

/**
 * @brief The Struct for High score Board
 * 
 */
typedef struct {
    char name[50];
    int score;
} HighScore;

/**
 * @brief Function For Save the Game
 * 
 * @param player Current Player for Saving
 */
void saveGame(const Player* player);

/**
 * @brief Function For Load the Game
 * 
 * @param player The Player for Load
 * @return int Returns 1 if successful
 */
int loadGame(Player* player);

/**
 * @brief Funciton For Printing The High Score Table
 */
void showHighScores();

/**
 * @brief Add's Player to the HighScore table
 * 
 * @param player Current Player for adding to HighScore Table
 */
void addHighScore(const Player* player);

#endif // SAVE_LOAD_H