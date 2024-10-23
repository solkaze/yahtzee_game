#ifndef WINDOW_STRUCT_H
#define WINDOW_STRUCT_H

#include <ncurses.h>

typedef struct yahtzeeWindow
{
	WINDOW *main_win;
	WINDOW *second_win;
}GameWin;

void createWindow(GameWin **win);

void freeWindow(GameWin *win);

#endif // WINDOW_STRUCT_H