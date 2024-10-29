#include <ncurses.h>
#include <time.h>
#include <locale.h>

#include "dice_list.h"
#include "dice.h"
#include "create.h"
#include "operation_dice.h"
#include "screen_place.h"
#include "time_sleep.h"

// すべてのサイコロを表示する関数
void displayAllDice(WINDOW *win, DiceList *dice, int num);

void displayAllDiceAnimate(WINDOW *win, DiceList *dice, int num);
// すべてのサイコロを画面から消去する関数
void eraseAllDice(WINDOW *win, int num);
// アニメーションを加えつつ消す関数
void eraseAllDiceAnimate(WINDOW *win, int num);

// 全てのキープしたサイコロを表示する
void displayAllKeepDice(WINDOW *win, DiceList *dice, int num);
// キープしたサイコロをすべて消す
void eraseAllKeepDice(WINDOW *win, int num);
// アニメーションを加えつつ消す
void eraseAllKeepDiceAnimate(WINDOW *win, int num);


// 全てのサイコロを一列に表示する
void displayAllDice(WINDOW *win, DiceList *dice, int num) {
	int size_x, size_y;

	getmaxyx(win, size_y, size_x);

	for(int i=0; i<num; i++){
		displayDice(win, getNodeAt(dice, i), getDiceX(size_x, i, num), getDiceY(size_y));
	}
	wrefresh(win);
}

// アニメーションを加えつつ表示
void displayAllDiceAnimate(WINDOW *win, DiceList *dice, int num) {
	int size_x, size_y;

	getmaxyx(win, size_y, size_x);

	for(int i=0; i<num; i++){
		displayDice(win, getNodeAt(dice, i), getDiceX(size_x, i, num), getDiceY(size_y));
		sleep_microseconds(70000);
		wrefresh(win);
	}
}

// 表示されているダイスをすべて消す関数
void eraseAllDice(WINDOW *win, int num) {
	int size_x, size_y;

	getmaxyx(win, size_y, size_x);

	for(int i = 0; i < num; i++) {
		eraseDice(win, getDiceX(size_x, i, num), getDiceY(size_y));
	}
	wrefresh(win);
}

// アニメーションを加えつつ消す関数
void eraseAllDiceAnimate(WINDOW *win, int num) {
	int size_x, size_y;

	getmaxyx(win, size_y, size_x);

	for(int i = 0; i < num; i++) {
		eraseDice(win, getDiceX(size_x, i, num), getDiceY(size_y));
		sleep_microseconds(80000);
		wrefresh(win);
	}
}

void displayAllKeepDice(WINDOW *win, DiceList *dice, int num) {
	int size_x, size_y;

	getmaxyx(win, size_y, size_x);

	for(int i=0; i<num; i++){
		displayDice(win, getNodeAt(dice, i), getKeepDiceX(size_x, i), getKeepDiceY(size_y));
	}
	wrefresh(win);
}

void eraseAllKeepDice(WINDOW *win, int num) {
	int size_x, size_y;

	getmaxyx(win, size_y, size_x);

	for(int i=0; i<num; i++){
		eraseDice(win, getKeepDiceX(size_x, i), getKeepDiceY(size_y));
	}
	wrefresh(win);
}

// アニメーションを加えつつ消す
void eraseAllKeepDiceAnimate(WINDOW *win, int num) {
	int size_x, size_y;

	getmaxyx(win, size_y, size_x);

	for(int i=0; i<num; i++){
		eraseDice(win, getKeepDiceX(size_x, i), getKeepDiceY(size_y));
		sleep_microseconds(80000);
		wrefresh(win);
	}
}