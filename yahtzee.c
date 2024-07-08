#include "error.h"
#include "title.h"
#include "game_screen.h"
#include "create.h"
#include "yahtzee_game.h"
#include "score.h"
#include "help.h"


#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <getopt.h>

// 色の要素を初期化
void initColor();
// 「ヨット」ゲーム起動
void run(WINDOW *win, WINDOW *secondWin);

void initModule();

void initWindowModule(WINDOW *win);
//////////////////////////////////////
//                                  //
//              main関数             //
//                                  //
//////////////////////////////////////

int main(int argc, char *argv[]) {

	WINDOW *secondWin = NULL;
	//WINDOW *ThirdWin = NULL;

	// 開始処理
	initModule();

	// 色を初期化
	initColor();

	// コマンドライン処理
	int ch;

	while ((ch = getopt(argc, argv, "d")) != -1) {
		switch (ch) {
		case 'd':
			setDebagMode(TRUE);
			break;
		default:
			argumentsError(argv);
			break;
		}
	}
	// getopt が -1 を返した後に optind が argc より小さい場合、未定の引数が存在する
	if (optind < argc) {
		argumentsError(argv);
	}

	// ウィンドウの作成処理
	int win_height = 50;
	int win_width = 186;
	int start_y = (LINES - win_height) / 2; // 中央に配置
	int start_x;

	if(getDebagMode()) {
		start_x = COLS - win_width;
	}
	else {
		start_x = (COLS - win_width) / 2;// 中央に配置
	}

	WINDOW *win = newwin(win_height, win_width, start_y, start_x);

	if(getDebagMode()) {
		int sub_start_x = 0;
		int sub_win_width = COLS - win_width;
		secondWin = newwin(win_height, sub_win_width, start_y, sub_start_x);
		box(secondWin, 0, 0);
		wrefresh(secondWin);
	}

	initWindowModule(win);
	// ゲーム起動
	run(win, secondWin);

	// 終了処理
	// 終了処理
	if (secondWin != NULL) {
		delwin(secondWin);
	}
	delwin(win);
	endwin();

	return 0;
}
void initModule() {
	setlocale(LC_ALL, "");  // 文字コードをUTF-8に設定
	initscr();              // スクリーンを初期化
	cbreak();               // 入力バッファを使用しない(Enterを押さない)
	noecho();               // 入力文字を表示しない
	curs_set(0);            // カーソルを表示しない
	start_color();          // 色を利用する
	initRandom();
}

void initWindowModule(WINDOW *win) {
	keypad(win, TRUE);   // キーボード入力を受け付ける
	nodelay(win, TRUE); // 入力を待たない
	box(win, 0, 0);
	wrefresh(win);
}

// 色の初期設定
void initColor() {
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	return;
}
//////////////////////////////////////
//                                  //
//              run関数              //
//                                  //
//////////////////////////////////////

void run(WINDOW *win, WINDOW *secondWin) {
	// 画面サイズ縦と横
	int screen_height, screen_width;

	///////////////////////
	//      タイトル画面    //
	///////////////////////

	// menu選択
	int menu_select = 0;
	int menu_max = 4;
	int ch = ERR;
	int temp_select = menu_select;


	while(menu_select != menu_max) {
		menu_select = 0;
		box(win, 0, 0);
		printYahtzee(win);
		printMenu(win);
		printTitleFrame(win);
		printTitleCursor(win, menu_select);
		wrefresh(win);

		while(ch != '\n') {

			getmaxyx(win, screen_height, screen_width);
			//毎度画面サイズが正しいか判断する
			sizeError(screen_height, screen_width);

			if(ch != ERR && menu_select != temp_select) {
				printTitleCursor(win, menu_select);
			}

			temp_select = menu_select;

			// 入力の受付
			ch = wgetch(win);

			switch(ch) {
				case KEY_LEFT:
				// カーソルを左に移動
				if(menu_select != 0) {
					deleteTitleCursor(win, menu_select);
					menu_select--;
				}
					break;

				case KEY_RIGHT:
				// カーソルを右に移動
				if(menu_select != menu_max) {
					deleteTitleCursor(win, menu_select);
					menu_select++;
				}
					break;
			}
		}

		// タイトル選択の作動
		switch(menu_select) {
			case 0:
				// 「cpuスタート」を選択
				//printStart();
				setVsCpu(TRUE);
				yahtzeeGame(win, secondWin);
				break;

			case 1:
				// 「2人で対戦」を選択
				setVsCpu(FALSE);
				yahtzeeGame(win, secondWin);
				break;

			case 2:
				// 「ヘルプ」を選択
				helpScreen(win);
				break;

			case 3:
				// 「スコア」を選択
				scoreScreen(win);
				break;

			case 4:
				// 「終了」を選択
				break;
		}
		// 入力文字リセット
		ch = ERR;
	}
	return;
}