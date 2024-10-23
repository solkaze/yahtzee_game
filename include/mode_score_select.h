#ifndef MODE_SCORE_SELECT_H
#define MODE_SCORE_SELECT_H

#include <ncurses.h>

#include "dice_list.h"
#include "cpu_queue.h"
#include "player.h"
#include "game_value.h"
#include "window_struct.h"

void scoreBoardSelection(GameWin *wins, DiceStruct *dice, Queue *cpu_queue, Player *pl[], GValue *gv, SBPlace bp);

#endif // MODE_SCORE_SELECT_H