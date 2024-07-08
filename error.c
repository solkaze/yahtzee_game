#include "error.h"

// エラー処理用ファイル
#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void argumentsError(char *argv[]) {
		mvprintw(0,0,"オプションまたは引数が間違っています：「 %s -(オプション) 」 で起動してください\n", argv[0]);
		mvprintw(2, 0, "・[-d]:デバッグモード\n");
		refresh();
		sleep(3);
		endwin();
		exit(EXIT_FAILURE);
	return;
}

void sizeError(int height, int width) {
	// 必要となる画面サイズ
	int need_width = 184, need_height = 42;

	if (width < need_width || height < need_height) {
		clear();
		mvprintw(0, 0, "ゲームに必要な画面サイズが足りません\n");
		mvprintw(1, 0, "必要サイズは %d x %d です\n", need_width, need_height);
		refresh();
		sleep(3);
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