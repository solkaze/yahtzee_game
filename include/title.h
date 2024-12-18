#ifndef TITLE_H
#define TITLE_H

#include <ncurses.h>
//タイトル画面表示

void displayTitleScreen(WINDOW *win, int select);

void printYahtzee(WINDOW *win);

// menu表示
void printMenu(WINDOW *win);

// カーソル表示
void printMenuCursor(WINDOW *win, int cursor);

// カーソル消去
void deleteTitleCursor(WINDOW *win,int cursor);

// カーソル表示をリセットする
void resetTitleCursor(WINDOW *win, int cursor);

void printMenuFrame(WINDOW *win);;

#endif

