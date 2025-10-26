#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/save_load.h"
#include "../include/player.h"
#include "../include/utils.h"
#include "../include/language.h"

/**
 * @brief Function For Save the Game
 * 
 * @param player Current Player for Saving
 */
void saveGame(const Player* player) {
    FILE* file = fopen(SAVE_FILE, "wb");

    if (file == NULL) {

        printf("%s\n", getString(STR_ERROR_SAVE_FAILED));
        pressEnterToContinue();

        return;
    }
    fwrite(player, sizeof(Player), 1, file);

    fclose(file);
    printf("%s\n", getString(STR_GAME_SAVED_SUCCESS));

    pressEnterToContinue();
}

/**
 * @brief Function For Load the Game
 * 
 * @param player The Player for Load
 * @return int Returns 1 if successful
 */
int loadGame(Player* player) {

    FILE* file = fopen(SAVE_FILE, "rb");

    if (file == NULL) {

        printf("%s\n", getString(STR_SAVE_FILE_NOT_FOUND));
        pressEnterToContinue();

        return 0;
    }
    fread(player, sizeof(Player), 1, file);
    fclose(file);
    printf("%s\n", getString(STR_GAME_LOADED_SUCCESS));
    pressEnterToContinue();

    return 1;
}

/**
 * @brief The Function That Compares High Scores
 * 
 * @param a Score for Player A
 * @param b Score for Player B
 * @return int Returns the Differences of Score
 */
static int compareScores(const void* a, const void* b) {

    HighScore* scoreA = (HighScore*)a;

    HighScore* scoreB = (HighScore*)b;

    return scoreB->score - scoreA->score;
}

/**
 * @brief The Struct for High score Board
 */
void showHighScores() {

    FILE* file = fopen(HIGHSCORE_FILE, "r");

    HighScore scores[MAX_HIGH_SCORES];
    int count = 0;

    if (file != NULL) {

        while (count < MAX_HIGH_SCORES && fscanf(file, "%s %d", scores[count].name, &scores[count].score) == 2) {

            count++;
        }
        fclose(file);
    }
    
    clearScreen();

    printf("===== %s =====\n", getString(STR_HIGH_SCORES_TITLE));
    
    if (count == 0) {

        printf("\n%s\n", getString(STR_NO_HIGH_SCORES));
    } 
    else {
        qsort(scores, count, sizeof(HighScore), compareScores);
        for (int i = 0; i < count; i++) {
            printf("%d. %-20s %d\n", i + 1, scores[i].name, scores[i].score);
        }
    }
    

    printf("\n==========================\n");
    pressEnterToContinue();
}

/**
 * @brief Add's Player to the HighScore table
 * 
 * @param player Current Player for adding to HighScore Table
 */
void addHighScore(const Player* player) {
    int current_score = (player->level * 1000) + player->gold;

    HighScore scores[MAX_HIGH_SCORES + 1];
    int count = 0;

    FILE* file = fopen(HIGHSCORE_FILE, "r");

    if (file != NULL) {
        while (count < MAX_HIGH_SCORES && fscanf(file, "%s %d", scores[count].name, &scores[count].score) == 2) {

            count++;
        }
        
        fclose(file);
    }

    if (count == MAX_HIGH_SCORES && current_score <= scores[count - 1].score) {

        return;

    }

    strcpy(scores[count].name, player->name);

    scores[count].score = current_score;

    if (count < MAX_HIGH_SCORES) {

        count++;
    }

    qsort(scores, count, sizeof(HighScore), compareScores);

    file = fopen(HIGHSCORE_FILE, "w");
    if (file != NULL) {

        int limit = (count < MAX_HIGH_SCORES) ? count : MAX_HIGH_SCORES;

        for (int i = 0; i < limit; i++) {

            fprintf(file, "%s %d\n", scores[i].name, scores[i].score);
        }

        fclose(file);
        
        printf("\n%s\n", getString(STR_HIGH_SCORE_CONGRATS));
    }
}