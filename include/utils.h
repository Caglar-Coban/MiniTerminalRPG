#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Function For Clearing Terminal
 */
void clearScreen();

/**
 * @brief Get the Random Number object
 * 
 * @param min minumum number
 * @param max maximum number
 * @return int The number that Generated
 */
int getRandomNumber(int min, int max);

/**
 * @brief Get the Integer Input
 * 
 * @return int Returns User's choice
 */
int getIntegerInput();

/**
 * @brief Functions that waiting to user press to enter to continue
 */
void pressEnterToContinue();

#endif // UTILS_H