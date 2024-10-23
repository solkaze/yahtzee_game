#ifndef CALC_SCORE_H
#define CALC_SCORE_H

#include "dice_list.h"

// 1の目を計算する
int calcAce(DiceList* head);

// 2の目を計算する
int calcDeuce(DiceList* head);

// 3の目を計算する
int calcTrey(DiceList* head);

// 4の目を計算する
int calcFour(DiceList* head);

// 5の目を計算する
int calcFive(DiceList* head);

// 6の目を計算する
int calcSix(DiceList* head);

// チョイスの計算
int calcChoice(DiceList* head);

// フォーダイスの計算
int calcFourDice(DiceList* head) ;

// フルハウスの計算
int calcFullHouse(DiceList* head);

// S.ストレートの計算
int calcSmallStraight(DiceList* head);

// B.ストレートの計算
int calcBigStraight(DiceList* head);

// ヨットの計算
int calcYahtzee(DiceList* head);

#endif // CALC_SCORE_H