#ifndef GAME_SCORE_H
#define GAME_SCORE_H

#include "dice_list.h"
#include "player.h"

#include <ncurses.h>

void displayPredictionScore(WINDOW *win, int x, int y, DiceList *dice, Player *pl, int turn);

void erasePredictionScore(WINDOW *win, int x, int y, Player *pl, int turn);

// 得点を表示する
void displayScore(WINDOW *win, int x, int y, Player *pl, int turn);

// 総合得点を表示する
int displayTotalScoreAnimate(WINDOW *win, int x, int y, int total, Player *pl, int turn);

// 小計を表示する
int displaySubTotalScoreAnimate(WINDOW *win, int x, int y, int total, Player *pl, int turn);

// 総合得点部分を初期化
void initDisplayTotalScore(WINDOW *win, int x, int y, int point);

// bonusの表示
void displayBonusScore(WINDOW *win, int x, int y, int point, int turn);

#endif // GAME_SCORE_H