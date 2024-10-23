#ifndef DICE_STRUCT_H
#define DICE_STRUCT_H

#include "dice_list.h"

typedef struct dice_struct
{
	// サイコロ格納用リスト
	DiceList *roll;
	// キープしたサイコロを格納
	DiceList *keep;
	// 一次的に格納する
	DiceList *temp;
	// 全てのサイコロを保持しているリスト
	DiceList *all;
}DiceStruct;

DiceStruct *createDiceStruct();

void initializeDiceStruct(DiceStruct *dice_struct);

void clearDiceStruct(DiceStruct *diceStruct);

void freeDiceStruct(DiceStruct *diceStruct);

#endif // DICE_STRUCT_H