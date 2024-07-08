#ifndef GAME_CURSOR_H
#define GAME_CURSOR_H

#include "player.h"

#include <ncurses.h>

// サイコロのカーソルを指す
void diceCursorShape(WINDOW *win, int x, int y);

// 位置に合わあせてカーソルを表示する
void printDiceCursor(WINDOW *win, int el, int num);

// カーソルを削除する
void eraseDiceCursor(WINDOW *win, int el, int num);

// キープ用カーソル表示
void printKeepDiceCursor(WINDOW *win, int el);

// キープ用カーソル削除
void eraseKeepDiceCursor(WINDOW *win, int el);

// 得点表のカーソルを表示する
void printScoreCursor(WINDOW *win, int x,int y, int num, int turn);

// 得点表のカーソルを消去する
void eraseScoreCursor(WINDOW *win, int x, int y, int num, int turn);

// 得点表のカーソル移動管理
int skipScoreCursor(Player *pl, int num, int key, int select);

// 得点表のカーソル位置をリセットする
int initScoreCursor(Player *pl);

// 振り直しのカーソルを表示
void printRerollCursor(WINDOW *win);

// 振り直しのカーソルを消去する
void eraseRerollCursor(WINDOW *win);

// Playerのターンのバーを表示する関数
void displayPlayerTurn(WINDOW *win, int x, int y, int turn);

#endif