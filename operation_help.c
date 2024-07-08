#include "operation_help.h"
#include "error.h"
#include "screen_place.h"

#include <locale.h>
#include <stdio.h>
#include <wchar.h>
#include <errno.h>
#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

int readFile(WINDOW *win, const char *filename, int max_length, int subwin_x, int subwin_y) {
	setlocale(LC_ALL, ""); // ロケールを設定してマルチバイト文字を扱えるようにする

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		notFoundError(win, filename);
		return 1;
	}

	wchar_t wline[4096]; // ワイド文字列用のバッファ
	char MBline[4096];   // マルチバイト文字列用のバッファ
	int x = subwin_x + 1;
	int y = subwin_y + 1;

	wmove(win, y, x); // サブウィンドウの中での開始位置にカーソルを移動

	while (fgets(MBline, sizeof(MBline), file) != NULL) {
		size_t len = mbstowcs(wline, MBline, sizeof(wline) / sizeof(wchar_t));
		if (len == (size_t)-1) {
			operationFileError(win);
			fclose(file);
			return 1;
		}

		int current_length = 0;
		for (size_t i = 0; i < len; ++i) {
			if (wline[i] == L'\n') {
				y++;
				wmove(win, y, x); // 改行後の位置を設定
				current_length = 0;
			} else {
				if (current_length >= max_length / 2) {
					y++;
					wmove(win, y, x); // 改行後の位置を設定
					current_length = 0;
				}
				wprintw(win, "%lc", wline[i]); // 全角文字を出力
				current_length++;
			}
		}
	}

	fclose(file);
	wrefresh(win);
	return 0;
}

void createHelpScreen(WINDOW *win) {

	int screen_x;
	int screen_y;

	getmaxyx(win, screen_y, screen_x);
	int x = screen_x/2;
	int adjust_line_x = (-50);

	char *item[4] = {"ルール", "操作方法", "役一覧", "タイトルへ戻る"};
	mvwaddch(win, 0, x + adjust_line_x, ACS_TTEE);
	mvwvline(win, 1, x + adjust_line_x, ACS_VLINE, screen_y - 2);
	mvwaddch(win, screen_y - 1, x + adjust_line_x, ACS_BTEE);

	// 項目の処理
	int placeX;
	int placeY[4];

	getHelpItemCursorPlace(win, placeY, &placeX);

	mvwprintw(win, placeY[0], placeX, "%s", item[0]);
	mvwprintw(win, placeY[1], placeX, "%s", item[1]);
	mvwprintw(win, placeY[2], placeX, "%s", item[2]);
	mvwprintw(win, placeY[3], placeX, "%s", item[3]);

	wrefresh(win);
}

void displayHelpItemCursor(WINDOW *win, int select) {
	int placeX;
	int placeY[4];

	getHelpItemCursorPlace(win, placeY, &placeX);

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
		usleep(10000);
	}

	wattrset(win, 0);
	wrefresh(win);
}

void displayHelpFrame(WINDOW *win) {
			// 項目の処理
	int placeX;
	int placeY[4];

	getHelpItemCursorPlace(win, placeY, &placeX);

		int length = 20;
	int top_delay = (-1);
	int bottom_delay = 1;
	int left_delay = (-2);
	wattrset(win, COLOR_PAIR(6));
	for(int i = 0; i < 4; i++) {
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

void eraseHelpItemCursor(WINDOW *win, int select) {


	int placeX;
	int placeY[4];

	getHelpItemCursorPlace(win, placeY, &placeX);

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