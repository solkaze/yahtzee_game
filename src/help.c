#include <ncurses.h>
#include <unistd.h>

#include "screen_place.h"
#include "operation_help.h"
#include "help.h"
#include "window_struct.h"
#include "error.h"

void initHelpScreen(WINDOW *win);

void helpScreen(GameWin *wins) {
	int main_screen_x;
	int main_screen_y;
	int main_start_y;
	int main_start_x;
	int sub_win_height = 41;
	int sub_win_width = 132;
	getmaxyx(wins->main_win, main_screen_y, main_screen_x);
	getbegyx(wins->main_win, main_start_y, main_start_x);

	initHelpScreen(wins->main_win);

	createHelpScreen(wins->main_win);
	// subwinの開始位置をwinの中央に設定
	int sub_start_y = main_start_y + (main_screen_y - sub_win_height) / 2;
	int sub_start_x = main_start_x + main_screen_x - sub_win_width - 5; // 画面の右端に配置
	WINDOW *sub_win = subwin(wins->main_win, sub_win_height, sub_win_width, sub_start_y, sub_start_x);
	box(sub_win, 0, 0);
	wrefresh(sub_win);

	int help_select = 0;
	int ch = ERR;

	// カーソルの初期設定
	displayHelpFrame(wins->main_win);
	readFile(sub_win, "data/rule.txt", sub_win_width - 2, 0, 0);
	displayHelpItemCursor(wins->main_win, help_select);

	while(ch != '\n' || help_select != 3) {

		while(help_select == 0) {

			sizeError(wins);

			if(ch != ERR) {
				readFile(sub_win, "data/rule.txt", sub_win_width - 2, 0, 0);
				displayHelpItemCursor(wins->main_win, help_select);
			}

			ch = wgetch(wins->main_win);

			switch(ch) {
				case KEY_DOWN:
					eraseHelpItemCursor(wins->main_win, help_select);
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
				readFile(sub_win, "data/operation.txt", sub_win_width - 2, 0, 0);
				displayHelpItemCursor(wins->main_win, help_select);
			}

			ch = wgetch(wins->main_win);

			switch(ch) {
				case KEY_UP:
					eraseHelpItemCursor(wins->main_win, help_select);
					help_select--;
					initHelpScreen(sub_win);
					break;

				case KEY_DOWN:
					eraseHelpItemCursor(wins->main_win, help_select);
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
				readFile(sub_win, "data/role.txt", sub_win_width - 2, 0, 0);
				displayHelpItemCursor(wins->main_win, help_select);
			}

			ch = wgetch(wins->main_win);

			switch(ch) {
				case KEY_UP:
					eraseHelpItemCursor(wins->main_win, help_select);
					help_select--;
					initHelpScreen(sub_win);
					break;

				case KEY_DOWN:
					eraseHelpItemCursor(wins->main_win, help_select);
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
				displayHelpItemCursor(wins->main_win, help_select);
			}

			ch = wgetch(wins->main_win);

			switch(ch) {
				case KEY_UP:
					eraseHelpItemCursor(wins->main_win, help_select);
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

	initHelpScreen(wins->main_win);
}

// 画面の初期化
void initHelpScreen(WINDOW *win) {
	werase(win);
	box(win, 0,0);
	wrefresh(win);
}