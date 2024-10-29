#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>

#include "title.h"
#include "screen_place.h"
#include "time_sleep.h"

//描画用関数を定義

// ロゴを表示する関数
void printYahtzee(WINDOW *win);
// メニュー表示をする関数
void printMenu(WINDOW *win);
// メニューカーソルを表示する関数
void printMenuCursor(WINDOW *win, int cursor);
// カーソルを消す関数
void deleteTitleCursor(WINDOW *win,int cursor);

void printMenuFrame(WINDOW *win);

///////////////////////////////////
//								 //
//			タイトル画面			//
//                         		 //
///////////////////////////////////

char *menu[5];

//int blinking_counter = 0;

void displayTitleScreen(WINDOW *win, int select) {
		box(win, 0, 0);
		printYahtzee(win);
		printMenu(win);
		printMenuFrame(win);
		printMenuCursor(win, select);
		wrefresh(win);
}


void printYahtzee(WINDOW *win) {
	int title_x, title_y;
	getmaxyx(win, title_y, title_x);

	char *title[30];

	title[0] =  "    .------------------..------------------..------------------..------------------..------------------..------------------..------------------.";
	title[1] =  "   / .--------------. // .--------------. // .--------------. // .--------------. // .--------------. // .--------------. // .--------------. /|";
	title[2] =  "  / /              / // /              / // /              / // /              / // /              / // /              / // /              / / |";
	title[3] =  " /  '-------------' //  '-------------' //  '-------------' //  '-------------' //  '-------------' //  '-------------' //  '-------------' /  |";
	title[4] =  " .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.    |";
	title[5] =  "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |   |";
	title[6] =  "| |  ____  ____  | || |      __      | || |  ____  ____  | || |  _________   | || |   ________   | || |  _________   | || |  _________   | |   |";
	title[7] =  "| | |_  _||_  _| | || |     /  \\     | || | |_   ||   _| | || | |  _   _  |  | || |  |  __   _|  | || | |_   ___  |  | || | |_   ___  |  | |   |";
	title[8] =  "| |   \\ \\  / /   | || |    / /\\ \\    | || |   | |__| |   | || | |_/ | | \\_|  | || |  |_/  / /    | || |   | |_  \\_|  | || |   | |_  \\_|  | |   |";
	title[9] =  "| |    \\ \\/ /    | || |   / ____ \\   | || |   |  __  |   | || |     | |      | || |     .'.' _   | || |   |  _|  _   | || |   |  _|  _   | |   |";
	title[10] = "| |    _|  |_    | || | _/ /    \\ \\_ | || |  _| |  | |_  | || |    _| |_     | || |   _/ /__/ |  | || |  _| |___/ |  | || |  _| |___/ |  | |   '";
	title[11] = "| |   |______|   | || ||____|  |____|| || | |____||____| | || |   |_____|    | || |  |________|  | || | |_________|  | || | |_________|  | |  / ";
	title[12] = "| |              | || |              | || |              | || |              | || |              | || |              | || |              | | /  ";
	title[13] = "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |/   ";
	title[14] = " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'     ";
	title[15] = "                                         .----------------.  .----------------.  .----------------.    |                                        ";
	title[16] = "                                        | .--------------. || .--------------. || .--------------. |   |                                        ";
	title[17] = "                                        | |   ________   | || |              | || |    _         | |   |                                        ";
	title[18] = "                                        | |  |______  |  | || |              | || |   | |        | |   |                                        ";
	title[19] = "                                        | |   ______| |  | || |   _  _   _   | || |   | |_____   | |   |                                        ";
	title[20] = "                                        | |  |______  |  | || |  |_||_| / /  | || |   |  _____|  | |   |                                        ";
	title[21] = "                                        | |   ______| |  | || |        / /   | || |   | |        | |   '                                        ";
	title[22] = "                                        | |  |________|  | || |       /_/    | || |   |_|        | |  /                                         ";
	title[23] = "                                        | |              | || |              | || |              | | /                                          ";
	title[24] = "                                        | '--------------' || '--------------' || '--------------' |/                                           ";
	title[25] = "                                         '----------------'  '----------------'  '----------------'                                             ";



	for (int i = 0; i < 26; i++) {
		mvwprintw(win, title_y / 2 - 18 + i, (title_x - strlen(title[i])) / 2, "%s", title[i]);
	}





	wrefresh(win);

}

void printMenu(WINDOW *win) {
	int placeX[5], placeY;
	getMenuPlace(win, placeX, &placeY);

	//メニューボード
	menu[0] = "ＣＰＵ対戦";
	menu[1] = "２人対戦";
	menu[2] = "ヘルプ";
	menu[3] = "対戦履歴";
	menu[4] = "ゲーム終了";

	for (int i = 0; i < 5; i++) {
		mvwprintw(win, placeY, placeX[i], "%s", menu[i]);
	}

	wrefresh(win);

}

void printMenuCursor(WINDOW *win, int cursor) {
	int length = 19;
	int top_delay = (-2);
	int bottom_delay = 2;
	int left_delay = (-4);

	int placeX[5], placeY;
	getMenuPlace(win, placeX, &placeY);

	// 矢印キーが入力されたときのみ更新する
		// 前のカーソル位置を保持する
		// 上かっこ
		wattrset(win, COLOR_PAIR(3));
		mvwaddch(win, placeY + top_delay, placeX[cursor] + left_delay, ACS_ULCORNER);
		mvwaddch(win, placeY + bottom_delay, placeX[cursor] + left_delay, ACS_LLCORNER);
		for(int i = 1; i <= length; i++) {
			mvwaddch(win, placeY + top_delay, placeX[cursor] + left_delay + i, ACS_HLINE);
			mvwaddch(win, placeY + bottom_delay, placeX[cursor] + left_delay + i, ACS_HLINE);
			wrefresh(win);
			sleep_microseconds(10000);
		}
		wattrset(win, 0);

		wrefresh(win);
}

// カーソルを消去する
void deleteTitleCursor(WINDOW *win,int cursor) {
	int placeX[5], placeY;
	getMenuPlace(win, placeX, &placeY);
	int length = 20;
	int top_delay = (-2);
	int bottom_delay = 2;
	int left_delay = (-4);
	mvwhline(win, placeY + top_delay, placeX[cursor] + left_delay, ' ', length);
	mvwhline(win, placeY + bottom_delay, placeX[cursor] + left_delay, ' ', length);
	wrefresh(win);
}

void printMenuFrame(WINDOW *win) {
	int placeX[5], placeY;
	getMenuPlace(win, placeX, &placeY);
	int length = 14;
	int top_delay = (-1);
	int bottom_delay = 1;
	int left_delay = (-2);
	wattrset(win, COLOR_PAIR(6));
	for(int i = 0; i < 5; i++) {
		mvwaddch(win, placeY + top_delay, placeX[i] + left_delay, ACS_ULCORNER);
		whline(win, ACS_HLINE, length);
		mvwaddch(win, placeY, placeX[i] + left_delay, ACS_VLINE);
		// 下かっこ
		mvwaddch(win, placeY + bottom_delay, placeX[i] + left_delay, ACS_LLCORNER);
		whline(win, ACS_HLINE, length);
	}
	wattrset(win, 0);

	wrefresh(win);
}