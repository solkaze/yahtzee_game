#ifndef OPERATION_MODE_H
#define OPERATION_MODE_H

#include <ncurses.h>
#include "game_value.h"
#include "dice_struct.h"
#include "player.h"
#include "cpu_queue.h"

void OPModeFirst(WINDOW *win, GValue *gv, DiceStruct *dice);

void OPModeSecond(WINDOW *win, GValue *gv, DiceStruct *dice);

void OPModeThird(WINDOW *win, GValue *gv, DiceStruct *dice, Player *pl, SValue *sv, SBPlace s_place, Queue *q);

void OPModeFourth(WINDOW *win, GValue *gv, DiceStruct *dice, Player *pl,SBPlace sp, Queue *q);

#endif