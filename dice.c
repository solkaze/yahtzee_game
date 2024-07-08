#include "dice.h"
#include "player.h"
#include "dice_list.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

void moduleOne(WINDOW *win, int x, int y);
void moduleTwo(WINDOW *win, int x, int y);
void moduleThree(WINDOW *win, int x, int y);
void moduleFour(WINDOW *win, int x, int y);
void moduleFive(WINDOW *win, int x, int y);
void moduleSix(WINDOW *win, int x, int y);
void moduleSeven(WINDOW *win, int x, int y);
void moduleEight(WINDOW *win, int x, int y);
void moduleNine(WINDOW *win, int x, int y);

void DiceFrame(WINDOW *win, int x, int y);

void displayOne(WINDOW *win, int x, int y);
void displayTwo(WINDOW *win, int x, int y);
void displayThree(WINDOW *win, int x, int y);
void displayFour(WINDOW *win, int x, int y);
void displayFive(WINDOW *win, int x, int y);
void displaySix(WINDOW *win, int x, int y);

void exclusiveOne(WINDOW *win, int x, int y);
void eraseDice(WINDOW *win, int x, int y);


void displayDice(WINDOW *win, int value , int x, int y) {
	DiceFrame(win, x, y);
	switch(value) {
		case 1:
			displayOne(win, x, y);
			break;
		case 2:
			displayTwo(win, x, y);
			break;
		case 3:
			displayThree(win, x, y);
			break;
		case 4:
			displayFour(win, x, y);
			break;
		case 5:
			displayFive(win, x, y);
			break;
		case 6:
			displaySix(win, x, y);
			break;
		default:
			break;
	}
}

void DiceFrame(WINDOW *win, int x, int y) {
	// 横17マス
	// 縦8マス
	int width_dice = 15; // 0～16 = 17マス
	int height_dice = 6;

	// 最上部
	mvwaddch(win, y, x, ACS_ULCORNER);
	for (int i = 0; i < width_dice; i++) {
		waddch(win, ACS_HLINE);
	}
	waddch(win, ACS_URCORNER);
	mvwvline(win, y + 1, x, ACS_VLINE, height_dice);
	mvwvline(win, y + 1, x + width_dice + 1, ACS_VLINE, height_dice);

	// 最下部
	mvwaddch(win, y + height_dice + 1, x, ACS_LLCORNER);
	for (int i = 0; i < width_dice; i++) {
		waddch(win, ACS_HLINE);
	}
	waddch(win, ACS_LRCORNER);
	wrefresh(win);
}

void displayOne(WINDOW *win, int x, int y) {
	// 出目の場所
	exclusiveOne(win, x, y);
}

void displayTwo(WINDOW *win, int x, int y) {
	// 出目の場所
	moduleOne(win, x, y);
	moduleNine(win, x, y);
}

void displayThree(WINDOW *win, int x, int y) {
	// 出目の場所
	moduleOne(win, x, y);
	moduleFive(win, x, y);
	moduleNine(win, x, y);
}

void displayFour(WINDOW *win, int x, int y) {
	// 出目の場所
	moduleOne(win, x, y);
	moduleThree(win, x, y);
	moduleSeven(win, x, y);
	moduleNine(win, x, y);
}

void displayFive(WINDOW *win, int x, int y) {
	// 出目の場所
	moduleOne(win, x, y);
	moduleThree(win, x, y);
	moduleFive(win, x, y);
	moduleSeven(win, x, y);
	moduleNine(win, x, y);
}

void displaySix(WINDOW *win, int x, int y) {
	// 出目の場所
	moduleOne(win, x, y);
	moduleThree(win, x, y);
	moduleFour(win, x, y);
	moduleSix(win, x, y);
	moduleSeven(win, x, y);
	moduleNine(win, x, y);
}

// |-------|
// | 1 2 3 |
// | 4 5 6 |
// | 7 8 9 |
// |-------|

void exclusiveOne(WINDOW *win, int x, int y) {
	int trout_x = 7, trout_y = 3;
	mvwaddch(win, y + trout_y, x + trout_x, ACS_ULCORNER | COLOR_PAIR(1));
	waddch(win, ACS_HLINE | COLOR_PAIR(1));
	waddch(win, ACS_URCORNER | COLOR_PAIR(1));
	mvwaddch(win, y + trout_y + 1, x + trout_x, ACS_LLCORNER | COLOR_PAIR(1));
	waddch(win, ACS_HLINE | COLOR_PAIR(1));
	waddch(win, ACS_LRCORNER | COLOR_PAIR(1));
	wrefresh(win);
}

void moduleOne(WINDOW *win, int x, int y) {
	int trout_x = 2, trout_y = 1;
	mvwaddch(win, y + trout_y, x + trout_x, ACS_ULCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_URCORNER);
	mvwaddch(win, y + trout_y + 1, x + trout_x, ACS_LLCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_LRCORNER);
	wrefresh(win);
}

void moduleTwo(WINDOW *win, int x, int y) {
	int trout_x = 7, trout_y = 1;
	mvwaddch(win, y + trout_y, x + trout_x, ACS_ULCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_URCORNER);
	mvwaddch(win, y + trout_y + 1, x + trout_x, ACS_LLCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_LRCORNER);
	wrefresh(win);
}

void moduleThree(WINDOW *win, int x, int y) {
	int trout_x = 12, trout_y = 1;
	mvwaddch(win, y + trout_y, x + trout_x, ACS_ULCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_URCORNER);
	mvwaddch(win, y + trout_y + 1, x + trout_x, ACS_LLCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_LRCORNER);
	wrefresh(win);
}

void moduleFour(WINDOW *win, int x, int y) {
	int trout_x = 2, trout_y = 3;
	mvwaddch(win, y + trout_y, x + trout_x, ACS_ULCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_URCORNER);
	mvwaddch(win, y + trout_y + 1, x + trout_x, ACS_LLCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_LRCORNER);
	wrefresh(win);
}

void moduleFive(WINDOW *win, int x, int y) {
	int trout_x = 7, trout_y = 3;
	mvwaddch(win, y + trout_y, x + trout_x, ACS_ULCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_URCORNER);
	mvwaddch(win, y + trout_y + 1, x + trout_x, ACS_LLCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_LRCORNER);
	wrefresh(win);
}

void moduleSix(WINDOW *win, int x, int y) {
	int trout_x = 12, trout_y = 3;
	mvwaddch(win, y + trout_y, x + trout_x, ACS_ULCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_URCORNER);
	mvwaddch(win, y + trout_y + 1, x + trout_x, ACS_LLCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_LRCORNER);
	wrefresh(win);
}

void moduleSeven(WINDOW *win, int x, int y) {
	int trout_x = 2, trout_y = 5;
	mvwaddch(win, y + trout_y, x + trout_x, ACS_ULCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_URCORNER);
	mvwaddch(win, y + trout_y + 1, x + trout_x, ACS_LLCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_LRCORNER);
	wrefresh(win);
}

void moduleEight(WINDOW *win, int x, int y) {
	int trout_x = 7, trout_y = 5;
	mvwaddch(win, y + trout_y, x + trout_x, ACS_ULCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_URCORNER);
	mvwaddch(win, y + trout_y + 1, x + trout_x, ACS_LLCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_LRCORNER);
	wrefresh(win);
}

void moduleNine(WINDOW *win, int x, int y) {
	int trout_x = 12, trout_y = 5;
	mvwaddch(win, y + trout_y, x + trout_x, ACS_ULCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_URCORNER);
	mvwaddch(win, y + trout_y + 1, x + trout_x, ACS_LLCORNER);
	waddch(win, ACS_HLINE);
	waddch(win, ACS_LRCORNER);
	wrefresh(win);
}

void eraseDice(WINDOW *win, int x, int y) {
	// 横幅17マス
	// 縦幅8マス
	int width_dice = 17;
	int height_dice = 8;
	for (int i = 0; i < height_dice; i++) {
		mvwhline(win, y + i, x, ' ', width_dice);
	}
	wrefresh(win);
}
