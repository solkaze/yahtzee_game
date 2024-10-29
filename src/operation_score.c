#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "operation_score.h"
#include "op_score_list.h"
#include "screen_place.h"
#include "time_sleep.h"

// 1試合の対戦結果を表示する
void displayScoreHistory(WINDOW *win, ScoreList *score_list, int history_select, int x, int y) {


	int player_1 = 0;
	int player_2 = 1;
	displayHistoryScore(win, x, y, score_list, player_1, history_select);
	displayHistoryScore(win, x, y, score_list, player_2, history_select);
	displayHistoryName(win, x, y, score_list, player_1, history_select);
	displayHistoryName(win, x, y, score_list, player_2, history_select);
	displayHistoryTotalScore(win, x, y, score_list, player_1, history_select);
	displayHistoryTotalScore(win, x, y, score_list, player_2, history_select);
	wrefresh(win);

}

// リセットのために表示を一旦消す
void eraseScoreHistory(WINDOW *win, int x, int y) {

	int placeX[2];
	int placeY[12];
	int player_1 = 0;
	int player_2 = 1;
	int h_length = 6;
	getScorePlaceX(x, placeX);
	getScorePlaceY(y, placeY);
	for (int i = 0; i < 12; i++) {
		mvwhline(win, placeY[i],placeX[player_1], ' ', h_length);
	}

	for (int i = 0; i < 12; i++) {
		mvwhline(win, placeY[i],placeX[player_2], ' ', h_length);
	}

	// 名前部分を消去する処理
	int start_x = getNamePlaceX(x, player_1);
	int start_y = getNamePlaceY(y);
	int n_length = 12;
	mvwhline(win, start_y, start_x, ' ', n_length);
	start_x = getNamePlaceX(x, player_2);
	mvwhline(win, start_y, start_x, ' ', n_length);
}

// 画面の初期化
void initScoreScreen(WINDOW *win) {
	wclear(win);
	box(win, 0,0);
	wrefresh(win);
}

// ページ番号を表示する
void displayPage(WINDOW *win, int history_select) {
	int screen_x = 29;
	int screen_y = 3;

	mvwprintw(win, screen_y, screen_x, "%2d", history_select);
}

void createScoreScreen(WINDOW *win, int history_select_max) {

	int screen_x;
	int screen_y;

	getmaxyx(win, screen_y, screen_x);
	int x = screen_x/2;
	int adjust_line_x = (-30);

	char *item[2] = {"ゲーム履歴", "タイトルへ戻る"};
	int h_line_y = 6;
	mvwaddch(win, 0, x + adjust_line_x, ACS_TTEE);
	mvwvline(win, 1, x + adjust_line_x, ACS_VLINE, screen_y - 2);
	mvwaddch(win, screen_y - 1, x + adjust_line_x, ACS_BTEE);
	mvwaddch(win, h_line_y, 0, ACS_LTEE);
	mvwhline(win, h_line_y, 1, ACS_HLINE, x + adjust_line_x - 1);
	mvwaddch(win, h_line_y, x + adjust_line_x, ACS_RTEE);

	// 項目の処理
	int placeX;
	int placeY[2];

	getScoreItemCursorPlace(win, &placeX, placeY);

	mvwprintw(win, placeY[0], placeX, "%s", item[0]);
	mvwprintw(win, placeY[1], placeX, "%s", item[1]);

	int screen_page_x = placeX + 10;
	int screen_page_y = 3;

	mvwprintw(win, screen_page_y, screen_page_x, "/ %d", history_select_max);
	wrefresh(win);
}

// 履歴のメージ移動のカーソルを表示する関数
void displayPageCursor(WINDOW *win, int select, int history_select, int history_max) {
	// 項目の処理
	int placeX;
	int placeY[2];

	int top_delay = (-3);
	int left_delay = (-2);
	int right_delay = 18;

	getScoreItemCursorPlace(win,&placeX, placeY);
	// カーソルが0のときのみ表示する
	wattrset(win, COLOR_PAIR(3));
	if(select == 0) {
		if(history_select == 0) {
			mvwprintw(win, placeY[0] + top_delay, placeX + left_delay, "  ");
			mvwprintw(win, placeY[0] + top_delay, placeX + right_delay, ">>");
		}
		else if(history_select == history_max) {
			mvwprintw(win, placeY[0] + top_delay, placeX + left_delay, "<<");
			mvwprintw(win, placeY[0] + top_delay, placeX + right_delay, "  ");
		}
		else{
			mvwprintw(win, placeY[0] + top_delay, placeX + left_delay, "<<");
			mvwprintw(win, placeY[0] + top_delay, placeX + right_delay, ">>");
		}
	}
	else {
		mvwprintw(win, placeY[0] + top_delay, placeX + left_delay, "  ");
		mvwprintw(win, placeY[0] + top_delay, placeX + right_delay, "  ");
	}

	wattrset(win, COLOR_PAIR(3));

	wattrset(win, 0);
	wrefresh(win);

}

// 表示選択におけるカーソルの表示
void displayHistoryItemCursor(WINDOW *win, int select) {

		// 項目の処理
	int placeX;
	int placeY[2];

	getScoreItemCursorPlace(win, &placeX, placeY);

	int top_delay = (-2);
	int bottom_delay = 2;

	int left_delay = (-4);
	int line_length = 24;

	wattrset(win, COLOR_PAIR(3));
	mvwaddch(win, placeY[select] + top_delay, placeX + left_delay, ACS_ULCORNER);

	mvwaddch(win, placeY[select] + bottom_delay, placeX + left_delay, ACS_LLCORNER);
	for(int i = 1; i <= line_length; i++) {
		mvwaddch(win, placeY[select] + top_delay, placeX + left_delay + i, ACS_HLINE);
		mvwaddch(win, placeY[select] + bottom_delay, placeX + left_delay + i, ACS_HLINE);
		wrefresh(win);
		sleep_microseconds(10000);
	}

	wattrset(win, 0);
	wrefresh(win);

}

void displayHistoryFrame(WINDOW *win) {
			// 項目の処理
	int placeX;
	int placeY[2];

	getScoreItemCursorPlace(win, &placeX, placeY);

		int length = 20;
	int top_delay = (-1);
	int bottom_delay = 1;
	int left_delay = (-2);
	wattrset(win, COLOR_PAIR(6));
	for(int i = 0; i < 2; i++) {
		mvwaddch(win, placeY[i] + top_delay, placeX + left_delay, ACS_ULCORNER);
		whline(win, ACS_HLINE, length);
		mvwaddch(win, placeY[i], placeX + left_delay, ACS_VLINE);
		// 下かっこ
		mvwaddch(win, placeY[i] + bottom_delay, placeX + left_delay, ACS_LLCORNER);
		whline(win, ACS_HLINE, length);
	}
	wattrset(win, 0);

	wrefresh(win);
}

void eraseHistoryItemCursor(WINDOW *win, int select) {


	int placeX;
	int placeY[2];

	getScoreItemCursorPlace(win, &placeX, placeY);

	int top_delay = (-2);
	int bottom_delay = 2;

	int left_delay = (-4);
	int line_length = 24;

	mvwaddch(win, placeY[select] + top_delay, placeX + left_delay, ' ');
	mvwhline(win, placeY[select] + top_delay, placeX + left_delay + 1, ' ', line_length);
	mvwaddch(win, placeY[select] + top_delay, placeX + left_delay + line_length + 1, ' ');

	mvwaddch(win, placeY[select] + bottom_delay, placeX + left_delay, ' ');
	mvwhline(win, placeY[select] + bottom_delay, placeX + left_delay + 1, ' ', line_length);
	mvwaddch(win, placeY[select] + bottom_delay, placeX + left_delay + line_length + 1, ' ');

	wrefresh(win);

}

// 得点を表示する
void displayHistoryScore(WINDOW *win, int x, int y, ScoreList *head, int turn, int index) {
	ScoreList *temp = head;
	int placeX[2];
	int placeY[12];
	getScorePlaceX(x, placeX);
	getScorePlaceY(y, placeY);

		// 指定されたインデックスのノードまで移動する
	for (int i = 0; i < index && temp != NULL; i++) {
		temp = temp->next;
	}

	if (temp == NULL) {
		// 指定されたインデックスがリストの範囲外の場合のエラーハンドリングなどをここに追加する
		// この例では何もしない
		return;
	}

	int scores[] = {
		temp->players[turn].ace, temp->players[turn].deuce,
		temp->players[turn].trey, temp->players[turn].four,
		temp->players[turn].five, temp->players[turn].six,
		temp->players[turn].choice, temp->players[turn].four_dice,
		temp->players[turn].full_house, temp->players[turn].small_straight,
		temp->players[turn].big_straight, temp->players[turn].yahtzee
	};

	for (int i = 0; i < 12; i++) {
		if (scores[i] != EMPTY) {
			mvwprintw(win, placeY[i], placeX[turn], "%2d", scores[i]);
		}
	}
}

void displayHistoryName(WINDOW *win, int x, int y, ScoreList *head, int turn, int index) {
	ScoreList *temp = head;
	int start_x = getNamePlaceX(x, turn);
	int start_y = getNamePlaceY(y);

	// 指定場所まで移動する
	for (int i = 0; i < index && temp != NULL; i++) {
		temp = temp->next;
	}

	if (temp == NULL) {

		return;
	}

	char *name = temp->players[turn].name;

	mvwprintw(win, start_y, start_x, "%s", name);
}

void displayHistoryTotalScore(WINDOW *win, int x, int y, ScoreList *head, int turn,int index) {
	ScoreList *temp = head;
	int placeX[2];
	int placeY[3];

	// ボーナス点
	int point = 35;
	int boarder = 63;
	getScorePlaceX(x, placeX);
	getTotalScorePlaceY(y, placeY);
		// 指定場所まで移動する
	for (int i = 0; i < index && temp != NULL; i++) {
		temp = temp->next;
	}

	if (temp == NULL) {

		return;
	}

	int total = calcTotalScore(&temp->players[turn]);

	int subTotal = calcSubTotalScore(&temp->players[turn]);

	mvwprintw(win, placeY[0], placeX[turn] - 2, "%2d / %2d", subTotal, boarder);

	if(subTotal >= boarder) {
		mvwprintw(win, placeY[1], placeX[turn], "+%2d", point);
		wrefresh(win);
	}
	else {
		mvwprintw(win, placeY[1], placeX[turn], "   ");
		wrefresh(win);
	}

	mvwprintw(win, placeY[2], placeX[turn], "%d", total);
	wrefresh(win);
}

void eraseHistoryTotalScore(WINDOW *win, int x, int y) {
	int placeX[2];
	int placeY[3];

	int player_1 = 0;
	int player_2 = 1;

	getScorePlaceX(x, placeX);
	getTotalScorePlaceY(y, placeY);


	mvwprintw(win, placeY[0], placeX[player_1] - 2, "   ");
	mvwprintw(win, placeY[1], placeX[player_1], "   ");
	mvwprintw(win, placeY[2], placeX[player_1], "   ");
	mvwprintw(win, placeY[0], placeX[player_2] - 2, "   ");
	mvwprintw(win, placeY[1], placeX[player_2], "   ");
	mvwprintw(win, placeY[2], placeX[player_2], "   ");
	wrefresh(win);
}