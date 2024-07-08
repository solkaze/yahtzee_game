#ifndef OPERATION_HELP_H
#define OPERATION_HELP_H

#include <ncurses.h>

int readFile(WINDOW *win, const char *filename, int max_length, int subwin_x, int subwin_y);

void createHelpScreen(WINDOW *win);

void displayHelpItemCursor(WINDOW *win, int select);

void displayHelpFrame(WINDOW *win);

void eraseHelpItemCursor(WINDOW *win, int select);

#endif