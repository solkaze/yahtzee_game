#ifndef TITLE_H
#define TITLE_H

#include <ncurses.h>
//タイトル画面表示
void printYahtzee(WINDOW *win);

// menu表示
void printMenu(WINDOW *win);

// カーソル表示
void printTitleCursor(WINDOW *win, int cursor);

// カーソル消去
void deleteTitleCursor(WINDOW *win,int cursor);

// カーソル表示をリセットする
void resetTitleCursor(WINDOW *win, int cursor);

void printTitleFrame(WINDOW *win);;

#endif

