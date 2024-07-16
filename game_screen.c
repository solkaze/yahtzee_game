#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "game_screen.h"
#include "operation_dice.h"
#include "screen_place.h"

void printScoreboard(WINDOW *win, int x, int y);
void keepDiceFrame(WINDOW *win);
void rerollPoint(WINDOW *win);
void displayRerollMessage(WINDOW *win, int reroll_count);

void gameScreen(WINDOW *win, int x, int y) {
	werase(win);
	box(win, 0, 0);
	printScoreboard(win, x, y);
	keepDiceFrame(win);
	rerollPoint(win);
	wrefresh(win);
}

void printScoreboard(WINDOW *win, int x, int y) {

	int role_name_delay = 2;
	int role_name_y_space = 1;
	// 表の縦線を定義
	int left_v_line = x;
	int sec_v_line = left_v_line + 20;
	int thi_v_line = sec_v_line + 15;
	int right_v_line = thi_v_line + 15;

	// 表の横線を定義
	int num_top_h_line = y;
	int num_sec_h_line = num_top_h_line + 3;
	int num_thi_h_line = num_sec_h_line + 2;
	int num_fou_h_line = num_thi_h_line + 2;
	int num_fif_h_line = num_fou_h_line + 2;
	int num_six_h_line = num_fif_h_line + 2;
	int num_sev_h_line = num_six_h_line + 2;
	int num_eig_h_line = num_sev_h_line + 2;
	int num_nin_h_line = num_eig_h_line + 2;
	int num_bot_h_line = num_nin_h_line + 2;

	//下半分の変数
	int cho_top_h_line = num_bot_h_line + 1;
	int cho_bot_h_line = cho_top_h_line + 2;

	//下部
	int sp_top_h_line = cho_bot_h_line + 1;
	int sp_sec_h_line = sp_top_h_line + 2;
	int sp_thi_h_line = sp_sec_h_line + 2;
	int sp_fou_h_line = sp_thi_h_line + 2;
	int sp_fif_h_line = sp_fou_h_line + 2;
	int sp_bot_h_line = sp_fif_h_line + 2;

	int total_top_h_line = sp_bot_h_line + 1;
	int total_bot_h_line = total_top_h_line + 4;
	//縦線を描画
	mvwvline(win, num_top_h_line + 1, left_v_line, ACS_VLINE, num_bot_h_line - 1);
	mvwvline(win, num_top_h_line + 1, sec_v_line, ACS_VLINE,num_bot_h_line - 1);
	mvwvline(win, num_top_h_line + 1, thi_v_line, ACS_VLINE, num_bot_h_line - 1);
	mvwvline(win, num_top_h_line + 1, right_v_line, ACS_VLINE, num_bot_h_line - 1);

	///////////////////////////////
	//		１から6までの表			//
	//////////////////////////////

	//横線を描画
	mvwhline(win, num_top_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, num_sec_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, num_thi_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, num_fou_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, num_fif_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, num_six_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, num_sev_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, num_eig_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, num_nin_h_line, left_v_line + 1, ACS_BULLET, right_v_line - left_v_line - 1);
	mvwhline(win, num_bot_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);

	// 先の角をきれいに
	// 左
	mvwaddch(win, num_top_h_line, left_v_line, ACS_ULCORNER);
	for(int i = 1; i < 8; i++) {
		mvwaddch(win, i * role_name_y_space*2 + num_top_h_line + 1, left_v_line, ACS_LTEE);
	}
	mvwaddch(win, num_bot_h_line, left_v_line, ACS_LLCORNER);

	mvwaddch(win, num_top_h_line, sec_v_line, ACS_TTEE);
	for(int i = 1; i < 8; i++) {
		mvwaddch(win, i * role_name_y_space*2 + num_top_h_line + 1, sec_v_line, ACS_PLUS);
	}
	mvwaddch(win, num_bot_h_line, sec_v_line, ACS_BTEE);

	mvwaddch(win, num_top_h_line, thi_v_line, ACS_TTEE);
	for(int i = 1; i < 8; i++) {
		mvwaddch(win, i * role_name_y_space*2 + num_top_h_line + 1, thi_v_line, ACS_PLUS);
	}
	mvwaddch(win, num_bot_h_line, thi_v_line, ACS_BTEE);

	mvwaddch(win, num_top_h_line, right_v_line, ACS_URCORNER);
	for(int i = 1; i < 8; i++) {
		mvwaddch(win, i * role_name_y_space*2 + num_top_h_line + 1, right_v_line, ACS_RTEE);
	}
	mvwaddch(win, num_bot_h_line, right_v_line, ACS_LRCORNER);
	// シックスまでの表

	//チョイスの表
	mvwhline(win, cho_top_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, cho_bot_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);

	// チョイス枠の縦ライン
	mvwvline(win, cho_top_h_line + 1, left_v_line, ACS_VLINE, cho_bot_h_line - cho_top_h_line -1);
	mvwvline(win, cho_top_h_line + 1, sec_v_line, ACS_VLINE,cho_bot_h_line - cho_top_h_line-1);
	mvwvline(win, cho_top_h_line + 1, thi_v_line, ACS_VLINE, cho_bot_h_line - cho_top_h_line-1);
	mvwvline(win, cho_top_h_line + 1, right_v_line, ACS_VLINE, cho_bot_h_line - cho_top_h_line-1);

	mvwaddch(win, cho_top_h_line, left_v_line, ACS_ULCORNER);
	mvwaddch(win, cho_top_h_line, sec_v_line, ACS_TTEE);
	mvwaddch(win, cho_top_h_line, thi_v_line, ACS_TTEE);
	mvwaddch(win, cho_top_h_line, right_v_line, ACS_URCORNER);

	mvwaddch(win, cho_bot_h_line, left_v_line, ACS_LLCORNER);
	mvwaddch(win, cho_bot_h_line, sec_v_line, ACS_BTEE);
	mvwaddch(win, cho_bot_h_line, thi_v_line, ACS_BTEE);
	mvwaddch(win, cho_bot_h_line, right_v_line, ACS_LRCORNER);

	////////////////////////////////////
	//		フォーダイスからヨットの表		//
	////////////////////////////////////
	mvwhline(win, sp_top_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, sp_sec_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, sp_thi_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, sp_fou_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, sp_fif_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, sp_bot_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);

	mvwvline(win, sp_top_h_line + 1, left_v_line, ACS_VLINE, sp_bot_h_line - sp_top_h_line - 1);
	mvwvline(win, sp_top_h_line + 1, sec_v_line, ACS_VLINE, sp_bot_h_line - sp_top_h_line - 1);
	mvwvline(win, sp_top_h_line + 1, thi_v_line, ACS_VLINE, sp_bot_h_line - sp_top_h_line - 1);
	mvwvline(win, sp_top_h_line + 1, right_v_line, ACS_VLINE, sp_bot_h_line - sp_top_h_line - 1);

	mvwaddch(win, sp_top_h_line, left_v_line, ACS_ULCORNER);
	for(int i = 1; i < 5; i++) {
		mvwaddch(win, i * role_name_y_space*2 + sp_top_h_line, left_v_line, ACS_LTEE);
	}
	mvwaddch(win, sp_bot_h_line, left_v_line, ACS_LLCORNER);

	mvwaddch(win, sp_top_h_line, sec_v_line, ACS_TTEE);
	for(int i= 1; i < 5; i++) {
		mvwaddch(win, i * role_name_y_space*2 + sp_top_h_line, sec_v_line, ACS_PLUS);
	}
	mvwaddch(win, sp_bot_h_line, sec_v_line, ACS_BTEE);

	mvwaddch(win, sp_top_h_line, thi_v_line, ACS_TTEE);
	for(int i = 1; i < 5; i++) {
		mvwaddch(win, i * role_name_y_space*2 + sp_top_h_line, thi_v_line, ACS_PLUS);
	}
	mvwaddch(win, sp_bot_h_line, thi_v_line, ACS_BTEE);

	mvwaddch(win, sp_top_h_line, right_v_line, ACS_URCORNER);
	for(int i = 1; i < 5; i++) {
		mvwaddch(win, i * role_name_y_space*2 + sp_top_h_line, right_v_line, ACS_RTEE);
	}
	mvwaddch(win, sp_bot_h_line, right_v_line, ACS_LRCORNER);

	////////////////////////////
	//		総合得点			//
	////////////////////////////

	mvwhline(win, total_top_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);
	mvwhline(win, total_bot_h_line, left_v_line + 1, ACS_HLINE, right_v_line - left_v_line - 1);

	mvwvline(win, total_top_h_line + 1, left_v_line, ACS_VLINE, total_bot_h_line - total_top_h_line - 1);
	mvwvline(win, total_top_h_line + 1, sec_v_line, ACS_VLINE, total_bot_h_line - total_top_h_line - 1);
	mvwvline(win, total_top_h_line + 1, thi_v_line, ACS_VLINE, total_bot_h_line - total_top_h_line - 1);
	mvwvline(win, total_top_h_line + 1, right_v_line, ACS_VLINE, total_bot_h_line - total_top_h_line - 1);

	mvwaddch(win, total_top_h_line, left_v_line, ACS_ULCORNER);
	mvwaddch(win, total_bot_h_line, left_v_line, ACS_LLCORNER);
	mvwaddch(win, total_top_h_line, sec_v_line, ACS_TTEE);
	mvwaddch(win, total_bot_h_line, sec_v_line, ACS_BTEE);
	mvwaddch(win, total_top_h_line, thi_v_line, ACS_TTEE);
	mvwaddch(win, total_bot_h_line, thi_v_line, ACS_BTEE);
	mvwaddch(win, total_top_h_line, right_v_line, ACS_URCORNER);
	mvwaddch(win, total_bot_h_line, right_v_line, ACS_LRCORNER);

	////////////////////////////
	//		役名一覧			//
	////////////////////////////
	mvwprintw(win, num_top_h_line + 1, left_v_line + 7, "%s", "プレイヤー名");
	mvwprintw(win, num_top_h_line + 2, left_v_line + role_name_delay, "%s", "役名");
	mvwprintw(win, num_sec_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "エース");
	mvwprintw(win, num_thi_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "デュース");
	mvwprintw(win, num_fou_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "トレイ");
	mvwprintw(win, num_fif_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "フォー");
	mvwprintw(win, num_six_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "ファイブ");
	mvwprintw(win, num_sev_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "シックス");
	mvwprintw(win, num_eig_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "小計");
	mvwprintw(win, num_nin_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "ボーナス");

	mvwprintw(win, cho_top_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "チョイス");

	mvwprintw(win, sp_top_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "フォーダイス");
	mvwprintw(win, sp_sec_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "フルハウス");
	mvwprintw(win, sp_thi_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "S.ストレート");
	mvwprintw(win, sp_fou_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "B.ストレート");
	mvwprintw(win, sp_fif_h_line + role_name_y_space, left_v_line + role_name_delay, "%s", "ヨット");

	mvwprintw(win, total_top_h_line + role_name_y_space*2, left_v_line + role_name_delay, "%s", "総合得点");

	wrefresh(win);
}

void keepDiceFrame(WINDOW *win) {
	int screen_x, screen_y;
	int frame_delay = 24;
	int dice_num = 5;

	getmaxyx(win, screen_y, screen_x);

	int top_h_line = getKeepDiceY(screen_y) -2;
	int bottom_h_line = top_h_line + 11;

	int left_v_line = getKeepDiceX(screen_x, 0) - 4;

	mvwaddch(win, top_h_line, left_v_line, ACS_ULCORNER);
	mvwaddch(win, bottom_h_line, left_v_line, ACS_LLCORNER);
	mvwvline(win, top_h_line + 1, left_v_line, ACS_VLINE, bottom_h_line - top_h_line - 1);

	mvwhline(win, top_h_line, left_v_line + 1, ACS_HLINE, frame_delay * dice_num - 1);
	mvwhline(win, bottom_h_line, left_v_line + 1, ACS_HLINE, frame_delay * dice_num - 1);

	for(int i = 1; i < dice_num; i++) {
		mvwaddch(win, top_h_line, left_v_line  + frame_delay * i, ACS_TTEE);

		mvwvline(win, top_h_line + 1, left_v_line + frame_delay * i, ACS_VLINE, bottom_h_line - top_h_line - 1);

		mvwaddch(win, bottom_h_line, left_v_line + frame_delay * i, ACS_BTEE);
	}

	mvwaddch(win, top_h_line, left_v_line + frame_delay * dice_num, ACS_URCORNER);
	mvwaddch(win, bottom_h_line, left_v_line + frame_delay * dice_num, ACS_LRCORNER);
	mvwvline(win, top_h_line + 1, left_v_line + frame_delay * dice_num, ACS_VLINE, bottom_h_line - top_h_line - 1);

	wrefresh(win);

}

void rerollPoint(WINDOW *win) {
	int place_x, place_y;

	rerollButtonPlace(win,&place_x, &place_y);

	int top_h_line = place_y - 2;
	int left_v_line = place_x - 2;
	int bottom_h_line = top_h_line + 4;
	int v_line_length = 3;
	int line_length = 20;


	char *reroll_message = "サイコロを振る";
	mvwprintw(win, place_y, place_x, "%s", reroll_message);
	mvwvline(win, top_h_line + 1, left_v_line, ACS_VLINE, v_line_length);
	mvwaddch(win, top_h_line, left_v_line, ACS_ULCORNER);
	mvwaddch(win, bottom_h_line, left_v_line, ACS_LLCORNER);
	mvwhline(win, top_h_line, left_v_line + 1, ACS_HLINE, line_length);
	mvwhline(win, bottom_h_line, left_v_line + 1, ACS_HLINE, line_length);
	wrefresh(win);
}

void displayRerollMessage(WINDOW *win, int reroll_count) {
	int place_x, place_y;

	getRerollMessage(win, &place_x, &place_y);

	int left_v_line = place_x - 2;
	int bottom_h_line = place_y + 1;
	int line_length = 21;

	char *reroll_message = "振り直し残り";
	if(reroll_count == 0) {
		mvwprintw(win, place_y, place_x, "%s: ", reroll_message);
		wattrset(win, COLOR_PAIR(1));
		wprintw(win, "%d", reroll_count);
		wattrset(win, 0);
		wprintw(win, "/2");
	}
	else {
		mvwprintw(win, place_y, place_x, "%s: %d/2", reroll_message, reroll_count);
	}
	mvwhline(win, bottom_h_line, left_v_line , ACS_HLINE, line_length);
	wrefresh(win);
}

void eraseRerollMessage(WINDOW *win) {
	int place_x, place_y;
	int length = 17;

	getRerollMessage(win, &place_x, &place_y);

	mvwhline(win, place_y, place_x, ' ', length);
	mvwhline(win, place_y + 1, place_x - 2, ' ', length + 4);
}