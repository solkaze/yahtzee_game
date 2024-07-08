#ifndef DEBAG_MODE_H
#define DEBAG_MODE_H

#include "dice_list.h"

#include <ncurses.h>

void setUpdateDice(bool flag);

bool getUpdateDice();

// リストのデバッグを管理
void debugList(WINDOW *win, DiceList *list1, DiceList *list2, DiceList *list3);

void debugVariable(WINDOW *win, int reroll, int keep, int p_turn, int turn);

#endif // DEBAG_MODE_H