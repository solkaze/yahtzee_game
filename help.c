#include "screen_place.h"
#include "operation_help.h"
#include "help.h"

#include <ncurses.h>
#include <unistd.h>

void initHelpScreen(WINDOW *win);

void helpScreen(WINDOW *win) {
	int main_screen_x;
	int main_screen_y;
	int main_start_y;
	int main_start_x;
	int sub_win_height = 41;
	int sub_win_width = 132;
	getmaxyx(win, main_screen_y, main_screen_x);
	getbegyx(win, main_start_y, main_start_x);

	initHelpScreen(win);

	createHelpScreen(win);
	// subwinの開始位置をwinの中央に設定
	int sub_start_y = main_start_y + (main_screen_y - sub_win_height) / 2;
	int sub_start_x = main_start_x + main_screen_x - sub_win_width - 5; // 画面の右端に配置
	WINDOW *sub_win = subwin(win, sub_win_height, sub_win_width, sub_start_y, sub_start_x);
	box(sub_win, 0, 0);
	wrefresh(sub_win);

	int help_select = 0;
	int ch;

	// カーソルの初期設定
	displayHelpFrame(win);
	readFile(sub_win, "rule.txt", sub_win_width - 2, 0, 0);
	displayHelpItemCursor(win, help_select);

	while(ch != '\n' || help_select != 3) {

		while(help_select == 0) {

			if(ch != ERR) {
				readFile(sub_win, "rule.txt", sub_win_width - 2, 0, 0);
				displayHelpItemCursor(win, help_select);
			}

			ch = wgetch(win);

			switch(ch) {
				case KEY_DOWN:
					eraseHelpItemCursor(win, help_select);
					help_select++;
					initHelpScreen(sub_win);
					break;
				default:
					ch = ERR;
					break;
			}
		}

		while(help_select == 1) {

			if(ch != ERR) {
				readFile(sub_win, "operation.txt", sub_win_width - 2, 0, 0);
				displayHelpItemCursor(win, help_select);
			}

			ch = wgetch(win);

			switch(ch) {
				case KEY_UP:
					eraseHelpItemCursor(win, help_select);
					help_select--;
					initHelpScreen(sub_win);
					break;

				case KEY_DOWN:
					eraseHelpItemCursor(win, help_select);
					help_select++;
					initHelpScreen(sub_win);
					break;
				default:
					ch = ERR;
					break;
			}
		}

		while(help_select == 2) {

			if(ch != ERR) {
				readFile(sub_win, "role.txt", sub_win_width - 2, 0, 0);
				displayHelpItemCursor(win, help_select);
			}

			ch = wgetch(win);

			switch(ch) {
				case KEY_UP:
					eraseHelpItemCursor(win, help_select);
					help_select--;
					initHelpScreen(sub_win);
					break;

				case KEY_DOWN:
					eraseHelpItemCursor(win, help_select);
					help_select++;
					initHelpScreen(sub_win);
					break;
				default:
					ch = ERR;
					break;
			}
		}

		while(ch != '\n' && help_select == 3) {

			if(ch != ERR) {
				displayHelpItemCursor(win, help_select);
			}

			ch = wgetch(win);

			switch(ch) {
				case KEY_UP:
					eraseHelpItemCursor(win, help_select);
					help_select--;
					initHelpScreen(sub_win);
					break;
				case '\n':
					break;
				default:
					ch = ERR;
					break;
			}
		}
	}
	wrefresh(sub_win);
	wclear(sub_win);
	delwin(sub_win);

	initHelpScreen(win);
}

// 画面の初期化
void initHelpScreen(WINDOW *win) {
	werase(win);
	box(win, 0,0);
	wrefresh(win);
}