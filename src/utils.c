#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/utils.h"
#include "../include/language.h"
#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

/**
 * @brief Function For Clearing Terminal
 */
void clearScreen() {
    system(CLEAR_COMMAND);
}

/**
 * @brief Get the Random Number object
 * 
 * @param min minumum number
 * @param max maximum number
 * @return int The number that Generated
 */
int getRandomNumber(int min, int max) {

    static int seed_initialized = 0;

    if (!seed_initialized) {

        srand(time(NULL));
        seed_initialized = 1;
    }

    return min + rand() % (max - min + 1);
}

/**
 * @brief Get the Integer Input
 * 
 * @return int Returns User's choice
 */
int getIntegerInput() {
    int value;
    char buffer[100];

    while (1) {

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {

            if (sscanf(buffer, "%d", &value) == 1) {

                return value;
            }
        }
        printf("%s", getString(STR_INVALID_INPUT_NUMBER));
    }
}

/**
 * @brief Functions that waiting to user press to enter to continue
 */
void pressEnterToContinue() {

    printf("\n%s", getString(STR_PRESS_ENTER));
    
    while (getchar() != '\n');

    getchar();
}