#ifndef CPU_OP_DATA_H
#define CPU_OP_DATA_H

#define FULL (-1)

#include "player.h"
#include "dice_list.h"

// もしすでに埋まっているならばその行にはFULLを代入する
void searchScoreArray(Player *pl, DiceList *di, int score[SCORE_MAX_NUM], float weights[SCORE_MAX_NUM]);

// 配列内のスコアの場所を返す
int findScoreIndex(int score[SCORE_MAX_NUM], int target);

// データの最大値を探す
double findMax(double arr[], int size);

// scoreの最大値を探す
int findMaxScore(int arr[], int size);

// データの最大値が何番目にあるか調べる関数
int findMaxIndex(double arr[], int size);

#endif //CPU_OP_DATA_H