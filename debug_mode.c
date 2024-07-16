#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>

#include "dice_list.h"
#include "debug_mode.h"
#include "dice_struct.h"

static bool debugMode = FALSE;

void setDebugMode(bool flag) {
	debugMode = flag;
}

bool getDebugMode() {
	return debugMode;
}

void debugDisplayDiceList(WINDOW *win, DiceList *head, int mode);

void debugList(WINDOW *win, DiceStruct *dice) {
	// 振り直すモード
	int reroll_mode = 2;
	int dice_mode = 4;
	int keep_mode = 6;
	mvwprintw(win, 1, 1, "< LISTS >");
	mvwprintw(win, reroll_mode, 1, "temp_list:");
	debugDisplayDiceList(win, dice->temp, reroll_mode + 1);
	mvwprintw(win, dice_mode, 1, "dice_list:");
	debugDisplayDiceList(win, dice->roll, dice_mode + 1);
	mvwprintw(win, keep_mode, 1, "keep_list:");
	debugDisplayDiceList(win, dice->keep, keep_mode + 1);
}

void debugListReset(WINDOW *win) {
	int reroll_mode = 2;
	int dice_mode = 4;
	int keep_mode = 6;
	int max_line = 30;
	mvwhline(win, reroll_mode + 1, 1, ' ', max_line);
	mvwhline(win, dice_mode + 1, 1, ' ', max_line);
	mvwhline(win, keep_mode + 1, 1, ' ', max_line);
	wrefresh(win);
}

void debugDisplayDiceList(WINDOW *win, DiceList *head, int mode) {
	DiceList* temp = head;
	wmove(win, mode, 1);
	if(temp != NULL) {
		wprintw(win, "-- ");
	}
	while (temp != NULL) {
		wprintw(win, "%d -- ", temp->data);
		temp = temp->next;
	}
	wrefresh(win);
}

void debugVariable(WINDOW *win, GValue *value) {
	mvwprintw(win, 9, 1, "< VARIABLES >");
	mvwprintw(win, 10, 1, "turn: %d", value->turn);
	mvwprintw(win, 11, 1, "player_turn: %d", value->p_turn);
	mvwprintw(win, 12, 1, "reroll: %d, keep: %d", value->reroll_dice, value->keep_dice);
	mvwprintw(win, 13, 1, "reroll_count: %d", value->reroll_count);
	mvwprintw(win, 14, 1, "dice_cursor: %d", value->dice_cursor);
	mvwprintw(win, 15, 1, "keep_cursor: %d", value->keep_cursor);
	mvwprintw(win, 16, 1, "score_cursor: %2d", value->score_cursor);
	wrefresh(win);
}
