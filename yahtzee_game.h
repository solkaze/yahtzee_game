#ifndef YAHTZEE_GAME_H
#define YAHTZEE_GAME_H

#include <ncurses.h>
#include <stdbool.h>

void setDebagMode(bool mode);

bool getDebagMode(void);

void setVsCpu(bool flag);

void yahtzeeGame(WINDOW *win, WINDOW *secondWin);

#endif // YAHTZEE_GAME_H