#ifndef MODE_KEEP_DICE_H
#define MODE_KEEP_DICE_H

#include <ncurses.h>

#include "dice_list.h"
#include "cpu_queue.h"
#include "dice_struct.h"
#include "game_value.h"
#include "window_struct.h"

void keepDiceSelection(GameWin *wins, DiceStruct *dice, Queue *cpu_queue, GValue *gv);

#endif // MODE_KEEP_DICE_H