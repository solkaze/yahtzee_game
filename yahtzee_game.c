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
#include "debag_mode.h"
#include "cpu_queue.h"
#include "message.h"
#include "cpu.h"

#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

static bool trans_keep_score = FALSE;
static bool trans_dice_score = FALSE;

static bool debugMode = FALSE;
static bool vs_cpu_flag = FALSE;

bool getVsCpu();

void yahtzeeGame(WINDOW *win, WINDOW *secondWin) {

	// 入力文字の格納
	int ch = ERR;
	// ターン数を制御する変数
	int turn = 1;
	int screen_x, screen_y;

	// プレイヤーの情報
	Player *player[2];

	// プレイヤー構造体の初期化
	for(int i = 0; i < 2; i++) {
		initializePlayer(&player[i]);
	}

	// Playerのターンを決定
	int player_turn = 0;

	// カーソル位置の決定
	int dice_cursor = 0;
	int keep_cursor = 0;
	int score_cursor = initScoreCursor(player[player_turn]);

	// スコア管理
	int total_score[2] = {0};
	int sub_total_score[2] = {0};

	// 振り直し管理
	int reroll_max = 3;
	int reroll_count = reroll_max;

	//* どの選択をしているか
	//* 1:サイコロ選択(キープするかどうか)
	//* 2:キープしたサイコロの選択
	//* 3:役を決定する
	//* 4:振り直しを選択する
	int mode_select = 4;

	int init_dice = 5;
	int reroll_dice = init_dice;
	int keep_dice = 0;

	int bonus_border = 63;
	int bonus_score = 35;

	//bonusを受け取っているかを判断
	bool is_bonus[2] = {false};

	// サイコロ格納用リスト
	DiceList *dice_list;
	// キープしたサイコロを格納
	DiceList *keep_dice_list;
	// 一次的に格納する
	DiceList *temp_list;
	// 全てのサイコロを保持しているリスト
	DiceList *all_dice_list;

	// CPUのキューを定義
	Queue *cpu_queue = createQueue();
	// 初期化し、準備しておく
	initCPUActionQueue(cpu_queue);

	/////////////////////
	//		開始		//
	/////////////////////

	getmaxyx(win, screen_y, screen_x);
	sizeError(screen_y, screen_x);

	// リストをそれぞれ初期化
	initializeDiceList(&dice_list);
	initializeDiceList(&keep_dice_list);
	initializeDiceList(&temp_list);
	initializeDiceList(&all_dice_list);

	// スコアボードの出力
	// スコアボードの位置
	int board_x = 5;
	int board_y = 3;
	// 画面表示
	gameScreen(win, board_x,board_y);
	wrefresh(win);
	initDisplayTotalScore(win, board_x, board_y, bonus_border);

		// 名前の初期設定
	inputName(win,board_x, board_y, getVsCpu(),player[0], 0);

	inputName(win, board_x, board_y, getVsCpu(), player[1], 1);


	if(debugMode) {
		debugVariable(secondWin, reroll_dice, keep_dice, player_turn, turn);
	}

	while((!isFull(player[0]) || !isFull(player[1])) && ch != 'q') {

		displayPlayerTurn(win, board_x, board_y, player_turn);

		// 入力を初期化
		ch = ERR;

		// カーソルの初期設定
		switch(mode_select) {
			case 1:
				printDiceCursor(win, dice_cursor, countNodes(dice_list));
				break;
			case 2:
				printKeepDiceCursor(win, keep_cursor);
				break;
			case 3:
				printScoreCursor(win, board_x, board_y, score_cursor, player_turn);
				break;
			default:
				break;
		}

		while(ch != '\n' && ch != 'q') {

			// キープするサイコロを選ぶ
			while(ch != '\n' && mode_select == 1 && ch != 'q') {

				if(ch != ERR) {
					printDiceCursor(win, dice_cursor, countNodes(dice_list));
				}

				if(debugMode) {
					debugList(secondWin, temp_list, dice_list, keep_dice_list);
				}

				if(getVsCpu() && player_turn == 1) {
					ch = CPUAction(cpu_queue);
				}
				else {
					ch = wgetch(win);
				}


				getmaxyx(win, screen_y, screen_x);
				sizeError(screen_y, screen_x);

				// 入力キーによって操作を変える
				switch(ch) {
					case KEY_LEFT:
						// 左端でなえればカーソル移動を行う
						if(dice_cursor != 0) {
							// 現在のカーソルを消去した後にカウントを下げる
							eraseDiceCursor(win, dice_cursor, reroll_dice);
							dice_cursor--;
						}
						else {
							//左端の場合は得点表に移動する
							eraseDiceCursor(win, dice_cursor, reroll_dice);

							mode_select = 3;
							trans_dice_score = true;
							//カーソル位置の初期化
							//dice_cursor = 0;
						}
						break;

					case KEY_RIGHT:
						if(dice_cursor != reroll_dice - 1) {
							eraseDiceCursor(win, dice_cursor, reroll_dice);
							dice_cursor++;
						}
						break;
					case KEY_UP:
						if(keep_dice != 0) {
							eraseDiceCursor(win, dice_cursor, reroll_dice);
							// キープしたサイコロへ移動
							mode_select = 2;
							// カーソル位置を初期化
							//!dice_cursor = 0;
						}
						break;
					case KEY_DOWN:
						eraseDiceCursor(win, dice_cursor, reroll_dice);
						// 振り直し選択へ移動
						mode_select = 4;
						// カーソル位置を初期化
						//!dice_cursor = 0;
						break;
					case '\n':
						// カーソルを消す
						eraseDiceCursor(win, dice_cursor, reroll_dice);
						// 端の場合はカーソル位置を調整する
						break;
					default:
						break;
				}
			}

			// キープしたサイコロを戻すか選ぶ
			while(ch != '\n' && mode_select == 2 && ch != 'q') {

				if(ch != ERR) {
					printKeepDiceCursor(win, keep_cursor);
				}

				if(debugMode) {
					debugList(secondWin, temp_list, dice_list, keep_dice_list);
				}

				if(getVsCpu() && player_turn == 1) {
					ch = CPUAction(cpu_queue);
				}
				else {
					ch = wgetch(win);
				}

				getmaxyx(win, screen_y, screen_x);
				sizeError(screen_y, screen_x);

				// 入力によって操作を変える
				switch(ch) {
					case KEY_LEFT:
						if(keep_cursor != 0) {
							eraseKeepDiceCursor(win, keep_cursor);
							keep_cursor--;
						}
						else {
							// 左端の場合は得点表に移動する
							mode_select = 3;

							eraseKeepDiceCursor(win, keep_cursor);
							trans_keep_score = true;
							//カーソル位置の初期化
							//keep_cursor = 0;
						}
						break;
					case KEY_RIGHT:
						if(keep_cursor != keep_dice - 1) {
							eraseKeepDiceCursor(win, keep_cursor);
							keep_cursor++;
						}
						break;
					case KEY_DOWN:
						if(reroll_dice != 0) {
							eraseKeepDiceCursor(win, keep_cursor);
							// サイコロ選択へ移動
							mode_select = 1;
							// カーソル位置を初期化
							//keep_cursor = 0;
						}
						break;
					case '\n' :
						eraseKeepDiceCursor(win, keep_cursor);
						break;
					default:
						break;
				}
			}

			// 得点表の操作
			while (ch != '\n' && mode_select == 3 && ch != 'q') {
				int temp_cursor = score_cursor;

				if(debugMode) {
					debugList(secondWin, temp_list, dice_list, keep_dice_list);
				}

				if(ch != ERR) {
					printScoreCursor(win, board_x, board_y, score_cursor, player_turn);
				}

				if(getVsCpu() && player_turn == 1) {
					ch = CPUAction(cpu_queue);
				}
				else {
					ch = wgetch(win);
				}

				getmaxyx(win, screen_y, screen_x);
				sizeError(screen_y, screen_x);

				switch(ch) {
					case KEY_UP:
						score_cursor = skipScoreCursor(player[player_turn], score_cursor, score_cursor, ch);
						if(temp_cursor != score_cursor) {
							eraseScoreCursor(win, board_x, board_y, temp_cursor, player_turn);
						}
						break;

					case KEY_DOWN:
						score_cursor = skipScoreCursor(player[player_turn], score_cursor, score_cursor, ch);
						if(temp_cursor != score_cursor) {
							eraseScoreCursor(win, board_x, board_y, temp_cursor, player_turn);
						}
						break;

					case KEY_RIGHT:
						if(reroll_count != 0) {
							if(trans_dice_score) {
								eraseScoreCursor(win, board_x, board_y, score_cursor, player_turn);
								mode_select = 1;
								trans_dice_score = false;
							}
							else if(trans_keep_score) {
								eraseScoreCursor(win, board_x, board_y, score_cursor, player_turn);
								mode_select = 2;
								trans_keep_score = false;
							}
							else {
								mode_select = 4;
							}
						}
						break;
					case '\n':
						eraseScoreCursor(win, board_x, board_y, score_cursor, player_turn);
					default:
						break;
				}
			}

			// 振り直しの処理
			while(ch != '\n' && mode_select == 4 && ch != 'q') {

				printRerollCursor(win);
				// サイコロを振る
				if(countNodes(temp_list) == 0) {
					for(int i = 0; i < reroll_dice; i++) {
						addNodeAtBeginning(&temp_list, rollDice());
					}
				}
				else {
					for(int i = 0; i < reroll_dice; i++) {
						updateNodeAt(temp_list, i, rollDice());
					}
				}
				usleep(30000);
				if(debugMode) {
					debugList(secondWin, temp_list, dice_list, keep_dice_list);
				}

				if(getVsCpu() && player_turn == 1) {
					ch = CPUAction(cpu_queue);
				}
				else {
					ch = wgetch(win);
				}

				// エンターキーが入力されたら値を保持して抜ける
				if(ch == '\n' || ch == 'q') {
					break;
				}
				if(ch == KEY_UP && countNodes(dice_list) != 0) {
					freeList(&temp_list);
					eraseRerollCursor(win);
					mode_select = 1;
				}

				getmaxyx(win, screen_y, screen_x);
				sizeError(screen_y, screen_x);
			}
		}


		switch(mode_select) {
			case 1:
				eraseAllDice(win, countNodes(dice_list));
				eraseAllKeepDice(win, countNodes(keep_dice_list));

				transferNode(&dice_list, &keep_dice_list, dice_cursor);
				reroll_dice = countNodes(dice_list);
				keep_dice = countNodes(keep_dice_list);
				if(dice_cursor >= reroll_dice && reroll_dice != 0) {
					dice_cursor--;
				}
				if(reroll_dice == 0) {
					mode_select = 2;
					// カーソル位置の初期化
					dice_cursor = 0;
				}
				displayAllDice(win, dice_list, countNodes(dice_list));

				break;

			case 2:
				eraseAllDice(win, reroll_dice);
				eraseAllKeepDice(win, keep_dice);

				transferInOrderNode(&keep_dice_list, &dice_list, keep_cursor);
				// 振りなおすサイコロの数をセット
				reroll_dice = countNodes(dice_list);
				keep_dice = countNodes(keep_dice_list);
				if(keep_cursor >= keep_dice && keep_cursor != 0) {
					keep_cursor--;
				}
				if(countNodes(keep_dice_list) == 0) {
					mode_select = 1;
					// カーソル位置の初期化
					keep_cursor = 0;
				}
				displayAllDice(win, dice_list, countNodes(dice_list));

				break;

			case 3:
				mergeLists(&all_dice_list, dice_list, keep_dice_list);

				// 得点を入れる処理
				switch(score_cursor) {
					case 0:
						setAce(all_dice_list, player[player_turn]);
						break;
					case 1:
						setDeuce(all_dice_list, player[player_turn]);
						break;
					case 2:
						setTrey(all_dice_list, player[player_turn]);
						break;
					case 3:
						setFour(all_dice_list, player[player_turn]);
						break;
					case 4:
						setFive(all_dice_list, player[player_turn]);
						break;
					case 5:
						setSix(all_dice_list, player[player_turn]);
						break;
					case 6:
						setChoice(all_dice_list, player[player_turn]);
						break;
					case 7:
						setFourDice(all_dice_list, player[player_turn]);
						break;
					case 8:
						setFullHouse(all_dice_list, player[player_turn]);
						break;
					case 9:
						setSmallStraight(all_dice_list, player[player_turn]);
						break;
					case 10:
						setBigStraight(all_dice_list, player[player_turn]);
						break;
					case 11:
						setYahtzee(all_dice_list, player[player_turn]);
						break;
					default:
						break;
				}
				// リストをすべてリセット
				freeList(&dice_list);
				freeList(&keep_dice_list);
				freeList(&all_dice_list);


				//得点を計算し格納する
				calcTotalScore(player[player_turn]);

				displayScore(win, board_x, board_y, player[player_turn], player_turn);

				// 出目の予測値をリセット
				erasePredictionScore(win, board_x, board_y, player[player_turn], player_turn);

				// サイコロの表示を消去
				eraseAllDiceAnimate(win, reroll_dice);
				eraseAllKeepDiceAnimate(win, keep_dice);

				// 振りなおすサイコロのリセット
				reroll_dice = init_dice;

				// キープしたサイコロを初期化する
				keep_dice = countNodes(keep_dice_list);

				// 得点を構造体へ入れる
				calcTotalScore(player[player_turn]);

				// 小計を表示する
				sub_total_score[player_turn] = displaySubTotalScoreAnimate(win, board_x, board_y, sub_total_score[player_turn], player[player_turn], player_turn);

				if(calcSubTotalScore(player[player_turn]) >= bonus_border && !is_bonus[player_turn]) {
					is_bonus[player_turn] = true;

					displayBonusScore(win, board_x, board_y, bonus_score, player_turn);
				}

				if(getVsCpu() && player_turn == 1) {
					initCPUActionQueue(cpu_queue);
				}

				// 得点を表示する
				total_score[player_turn] = displayTotalScoreAnimate(win, board_x, board_y, total_score[player_turn], player[player_turn], player_turn);

				eraseRerollMessage(win);
				// プレイヤーを交代する
				if(player_turn == 0) {
					player_turn = 1;
				}
				else {
					player_turn = 0;
					turn++;
				}

				// モードを振り直しにセット
				mode_select = 4;

				// スコアのカーソルをリセット
				score_cursor = initScoreCursor(player[player_turn]);


				// 振り直し回数もリセット
				reroll_count = reroll_max;

				break;

			case 4:
				// 振り直したサイコロのカーソルを消す
				eraseRerollCursor(win);
				// サイコロの表示を消す
				if(countNodes(dice_list) != 0) {
					usleep(10000);
					eraseAllDiceAnimate(win, reroll_dice);
				}

				// サイコロの表をリセット
				// 振り直したサイコロを再度代入する処理
				freeList(&dice_list);
				copyList(temp_list, &dice_list);
				reroll_dice = countNodes(dice_list);
				// 一次的に保持していたリストを開放する
				freeList(&temp_list);

				// 全てのサイコロをいったん保持する
				mergeLists(&all_dice_list, dice_list, keep_dice_list);

				displayAllDiceAnimate(win, dice_list, reroll_dice);
				sleep(1);
				sortList(&dice_list);
				eraseAllDiceAnimate(win, reroll_dice);
				displayAllDiceAnimate(win, dice_list, reroll_dice);

				// サイコロを振ると振りなおせる回数が減る
				reroll_count--;
				displayRerollMessage(win, reroll_count);
				//サイコロを振ると必ず選択画面へ移動
				dice_cursor = 0;

				// まだ振りなおせる場合はモードを1に
				if(reroll_count > 0) {
					mode_select = 1;
				}
				// 無理ならば得点表に移動
				else {
					mode_select = 3;
				}

				score_cursor = initScoreCursor(player[player_turn]);
				// 予想店を表示
				displayPredictionScore(win, board_x, board_y, all_dice_list, player[player_turn], player_turn);
				// 役がそろっていたら表示する
				if(checkFunctions(all_dice_list)) {
					displayMessage(win, all_dice_list, player[player_turn]);
					// そのままなら消えてしまうため戻す処理を行う
					displayAllDice(win, dice_list, countNodes(dice_list));
				}
				if(getVsCpu() && player_turn == 1) {
					CPUActionDecision(cpu_queue, dice_list, keep_dice_list, player[player_turn], reroll_count);
				}
				// 全てのリストをいったんリセットする
				freeList(&all_dice_list);

				break;

			default:
				break;
		}

		// デバッグ表更新
		if(debugMode) {
			// デバッグモード設定
			setUpdateDice(TRUE);
			debugList(secondWin, temp_list, dice_list, keep_dice_list);
			debugVariable(secondWin, reroll_dice, keep_dice, player_turn, turn);
		}

		displayAllKeepDice(win, keep_dice_list, countNodes(keep_dice_list));
	}

	if(calcTotalScore(player[0]) > calcTotalScore(player[1]) && ch != 'q') {
		displayWinMessage(win, player[0]);
	}
	else if(calcTotalScore(player[1]) > calcTotalScore(player[0]) && ch != 'q') {
		displayWinMessage(win, player[1]);
	}
	else if(ch != 'q') {
		displayDrawMessage(win);
	}

	// ゲーム終了処理
	// リストを開放する
	freeList(&dice_list);
	freeList(&keep_dice_list);
	freeList(&temp_list);
	freeList(&all_dice_list);

	// キューを開放
	freeQueue(cpu_queue);

	// 画面のリセット
	werase(win);
	wrefresh(win);


	// 試合結果をファイルに書き込む処理
	if(ch != 'q') {
		inputHistory(win, player);
	}

	// メモリを解放
	for(int i = 0; i < 2; i++) {
		freePlayer(player[i]);
	}

}

// デバッグモードを管理
void setDebagMode(bool mode) {
	debugMode = mode;
}

bool getDebagMode(void) {
	return debugMode;
}

void setVsCpu(bool flag) {
	vs_cpu_flag = flag;
}
bool getVsCpu() {
	return vs_cpu_flag;
}