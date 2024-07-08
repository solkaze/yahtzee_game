#include "dice_list.h"

#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>

static bool update_dice_flag = FALSE;

void setUpdateDice(bool flag) {
	update_dice_flag = flag;
}
bool getUpdateDice() {
	return update_dice_flag;
}

void debugDisplayDiceList(WINDOW *win, DiceList *head, int mode);

void debugList(WINDOW *win, DiceList *list1, DiceList *list2, DiceList *list3) {
	// 振り直すモード
	int reroll_mode = 2;
	int dice_mode = 4;
	int keep_mode = 6;
	mvwprintw(win, 1, 1, "< LISTS >");
	mvwprintw(win, reroll_mode, 1, "temp_list:");
	debugDisplayDiceList(win, list1, reroll_mode + 1);
	mvwprintw(win, dice_mode, 1, "dice_list:");
	debugDisplayDiceList(win, list2, dice_mode + 1);
	mvwprintw(win, keep_mode, 1, "keep_list:");
	debugDisplayDiceList(win, list3, keep_mode + 1);
	int max_line = 30;
	if(update_dice_flag == TRUE) {
		mvwhline(win, reroll_mode + 1, 1, ' ', max_line);
		mvwhline(win, dice_mode + 1, 1, ' ', max_line);
		mvwhline(win, keep_mode + 1, 1, ' ', max_line);
		wrefresh(win);
		update_dice_flag = FALSE;
	}
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

void debugVariable(WINDOW *win, int reroll, int keep, int p_turn, int turn) {
	mvwprintw(win, 9, 1, "< VARIABLES >");
	mvwprintw(win, 10, 1, "turn: %d", turn);
	mvwprintw(win, 11, 1, "player_turn: %d", p_turn);
	mvwprintw(win, 12, 1, "reroll: %d, keep: %d", reroll, keep);
	wrefresh(win);
}
