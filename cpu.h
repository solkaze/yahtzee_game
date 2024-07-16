#ifndef CPU_H
#define CPU_H

#include <ncurses.h>

#include "cpu_queue.h"
#include "dice_list.h"
#include "player.h"

#define MAX_TRIAL 32

void setComputer(bool flag);

bool getComputer();

int CPUAction(Queue *q);

void initCPUActionQueue(Queue *q);

// 行動決定処理
void CPUActionDecision(Queue *q, DiceList *dice, DiceList *keep, Player *pl, int reroll_count);

#endif