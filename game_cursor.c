#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>

#include "game_cursor.h"
#include "operation_dice.h"
#include "player.h"
#include "screen_place.h"

#ifdef EMPTY
#undef EMPTY
#endif
#define EMPTY (-1)

// カーソルの形を定義する
void diceCursorShape(WINDOW *win, int x, int y) {
	// 取得するのはサイコロの左上の座標とする
	int cursor_x = x - 2;
	int cursor_y = y - 1;
	int right_cursor_x = 20;
	int under_cursor_y = 6;
	int bottom_cursor_y = 3;

	// カラーをセット

	mvwaddch(win, cursor_y, cursor_x, ACS_ULCORNER | COLOR_PAIR(3));

	for(int i = 1; i < 6; i++) {
		mvwaddch(win, cursor_y, cursor_x + i, ACS_HLINE | COLOR_PAIR(3));
	}

	for(int i = 1; i < 6; i++) {
		mvwaddch(win, cursor_y, cursor_x + i + 14, ACS_HLINE | COLOR_PAIR(3));
	}

	mvwaddch(win, cursor_y, cursor_x + right_cursor_x, ACS_URCORNER | COLOR_PAIR(3));

	for(int i = 1; i < 3; i++) {
		mvwaddch(win, cursor_y + i, cursor_x, ACS_VLINE | COLOR_PAIR(3));
		mvwaddch(win, cursor_y + i, cursor_x + right_cursor_x, ACS_VLINE | COLOR_PAIR(3));
	}

	for(int i = 1; i < 3; i++) {
		mvwaddch(win, cursor_y + i + under_cursor_y, cursor_x, ACS_VLINE | COLOR_PAIR(3));
		mvwaddch(win, cursor_y + i + under_cursor_y, cursor_x + right_cursor_x, ACS_VLINE | COLOR_PAIR(3));
	}

	mvwaddch(win, cursor_y + under_cursor_y + bottom_cursor_y, cursor_x, ACS_LLCORNER | COLOR_PAIR(3));

	for(int i = 1; i < 6; i++) {
		mvwaddch(win, cursor_y + under_cursor_y + bottom_cursor_y, cursor_x + i, ACS_HLINE | COLOR_PAIR(3));
	}

	for(int i = 1; i < 6; i++) {
		mvwaddch(win, cursor_y + under_cursor_y + bottom_cursor_y, cursor_x + i + 14, ACS_HLINE | COLOR_PAIR(3));
	}

	mvwaddch(win, cursor_y + under_cursor_y + bottom_cursor_y, cursor_x + right_cursor_x, ACS_LRCORNER | COLOR_PAIR(3));

	wrefresh(win);
}


// サイコロの上にあるカーソルを消去する
void deleteDiceCursor(WINDOW *win,int x, int y) {
	int cursor_x = x - 2;
	int cursor_y = y - 1;
	int right_cursor_x = 20;
	int bottom_cursor_y = 9;
	int dice_x_size = 20;
	int dice_y_size = 10;

	mvwhline(win, cursor_y, cursor_x, ' ', dice_x_size);
	mvwvline(win, cursor_y, cursor_x, ' ', dice_y_size);
	mvwhline(win, cursor_y + bottom_cursor_y, cursor_x, ' ', dice_x_size);
	mvwvline(win, cursor_y, cursor_x + right_cursor_x, ' ', dice_y_size);
}

// サイコロの形を表示する
// el : 表示する要素番目
//num : 最大のサイコロの数
void printDiceCursor(WINDOW *win,int el, int num) {
	int x, y;

	getmaxyx(win, y, x);
	diceCursorShape(win, getDiceX(x, el, num), getDiceY(y));
}

void printKeepDiceCursor(WINDOW *win,int el) {
	int x, y;

	getmaxyx(win, y, x);
	diceCursorShape(win, getKeepDiceX(x, el), getKeepDiceY(y));
}

void eraseDiceCursor(WINDOW *win,int el, int num) {
	int x, y;

	getmaxyx(win, y, x);
	deleteDiceCursor(win, getDiceX(x, el, num), getDiceY(y));
}

void eraseKeepDiceCursor(WINDOW *win,int el) {
	int x, y;

	getmaxyx(win, y, x);
	deleteDiceCursor(win, getKeepDiceX(x, el), getKeepDiceY(y));
}

// num:得点の位置を示す変数
// turn:プレイヤーのターン
void printScoreCursor(WINDOW *win,int x,int y, int num, int turn) {

	int placeX[2];
	int placeY[12];

	getCursorPlaceX(x, placeX);
	getCursorPlaceY(y, placeY);

	// Playerによって変える
	mvwaddch(win, placeY[num], placeX[turn], '[' | COLOR_PAIR(3));
	mvwaddch(win, placeY[num], placeX[turn] + 11, ']' | COLOR_PAIR(3));
	wrefresh(win);
}

void eraseScoreCursor(WINDOW *win, int x, int y, int num, int turn) {

	int placeX[2];
	int placeY[12];

	getCursorPlaceX(x, placeX);
	getCursorPlaceY(y, placeY);

	mvwaddch(win, placeY[num], placeX[turn], ' ' | COLOR_PAIR(3));
	mvwaddch(win, placeY[num], placeX[turn] + 11, ' ' | COLOR_PAIR(3));
	wrefresh(win);
}

// すでに点数が入っているところへ再度入らないようにする
int skipScoreCursor(Player *pl, int num, int key, int select) {
	switch(num) {
		case 0:  // エース
			switch(select) {
				case KEY_UP:
					if (pl->ace != EMPTY) {
						num = key;
					}
					break;
				case KEY_DOWN:
					num++;
					if (pl->deuce != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
			}
			break;

		case 1:  // デュース
			switch(select) {
				case KEY_UP:
					num--;
					if (pl->ace != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
				case KEY_DOWN:
					num++;
					if (pl->trey != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
			}
			break;

		case 2:  // トレイ
			switch(select) {
				case KEY_UP:
					num--;
					if (pl->deuce != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
				case KEY_DOWN:
					num++;
					if (pl->four != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
			}
			break;

		case 3:  // フォー
			switch(select) {
				case KEY_UP:
					num--;
					if (pl->trey != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
				case KEY_DOWN:
					num++;
					if (pl->five != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
			}
			break;

		case 4:  // ファイブ
			switch(select) {
				case KEY_UP:
					num--;
					if (pl->four != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
				case KEY_DOWN:
					num++;
					if (pl->six != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
			}
			break;

		case 5:  // シックス
			switch(select) {
				case KEY_UP:
					num--;
					if (pl->five != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
				case KEY_DOWN:
					num++;
					if (pl->choice != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
			}
			break;

		case 6:  // チョイス
			switch(select) {
				case KEY_UP:
					num--;
					if (pl->six != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
				case KEY_DOWN:
					num++;
					if (pl->four_dice != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
			}
			break;

		case 7:  // フォーダイス
			switch(select) {
				case KEY_UP:
					num--;
					if (pl->choice != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
				case KEY_DOWN:
					num++;
					if (pl->full_house != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
			}
			break;

		case 8:  // フルハウス
			switch(select) {
				case KEY_UP:
					num--;
					if (pl->four_dice != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
				case KEY_DOWN:
					num++;
					if (pl->small_straight != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
			}
			break;

		case 9:  // S.ストレート
			switch(select) {
				case KEY_UP:
					num--;
					if (pl->full_house != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
				case KEY_DOWN:
					num++;
					if (pl->big_straight != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
			}
			break;

		case 10:  // B.ストレート
			switch(select) {
				case KEY_UP:
					num--;
					if (pl->small_straight != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
				case KEY_DOWN:
					num++;
					if (pl->yahtzee != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
			}
			break;

		case 11:  // ヨット
			switch(select) {
				case KEY_UP:
					num--;
					if (pl->big_straight != EMPTY) {
						num = skipScoreCursor(pl, num, key, select);
					}
					break;
				case KEY_DOWN:
					if (pl->yahtzee != EMPTY) {
						num = key;
					}
					break;
			}
			break;
	}

	return num;
}

// 得点表のカーソル位置をリセットする
int initScoreCursor(Player *pl) {
	int count = 0;
	int *scores[] = { &pl->ace, &pl->deuce, &pl->trey, &pl->four, &pl->five, &pl->six,
						&pl->choice, &pl->four_dice, &pl->full_house, &pl->small_straight,
						&pl->big_straight, &pl->yahtzee };
	int length = sizeof(scores) / sizeof(scores[0]);

	for(int i = 0; i < length; i++) {
		if(*scores[i] == EMPTY) {
			return count;
		}
		count++;
	}
	return count;
}

// ふりなおしのカーソル表示
void printRerollCursor(WINDOW *win) {
	int screen_x, screen_y;

	rerollButtonPlace(win, &screen_x, &screen_y);

	int top_h_line = screen_y - 3;
	int left_v_line = screen_x - 4;
	int bottom_h_line = top_h_line + 6;
	int h_line_length = 25;

	// カラーをセット
	wattron(win, COLOR_PAIR(3));

	mvwaddch(win, top_h_line, left_v_line, ACS_ULCORNER);
	mvwaddch(win, bottom_h_line, left_v_line, ACS_LLCORNER);
	mvwhline(win, top_h_line, left_v_line + 1, ACS_HLINE, h_line_length);
	mvwhline(win, bottom_h_line, left_v_line + 1, ACS_HLINE, h_line_length);

	wattroff(win, COLOR_PAIR(3));
	wrefresh(win);
}

void eraseRerollCursor(WINDOW *win) {
	int screen_x, screen_y;

	rerollButtonPlace(win, &screen_x, &screen_y);

	int top_h_line = screen_y - 3;
	int left_v_line = screen_x - 4;
	int bottom_h_line = top_h_line + 6;
	int h_line_length = 26;

	mvwhline(win, top_h_line, left_v_line, ' ', h_line_length);
	mvwhline(win, bottom_h_line, left_v_line, ' ', h_line_length);

	wrefresh(win);
}

void displayPlayerTurn(WINDOW *win, int x, int y, int turn) {
	int line_length = 12;
	// カラーをセット
	wattron(win, COLOR_PAIR(3));
	if(turn == 0) {
		mvwhline(win, getNamePlaceY(y) + 1, getNamePlaceX(x, turn), '=', line_length);
		mvwhline(win, getNamePlaceY(y) + 1, getNamePlaceX(x, turn + 1), ' ', line_length);
	}
	else {
		mvwhline(win, getNamePlaceY(y) + 1, getNamePlaceX(x, turn), '=', line_length);
		mvwhline(win, getNamePlaceY(y) + 1, getNamePlaceX(x, turn - 1), ' ', line_length);
	}
	wattrset(win, 0); // 初期色に戻す
	wrefresh(win);
}