#include <ncurses.h>
#include <unistd.h>

#include "score.h"
#include "op_score_list.h"
#include "operation_score.h"
#include "game_screen.h"
#include "game_score.h"
#include "screen_place.h"
#include "name.h"
#include "window_struct.h"
#include "error.h"

// 処理開始層

void scoreScreen(GameWin *wins) {

	// スクリーンの初期化
	initScoreScreen(wins->main_win);

	ScoreList *score_history;

	int x, y;
	getmaxyx(wins->main_win, y, x);

	int ch = ERR;

	// 履歴を確認するかタイトルへ戻るか
	int score_select = 0;
	// 履歴を参照するためのカーソル
	int history_select = 0;

	int adjust_x = 10;
	int adjust_y = (- 20);

	int board_x = x/2 + adjust_x;
	int board_y = y/2 + adjust_y;

	// リストを初期化する
	initializeScoreList(&score_history);

	// スコアテキストファイルから情報を取得する
	readListFromFile(wins->main_win, &score_history, "data/score.txt");

	int history_max = countScoreNode(score_history) - 1;

	createScoreScreen(wins->main_win, history_max + 1);

	displayPage(wins->main_win, history_select + 1);


	printScoreboard(wins->main_win, board_x, board_y);

	// スコアの履歴を表示
	displayScoreHistory(wins->main_win, score_history, history_select, board_x, board_y);

	// カーソル表示
	displayHistoryFrame(wins->main_win);
	displayHistoryItemCursor(wins->main_win, score_select);
	displayPageCursor(wins->main_win, score_select, history_select, history_max);

	// セレクトが2の時にenterを入力すると終了するようにする
	while(ch != '\n' || score_select != 1) {

		// セレクト0の処理
		while(score_select == 0) {

			sizeError(wins);

			if(ch != ERR) {
				displayPageCursor(wins->main_win, score_select, history_select, history_max);
			}

			if(ch != ERR && ch != KEY_LEFT && ch != KEY_RIGHT) {
				displayHistoryItemCursor(wins->main_win, score_select);
			}

			ch = wgetch(wins->main_win);

			// 途中入力の処理
			switch(ch) {
				case KEY_DOWN:
				// 下を押したときの処理
					eraseHistoryItemCursor(wins->main_win, score_select);
					score_select = 1;
					break;
				case KEY_LEFT:
				// 左を押したときの処理
					if(history_select > 0) {
						eraseHistoryTotalScore(wins->main_win, board_x, board_y);
						eraseScoreHistory(wins->main_win, board_x, board_y);
						history_select--;
					}
					else {
						ch = ERR;
					}
					break;
				case KEY_RIGHT:
				// 右を押したときの処理
					if(history_select < history_max) {
						eraseHistoryTotalScore(wins->main_win, board_x, board_y);
						eraseScoreHistory(wins->main_win, board_x, board_y);
						history_select++;
					}
					else {
						ch = ERR;
					}
					break;
				default:
					ch = ERR;
					break;
			}
			// 表示を変更する処理
			if(ch != ERR && ch != KEY_DOWN) {
				displayPage(wins->main_win, history_select + 1);
				displayScoreHistory(wins->main_win, score_history, history_select, board_x, board_y);
			}
		}

		// セレクト2の処理
		// タイトルへ戻る
		while(ch != '\n' && score_select == 1) {

			if(ch != ERR) {
				displayPageCursor(wins->main_win, score_select, history_select, history_max);
				displayHistoryItemCursor(wins->main_win, score_select);
			}

			ch =wgetch(wins->main_win);

			switch(ch) {
				case KEY_UP:
					eraseHistoryItemCursor(wins->main_win, score_select);
					score_select = 0;
					break;
				case '\n':
					break;
				default:
					ch = ERR;
					break;
			}
		}
	}

	freeScoreList(&score_history);
	initScoreScreen(wins->main_win);
}