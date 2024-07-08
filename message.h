#ifndef MESSAGE_H
#define MESSAGE_H

#include "dice_list.h"

#include <ncurses.h>
#include <stdbool.h>

void displayMessage(WINDOW *win, DiceList *dice, Player *pl);

// 配列内の関数の結果が一つでも0より上であればTRUEを返す関数
bool checkFunctions(DiceList *dice);

// 勝利メッセージ
void displayWinMessage(WINDOW *win, Player *pl);

// 引き分けメッセージ
void displayDrawMessage(WINDOW *win);

#endif