#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>

#include "player.h"
#include "screen_place.h"

#define NAME_LENGTH 12

void inputName(WINDOW *win,int x, int y, bool cpu, Player *pl, int turn);

void displayInputNameFrame(WINDOW *win);

// 枠まで消す
void eraseInputNameFrame(WINDOW *win);

void displayPlayerName(WINDOW *win,int x, int y, Player *pl, int turn);

void setSetting(WINDOW *win) {
	echo();
	nodelay(win, FALSE);
	keypad(win, FALSE);
	curs_set(1);
	nocbreak();
}

void resetSetting(WINDOW *win) {
	noecho();
	nodelay(win, TRUE);
	keypad(win, TRUE);
	curs_set(0);
	cbreak();
}

void inputName(WINDOW *win,int x, int y, bool cpu, Player *pl, int turn) {

	int start_x, start_y;
	getMessagePlace(&start_x, &start_y);
	int width = 73;
	int height = 7;

	WINDOW *name_win = derwin(win, height, width, start_y, start_x);
	box(name_win, 0, 0);
	wrefresh(name_win);


	bool name_success = false;

	// 名前登録時の設定有効化
	setSetting(win);

	while(!name_success) {
		char name[NAME_LENGTH];
		memset(name, '\0', sizeof(name));

		mvwprintw(name_win, 1, 1, "Player%dを入力してください(半角12文字 ，全角4文字以内)", turn + 1);

		int name_input_place_x = 1;
		int name_input_delay = 3;
		int name_input_place_y = 3;
		// 入力
		mvwprintw(name_win,  name_input_place_y, name_input_place_x, ">> ");
		wrefresh(name_win);
		wmove(name_win,  name_input_place_y, name_input_place_x + name_input_delay);
		if(turn == 0 || !cpu) {
			wgetnstr(name_win, name, NAME_LENGTH);
		}

		if(turn == 0) {
			// もし何も入力されなかったときの処理
			if(strlen(name) == 0) {
				pl->name = strdup("player1");
				wrefresh(name_win);
				name_success = true;
			}
			else if(strlen(name) > NAME_LENGTH) {
				werase(name_win);
				box(name_win, 0, 0);
				mvwprintw(name_win, 1, 1, "文字数制限に達しました　入力をやり直してください");
				wrefresh(name_win);
				sleep(1);
			}
			else {
				pl->name = strdup(name);
				name_success = true;
			}
		}
		else if(turn == 1) {
			if(cpu) {
				pl->name = strdup("CPU");
				name_success = true;
			}
			else if(strlen(name) == 0) {
				pl->name = strdup("player2");
				wrefresh(name_win);
				name_success = true;
			}
			else if(strlen(name) > NAME_LENGTH) {
				werase(name_win);
				box(name_win, 0, 0);
				mvwprintw(name_win, 1, 1, "文字数制限に達しました　入力をやり直してください");
				wrefresh(name_win);
				sleep(1);
			}
			else {
				pl->name = strdup(name);
				name_success = true;
			}
		}
	}


	// 名前登録用の設定無効化
	werase(name_win);
	delwin(name_win);
	resetSetting(win);
	wrefresh(win);
	displayPlayerName(win,x, y, pl, turn);

}

void displayPlayerName(WINDOW *win,int x, int y, Player *pl, int turn) {

	int start_x = getNamePlaceX(x, turn);
	int start_y = getNamePlaceY(y);

	mvwprintw(win, start_y, start_x, "%s", pl->name);
	wrefresh(win);
}