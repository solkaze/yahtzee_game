#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <ncurses.h>
// ゲーム画面を表示する
void gameScreen(WINDOW *win, int x, int y);

//スコアボードを表示する
void printScoreboard(WINDOW *win, int x, int y);

void displayRerollMessage(WINDOW *win, int reroll_count);

void eraseRerollMessage(WINDOW *win);

#endif // GAME_SCREEN_H