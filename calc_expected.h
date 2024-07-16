#ifndef CALC_EXPECTED_H
#define CALC_EXPECTED_H

#include "dice_list.h"
#include "player.h"

int calcWeightedMaxScore(DiceList* head, Player *pl);

double calcDiceZero(DiceList *dice, Player *pl);

// 1つだけ振りなおす場合の処理
double calcDiceOne(DiceList *dice, Player *pl);

// 2つ振りなおす場合
double calcDiceTwo(DiceList *dice, Player *pl);

// 3つ振りなおす場合の処理
double calcDiceThree(DiceList *dice, Player *pl);

// 4つ振りなおす場合の処理
double calcDiceFour(DiceList *dice, Player *pl);

// 5つ振りなおす場合の処理
double calcDiceFive(DiceList *dice, Player *pl);


#endif