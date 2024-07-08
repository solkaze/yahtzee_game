#ifndef OPERATION_DICE_H
#define OPERATION_DICE_H

#include "dice_list.h"

#include <ncurses.h>

// すべてのサイコロを表示する関数
void displayAllDice(WINDOW *win, DiceList *dice, int num);

void displayAllDiceAnimate(WINDOW *win, DiceList *dice, int num);
// すべてのサイコロを画面から消去する関数
void eraseAllDice(WINDOW *win, int num);
// アニメーションを加えつつ消す関数
void eraseAllDiceAnimate(WINDOW *win, int num);

// 全てのキープしたサイコロを表示する
void displayAllKeepDice(WINDOW *win, DiceList *dice, int num);
// キープしたサイコロをすべて消す
void eraseAllKeepDice(WINDOW *win, int num);
// アニメーションを加えつつ消す
void eraseAllKeepDiceAnimate(WINDOW *win, int num);
// 指定番目のサイコロのx座標を取得する関数
int getDiceX(int size_x, int el, int num);
// 指定番目のサイコロのy座標を取得する
int getDiceY(int size_y);

#endif // OPERATION_DICE_H