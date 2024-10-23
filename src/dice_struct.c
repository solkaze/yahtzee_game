#include <stdio.h>
#include <stdlib.h>

#include "dice_list.h"
#include "dice_struct.h"

// DiceStructのメモリ割り当てと初期化を行う関数
DiceStruct *createDiceStruct() {
    DiceStruct *diceStruct = (DiceStruct *)malloc(sizeof(DiceStruct));
    if (diceStruct == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    initializeDiceStruct(diceStruct);
    return diceStruct;
}

// DiceStructの初期化関数
void initializeDiceStruct(DiceStruct *diceStruct) {
    if (diceStruct != NULL) {
        initializeDiceList(&(diceStruct->roll));
        initializeDiceList(&(diceStruct->keep));
        initializeDiceList(&(diceStruct->temp));
        initializeDiceList(&(diceStruct->all));
    }
}

// DiceStructの解放関数
void clearDiceStruct(DiceStruct *diceStruct) {
    freeList(&(diceStruct->roll));
    freeList(&(diceStruct->keep));
    freeList(&(diceStruct->temp));
    freeList(&(diceStruct->all));
}

void freeDiceStruct(DiceStruct *diceStruct) {
    if (diceStruct != NULL) {
        freeList(&(diceStruct->roll));
        freeList(&(diceStruct->keep));
        freeList(&(diceStruct->temp));
        freeList(&(diceStruct->all));
        free(diceStruct); // 動的に割り当てたDiceStruct自体を解放
    }
}