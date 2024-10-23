#ifndef DICE_H
#define DICE_H

#include <ncurses.h>
// サイコロを表示する関数
void displayDice(WINDOW *win,int value , int x, int y);

// サイコロを削除する
void eraseDice(WINDOW *win,int x, int y);

#endif // DICE_H