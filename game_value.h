#ifndef DICE_VALUE_H
#define DICE_VALUE_H

#define REROLL_MAX 3
#define INIT_DICE 5

#include <stdbool.h>
#include <stdlib.h>

#include "player.h"

typedef struct dice_value {
	int input_key;
    // 各項目のカーソル
    int dice_cursor;
    int keep_cursor;
    int score_cursor;

    // モード選択
    int mode_select;

    // 振り直し対象の決定
    int reroll_dice;
    int keep_dice;

    // 残りの振りなおせる回数を定義
    int reroll_count;

    // ボーナスの点と必要点を定義
    // プレイヤーのターンを定義
    int p_turn;

	int turn;

    // 全体ターンを定義
}GValue;

typedef struct score_value {
	int bonus_border;
	int bonus_score;

	bool is_bonus[2];

	int total_score[2];
	int sub_total_score[2];

}SValue;

typedef struct score_board_place {
	int x;
	int y;
}SBPlace;

GValue *createGameValue();

void initializeValue(GValue *va);

void setPlayerTurn(GValue *gv);

// 点数をつけたあと呼び出す
void resetValue(GValue *gv, Player *pl);

void initScoreValue(SValue *sv);

void setScoreBoardPlace(SBPlace *bp);

void freeGameValue(GValue *gv);

#endif