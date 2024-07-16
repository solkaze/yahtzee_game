#ifndef OPERATION_SCORE_H
#define OPERATION_SCORE_H

#include "op_score_list.h"

void displayScoreHistory(WINDOW *win, ScoreList *score_list, int history_select, int x, int y);

void initScoreScreen(WINDOW *win);

void createScoreScreen(WINDOW *win, int history_select_max);

void displayPage(WINDOW *win, int history_select);

// カーソル表示を行う
void displayHistoryItemCursor(WINDOW *win, int select);

// カーソルを消す
void eraseHistoryItemCursor(WINDOW *win, int select);

void displayHistoryScore(WINDOW *win, int x, int y, ScoreList *head, int turn, int index);

void displayHistoryName(WINDOW *win, int x, int y, ScoreList *head, int turn, int index);

void eraseScoreHistory(WINDOW *win, int x, int y);

// 履歴のメージ移動のカーソルを表示する関数
void displayPageCursor(WINDOW *win, int select, int history_select, int history_max);

void displayHistoryTotalScore(WINDOW *win, int x, int y, ScoreList *head, int turn,int index);

void eraseHistoryTotalScore(WINDOW *win, int x, int y);

// 見やすさを上げるフレームを生成
void displayHistoryFrame(WINDOW *win);

#endif