#ifndef NAME_H
#define NAME_H

#include <ncurses.h>
#include <stdbool.h>

void displayInputNameFrame(WINDOW *win);

void inputName(WINDOW *win,int x, int y, bool cpu, Player *pl, int turn);

void displayPlayerName(WINDOW *win,int x, int y, Player *pl, int turn);

#endif