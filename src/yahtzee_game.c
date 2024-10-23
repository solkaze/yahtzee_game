#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#include "error.h"
#include "title.h"
#include "player.h"
#include "dice.h"
#include "game_screen.h"
#include "create.h"
#include "dice_list.h"
#include "operation_dice.h"
#include "operation_score.h"
#include "game_cursor.h"
#include "yahtzee_game.h"
#include "game_score.h"
#include "name.h"
#include "debug_mode.h"
#include "cpu_queue.h"
#include "message.h"
#include "cpu.h"
#include "mode_roll_dice.h"
#include "mode_keep_dice.h"
#include "mode_score_select.h"
#include "mode_reroll_select.h"
#include "dice_cursor_flag.h"
#include "dice_struct.h"
#include "game_value.h"
#include "operation_mode.h"
#include "window_struct.h"

void yahtzeeGame(GameWin *wins) {

	/////////////////////
	//		初期設定	 //
	/////////////////////

	// プレイヤーの情報
	Player *player[2];

	// プレイヤー構造体の初期化
	for(int i = 0; i < 2; i++) {
		player[i] = createPlayer();
	}

	GValue *g_value = createGameValue();

	SValue score_value;
	initScoreValue(&score_value);
	SBPlace s_place;
	setScoreBoardPlace(&s_place);

	DiceStruct *dice = createDiceStruct();

	// CPUのキューを定義
	Queue *cpu_queue = createQueue();
	// 初期化し、準備しておく
	initCPUActionQueue(cpu_queue);

	/////////////////////
	//		開始		//
	/////////////////////

	sizeError(wins);
	// 画面表示
	gameScreen(wins->main_win, s_place.x,s_place.y);
	wrefresh(wins->main_win);
	initDisplayTotalScore(wins->main_win, s_place.x, s_place.y, score_value.bonus_border);

	// 名前の初期設定
	inputName(wins->main_win, s_place.x, s_place.y, getComputer(), player[0], 0);
	inputName(wins->main_win, s_place.x, s_place.y, getComputer(), player[1], 1);


	if(getDebugMode()) {
		debugVariable(wins->second_win, g_value);
	}

	while((!isFull(player[0]) || !isFull(player[1])) && g_value->input_key != 'q') {

		displayPlayerTurn(wins->main_win, s_place.x, s_place.y, g_value->p_turn);

		// 入力を初期化
		while ((g_value->input_key = wgetch(wins->main_win)) != ERR) {
        // 何もしない
		}
		g_value->input_key = OK;

		// カーソルの初期設定
		switch(g_value->mode_select) {
			case 1:
				printDiceCursor(wins->main_win, g_value->dice_cursor, countNodes(dice->roll));
				break;
			case 2:
				printKeepDiceCursor(wins->main_win, g_value->keep_cursor);
				break;
			case 3:
				printScoreCursor(wins->main_win, s_place.x, s_place.y, g_value->score_cursor, g_value->p_turn);
				break;
			default:
				break;
		}

		while(g_value->input_key != '\n' && g_value->input_key != 'q') {
			//カーソル操作処理

			rollDiceSelection(wins, dice, cpu_queue, g_value);

			keepDiceSelection(wins, dice, cpu_queue, g_value);

			scoreBoardSelection(wins, dice, cpu_queue, player, g_value, s_place);

			rerollSelection(wins, dice, cpu_queue, g_value);
		}

		switch(g_value->mode_select) {
			//ENTERキー決定後処理
			case 1:
				OPModeFirst(wins->main_win, g_value, dice);
				break;

			case 2:
				OPModeSecond(wins->main_win, g_value, dice);
				break;

			case 3:
				OPModeThird(wins->main_win, g_value, dice, player[g_value->p_turn], &score_value, s_place, cpu_queue);
				break;

			case 4:
				OPModeFourth(wins->main_win, g_value, dice, player[g_value->p_turn], s_place, cpu_queue);
				break;

			default:
				break;
		}

		// デバッグ表更新
		if(getDebugMode()) {
			debugListReset(wins->second_win);
			debugList(wins->second_win, dice);
			debugVariable(wins->second_win, g_value);
		}

		displayAllKeepDice(wins->main_win, dice->keep, countNodes(dice->keep));
	}
	// 試合結果を表示する
	// 試合結果をファイルに書き込む処理
	if(g_value->input_key != 'q') {
		displayWinner(wins->main_win, player);
		inputHistory(wins->main_win, player);
	}
		// 画面のリセット
	wclear(wins->main_win);
	wclear(wins->second_win);
	wrefresh(wins->main_win);
	wrefresh(wins->second_win);

	// ゲーム終了処理
	// リストを開放する
	freeDiceStruct(dice);
	freeGameValue(g_value);

	// キューを開放
	freeQueue(cpu_queue);

	// メモリを解放
	for(int i = 0; i < 2; i++) {
		freePlayer(player[i]);
	}
}