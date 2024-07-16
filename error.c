#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "error.h"
#include "debug_mode.h"
#include "window_struct.h"

// エラー処理用ファイル

void argumentsError(char *argv[]) {
		mvprintw(0,0,"オプションまたは引数が間違っています：「 %s -(オプション) 」 で起動してください\n", argv[0]);
		mvprintw(2, 0, "・[-d]:デバッグモード\n");
		refresh();
		sleep(3);
		endwin();
		exit(EXIT_FAILURE);
	return;
}

void sizeError(GameWin *wins) {
	// 必要となる画面サイズ
	int screen_x, screen_y;
	int s_screen_x = 0;
	int s_screen_y = 0;
	getmaxyx(wins->main_win, screen_y, screen_x);
	if(wins->second_win != NULL) {
		getmaxyx(wins->second_win, s_screen_y, s_screen_x);
	}
	int need_width = 186, need_height = 50;
	if(getDebugMode()) {
		need_width += 40;
	}

	if (screen_x + s_screen_x < need_width || screen_y + s_screen_y < need_height) {
		clear();
		mvprintw(0, 0, "ゲームに必要な画面サイズが足りません\n");
		mvprintw(1, 0, "必要サイズは %d x %d です\n", need_width, need_height);
		refresh();
		sleep(2);
		endwin();
		exit(EXIT_FAILURE);
	}
	return;
}

// スコアファイルが見つからなかったときのエラー処理
void scoreFileError(WINDOW *win) {
		werase(win);
		wmove(win, 1, 1);
		wprintw(win, "スコアファイル読み込みに失敗しました\n");
		wrefresh(win);
}

void notFoundError(WINDOW *win, const char *name) {
	werase(win);
	wmove(win, 1, 1);
	wprintw(win, "「%s」は見つかりませんでした\n", name);
	wrefresh(win);
}

void operationFileError(WINDOW *win) {
		werase(win);
		wmove(win, 1, 1);
		wprintw(win, "ファイル操作でエラーが発生しました\n");
		wrefresh(win);
}