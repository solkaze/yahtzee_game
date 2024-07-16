#include <ncurses.h>
#include <string.h>
#include "game_value.h"
#include "game_cursor.h"
#include "player.h"

GValue *createGameValue() {
    GValue *va = malloc(sizeof(GValue));
	if(va == NULL) {
		endwin();
		printf("Error: malloc failed\n");
		exit(1);
	}

    initializeValue(va);

    return va;
}

void initializeValue(GValue *gv) {
	// キーの入力された情報が保持される
	gv->input_key = OK;
	// カーソル位置の初期設定
    gv->dice_cursor = 0;
    gv->keep_cursor = 0;
    gv->score_cursor = 0;

    // モード選択初期は4
    gv->mode_select = 4;

    gv->reroll_dice = INIT_DICE;
    gv->keep_dice = 0;

	// 振り直し最大数を定義

	gv->reroll_count = REROLL_MAX;

    gv->p_turn = 0;

	gv->turn = 0;
}

void setPlayerTurn(GValue *gv) {
    if(gv->p_turn == 0) {
        gv->p_turn = 1;
    }
    else {
        gv->p_turn = 0;
		(gv->turn)++;
    }
}

// 点数をつけたあと呼び出す
void resetValue(GValue *gv, Player *pl) {
    gv->dice_cursor = 0;
    gv->keep_cursor = 0;
    gv->score_cursor = initScoreCursor(pl);

	gv->reroll_count = REROLL_MAX;

	gv->reroll_dice = 5;
    gv->keep_dice = 0;

	gv->mode_select = 4;
}

void initScoreValue(SValue *sv) {
	sv->bonus_border = 63;
	sv->bonus_score = 35;

	memset(sv->is_bonus, FALSE, sizeof(sv->is_bonus));

	memset(sv->total_score, 0, sizeof(sv->total_score));
	memset(sv->sub_total_score, 0, sizeof(sv->sub_total_score));
}

void setScoreBoardPlace(SBPlace *bp) {
	bp->x = 5;
	bp->y = 3;
}

//メモリを開放
void freeGameValue(GValue *gv) {
	free(gv);
}