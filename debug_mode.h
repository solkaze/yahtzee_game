#ifndef DEBUG_MODE_H
#define DEBUG_MODE_H

#include <ncurses.h>
#include <stdbool.h>

#include "dice_list.h"
#include "dice_struct.h"
#include "game_value.h"

void setDebugMode(bool flag);

bool getDebugMode();

// リストのデバッグを管理
void debugList(WINDOW *win, DiceStruct *dice);

void debugListReset(WINDOW *win);

void debugVariable(WINDOW *win, GValue *value);

#endif // DEBUG_MODE_H