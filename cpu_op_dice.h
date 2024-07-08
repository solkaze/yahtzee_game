#ifndef CPU_OP_DICE_H
#define CPU_OP_DICE_H

#define DEL (-1)

#include "dice_list.h"

// 指定された配列の値に基づいてリストの要素をDELに書き換える関数
void replaceNodesByBit(DiceList* head, int num, int size, unsigned int replaceIfBitIs);
// DELの要素をすべて削除する関数
void deleteDelNodes(DiceList** head_ref);
// 置き換えと削除を同時に行う関数
void deleteByBit(DiceList** head, int num, int size, unsigned int replaceIfBitIs);
#endif