#include <ncurses.h>
#include <unistd.h>

#include "game_value.h"
#include "dice_struct.h"
#include "dice_list.h"
#include "operation_mode.h"
#include "operation_dice.h"
#include "player.h"
#include "cpu_queue.h"
#include "cpu.h"
#include "game_screen.h"
#include "game_score.h"
#include "game_cursor.h"
#include "operation_score.h"
#include "message.h"
#include "time_sleep.h"

void OPModeFirst(WINDOW *win, GValue *gv, DiceStruct *dice) {
	eraseAllDice(win, countNodes(dice->roll));
	eraseAllKeepDice(win, countNodes(dice->keep));

	transferNode(&(dice->roll), &(dice->keep), gv->dice_cursor);
	gv->reroll_dice = countNodes(dice->roll);
	gv->keep_dice = countNodes(dice->keep);
	if(gv->dice_cursor >= gv->reroll_dice && gv->reroll_dice > 0) {
		(gv->dice_cursor)--;
	}
	if(gv->reroll_dice == 0) {
		gv->mode_select = 2;
		// カーソル位置の初期化
		gv->dice_cursor = 0;
	}
	displayAllDice(win, dice->roll, countNodes(dice->roll));
}

void OPModeSecond(WINDOW *win, GValue *gv, DiceStruct *dice) {
	eraseAllDice(win, gv->reroll_dice);
	eraseAllKeepDice(win, gv->keep_dice);

	transferInOrderNode(&(dice->keep), &(dice->roll), gv->keep_cursor);
	// 振りなおすサイコロの数をセット
	gv->reroll_dice = countNodes(dice->roll);
	gv->keep_dice = countNodes(dice->keep);
	if(gv->keep_cursor >= gv->keep_dice && gv->keep_dice > 0) {
		(gv->keep_cursor)--;
	}
	if(countNodes(dice->keep) == 0) {
		gv->mode_select = 1;
		// カーソル位置の初期化
		gv->keep_cursor = 0;
	}
	displayAllDice(win, dice->roll, countNodes(dice->roll));
}

void OPModeThird(WINDOW *win, GValue *gv, DiceStruct *dice, Player *pl, SValue *sv, SBPlace sp, Queue *q) {
	mergeLists(&(dice->all), dice->roll, dice->keep);

	// 得点を入れる処理
	setScore(dice->all, pl, gv->score_cursor);
	// リストをすべてリセット
	clearDiceStruct(dice);


	//得点を計算し格納する
	calcTotalScore(pl);

	displayScore(win, sp.x, sp.y, pl, gv->p_turn);

	// 出目の予測値をリセット
	erasePredictionScore(win, sp.x, sp.y, pl, gv->p_turn);

	// サイコロの表示を消去
	eraseAllDiceAnimate(win, gv->reroll_dice);
	eraseAllKeepDiceAnimate(win, gv->keep_dice);

	// 振りなおすサイコロのリセット
	gv->reroll_dice = INIT_DICE;

	// キープしたサイコロを初期化する
	gv->keep_dice = countNodes(dice->keep);

	// 得点を構造体へ入れる
	calcTotalScore(pl);

	// 小計を表示する
	sv->sub_total_score[gv->p_turn] = displaySubTotalScoreAnimate(win, sp.x, sp.y, sv->sub_total_score[gv->p_turn], pl, gv->p_turn);

	if(calcSubTotalScore(pl) >= sv->bonus_border && !(sv->is_bonus[gv->p_turn])) {
		sv->is_bonus[gv->p_turn] = true;

		displayBonusScore(win, sp.x, sp.y, sv->bonus_score, gv->p_turn);
	}
	// 得点を表示する
	sv->total_score[gv->p_turn] = displayTotalScoreAnimate(win, sp.x, sp.y, sv->total_score[gv->p_turn], pl, gv->p_turn);
	if(getComputer() && gv->p_turn == 1) {
		initCPUActionQueue(q);
	}
	eraseRerollMessage(win);
	// プレイヤーを交代する
	setPlayerTurn(gv);

	// モードを振り直しにセット
	gv->mode_select = 4;

	// スコアのカーソルをリセット
	gv->score_cursor = initScoreCursor(pl);
	gv->dice_cursor = 0;
	gv->keep_cursor = 0;


	// 振り直し回数もリセット
	gv->reroll_count = REROLL_MAX;
}

void OPModeFourth(WINDOW *win, GValue *gv, DiceStruct *dice, Player *pl,SBPlace sp, Queue *q) {
	// 振り直したサイコロのカーソルを消す
	eraseRerollCursor(win);
	// サイコロの表示を消す
	if(countNodes(dice->roll) != 0) {
		sleep_microseconds(10000);
		eraseAllDiceAnimate(win, gv->reroll_dice);
	}

	// サイコロの表をリセット
	// 振り直したサイコロを再度代入する処理
	freeList(&(dice->roll));
	copyList(dice->temp, &(dice->roll));
	gv->reroll_dice = countNodes(dice->roll);
	// 一次的に保持していたリストを開放する
	freeList(&(dice->temp));

	// 全てのサイコロをいったん保持する
	mergeLists(&(dice->all), dice->roll, dice->keep);

	displayAllDiceAnimate(win, dice->roll, gv->reroll_dice);
	sleep(1);
	sortList(&(dice->roll));
	eraseAllDiceAnimate(win, gv->reroll_dice);
	displayAllDiceAnimate(win, dice->roll, gv->reroll_dice);

	// サイコロを振ると振りなおせる回数が減る
	(gv->reroll_count)--;
	displayRerollMessage(win, gv->reroll_count);
	//サイコロを振ると必ず選択画面へ移動
	// サイコロのカーソルの位置とキープのカーソルの位置をリセット
	gv->dice_cursor = 0;
	gv->keep_cursor = 0;

	// まだ振りなおせる場合はモードを1に
	if(gv->reroll_count > 0) {
		gv->mode_select = 1;
	}
	// 無理ならば得点表に移動
	else {
		gv->mode_select = 3;
	}

	gv->score_cursor = initScoreCursor(pl);
	// 予想店を表示
	displayPredictionScore(win, sp.x, sp.y, dice->all, pl, gv->p_turn);
	// 役がそろっていたら表示する
	if(checkFunctions(dice->all)) {
		displayMessage(win, dice->all, pl);
		// そのままなら消えてしまうため戻す処理を行う
		displayAllDice(win, dice->roll, countNodes(dice->roll));
	}
	if(getComputer() && gv->p_turn == 1) {
		CPUActionDecision(q, dice->roll, dice->keep, pl, gv->reroll_count);
	}
	// 全てのリストをいったんリセットする
	freeList(&(dice->all));
}