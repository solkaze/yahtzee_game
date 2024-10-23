#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "message.h"
#include "dice_list.h"
#include "calc_score.h"
#include "screen_place.h"
#include "calc_score.h"

void displayMessageFourDice(WINDOW *win) {
	int start_x, start_y;
	getMessagePlace(&start_x, &start_y);
	int width = 73;
	int height = 14;
	WINDOW *sub_win = derwin(win, height, width, start_y, start_x);
	werase(sub_win);
	box(sub_win, 0, 0);
	wrefresh(sub_win);
	char *message[12] = {
		"                                         #                          ",
		"                                     #   # #        #               ",
		" ########                            #####         #     ######     ",
		"        ##       #                  #    #       ##           #     ",
		"        #    #######               #     #      ##            #     ",
		"        #       ##     #########  #  #  #     ## #           #      ",
		"        #      # #                    ###        #          ##      ",
		"       #      #  #                     #         #         #  #     ",
		"     ##      #   #                    ##         #       ##    #    ",
		"   ##           ##                  ##           #      ##      #   ",
		"                                   ##                               ",
		"                                                                    "
	};
	int max_x = getmaxx(sub_win);

	for(int i = 0; i < 11; i++) {
		mvwprintw(sub_win, i + 1, (max_x - strlen(message[i])) / 2, "%s", message[i]);
	}
	wrefresh(sub_win);
	// 2秒待ったらウィンドウを閉じる
	sleep(2);
	werase(sub_win);
	delwin(sub_win);
	wrefresh(win);
}

void displayMessageFullHouse(WINDOW *win) {
	int start_x, start_y;
	getMessagePlace(&start_x, &start_y);
	int width = 73;
	int height = 14;

	WINDOW *sub_win = derwin(win, height, width, start_y, start_x);
	werase(sub_win);
	box(sub_win, 0, 0);
	wrefresh(sub_win);
	char *message[12] = {
		"                                                         ",
		"              # #                     #                  ",
		" ########     # #        #        #########   ######     ",
		"        ##    # #        #   #    #       #        #     ",
		"        #     # #        #   #    #      #         #     ",
		"        #     # #   #   ##   #           #        #      ",
		"        #    ## #   #   #     #          #       ##      ",
		"       #     #  #  #    #     #         #       #  #     ",
		"     ##     ##  ####   #      ##       #      ##    #    ",
		"   ##       #   ##     #       #     ##      ##      #   ",
		"                                                         ",
		"                                                         "
	};
	int max_x = getmaxx(sub_win);

	for(int i = 0; i < 11; i++) {
		mvwprintw(sub_win, i + 1, (max_x - strlen(message[i])) / 2, "%s", message[i]);
	}
	wrefresh(sub_win);
	// 2秒待ったらウィンドウを閉じる
	sleep(2);
	werase(sub_win);
	delwin(sub_win);
	wrefresh(win);
}

void displayMessageSmallStraight(WINDOW *win) {
	int start_x, start_y;
	getMessagePlace(&start_x, &start_y);
	int width = 73;
	int height = 14;
	WINDOW *sub_win = derwin(win, height, width, start_y, start_x);
	werase(sub_win);
	box(sub_win, 0, 0);
	wrefresh(sub_win);
	char *message[12] = {
		"                                                                      ",
		"   ###                        #         #                      #      ",
		"  #   #           ######      #         #                      #      ",
		"  #                    #      #         #                      #      ",
		"  ##                   #      ##        #      #               ##     ",
		"   ###                #       # ###     #     ##  #########    # ###  ",
		"      #              ##       #   ##    #    ##                #   ## ",
		"      ##            #  #      #         #   ##                 #      ",
		" ##   ##          ##    #     #         # ##                   #      ",
		"  #####    #     ##      #    #         ##                     #      ",
		"                              #                                #      ",
		"                                                                      "
	};
	int max_x = getmaxx(sub_win);

	for(int i = 0; i < 11; i++) {
		mvwprintw(sub_win, i + 1, (max_x - strlen(message[i])) / 2, "%s", message[i]);
	}
	wrefresh(sub_win);
	// 2秒待ったらウィンドウを閉じる
	sleep(2);
	werase(sub_win);
	delwin(sub_win);
	wrefresh(win);
}

void displayMessageBigStraight(WINDOW *win) {
	int start_x, start_y;
	getMessagePlace(&start_x, &start_y);
	int width = 73;
	int height = 14;
	WINDOW *sub_win = derwin(win, height, width, start_y, start_x);
	werase(sub_win);
	box(sub_win, 0, 0);
	wrefresh(sub_win);
	char *message[12] = {
		"                                                                      ",
		" #####                        #         #                      #      ",
		" #    #           ######      #         #                      #      ",
		" #    ##               #      #         #                      #      ",
		" #    #                #      ##        #      #               ##     ",
		" #####                #       # ###     #     ##  #########    # ###  ",
		" #    ##             ##       #   ##    #    ##                #   ## ",
		" #     #            #  #      #         #   ##                 #      ",
		" #    ##          ##    #     #         # ##                   #      ",
		" ######    #     ##      #    #         ##                     #      ",
		"                              #                                #      ",
		"                                                                      "
	};
	int max_x = getmaxx(sub_win);

	for(int i = 0; i < 12; i++) {
		mvwprintw(sub_win, i + 1, (max_x - strlen(message[i])) / 2, "%s", message[i]);
	}
	wrefresh(sub_win);
	// 2秒待ったらウィンドウを閉じる
	sleep(2);
	werase(sub_win);
	delwin(sub_win);
	wrefresh(win);
}

void displayMessageYahtzee(WINDOW *win) {
	int start_x, start_y;
	getMessagePlace(&start_x, &start_y);
	int width = 73;
	int height = 14;
	WINDOW *sub_win = derwin(win, height, width, start_y, start_x);
	werase(sub_win);
	box(sub_win, 0, 0);
	wrefresh(sub_win);
	char *message[12] = {
		"                                                    ",
		"                         #            #          #  ",
		"  #######                #            #          #  ",
		"        #      #   #     #            #          #  ",
		"        #    #  #  #     ##           #          #  ",
		"  #######    #  #  #     # ###        #          #  ",
		"        #         #      #   ##       #          #  ",
		"        #         #      #            #          #  ",
		"        #       ##       #            #          #  ",
		" ########      ##        #                          ",
		"                         #            #          #  ",
		"                                                    "
	};

	int max_x = getmaxx(sub_win);

	wattrset(sub_win, COLOR_PAIR(3));
	for(int i = 0; i < 12; i++) {
		mvwprintw(sub_win, i + 1, (max_x - strlen(message[i])) / 2, "%s", message[i]);
	}
	wattrset(sub_win, 0);
	wrefresh(sub_win);
	// 2秒待ったらウィンドウを閉じる
	sleep(2);
	werase(sub_win);
	delwin(sub_win);
	wrefresh(win);
}



// 配列内の関数の結果が一つでも0より上であればTRUEを返す関数
bool checkFunctions(DiceList *dice) {
	int (*calc_functions[])(DiceList *) = {calcYahtzee, calcBigStraight, calcSmallStraight, calcFullHouse, calcFourDice};
	int num_functions = sizeof(calc_functions) / sizeof(calc_functions[0]);
	for (int i = 0; i < num_functions; i++) {
		if (calc_functions[i](dice) > 0) {
			return TRUE;
		}
	}
	return FALSE;
}

void displayMessage(WINDOW *win, DiceList *dice, Player *pl) {
	int (*calc_functions[])(DiceList *) = {calcYahtzee, calcBigStraight, calcSmallStraight, calcFullHouse, calcFourDice};
		//個々から処理開始
	if(calc_functions[0](dice) > 0 && pl->yahtzee == EMPTY) {
		displayMessageYahtzee(win);
	}
	else if(calc_functions[1](dice) > 0 && pl->big_straight == EMPTY) {
		displayMessageBigStraight(win);
	}
	else if(calc_functions[2](dice) > 0 && pl->small_straight == EMPTY) {
		displayMessageSmallStraight(win);
	}
	else if(calc_functions[3](dice) > 0 && pl->full_house == EMPTY) {
		displayMessageFullHouse(win);
	}
	else if(calc_functions[4](dice) > 0 && pl->four_dice == EMPTY) {
		displayMessageFourDice(win);
	}
}

// 勝利メッセージ

void displayWinMessage(WINDOW *win, Player *pl) {
	int start_x, start_y;
	getMessagePlace(&start_x, &start_y);
	int width = 73;
	int height = 16;
	WINDOW *sub_win = derwin(win, height, width, start_y, start_x);
	werase(sub_win);
	box(sub_win, 0, 0);
	wrefresh(sub_win);
	char *message[12] = {
		"                                                                  ",
		" #         #    ###      ##    #    ##    #     #####     #####   ",
		" ##   #   ##     #       ##    #    ##    #     #         #    #  ",
		"  #  ###  #      #       # #   #    # #   #     #         #    ## ",
		"  #  # #  #      #       # ##  #    # ##  #     #         #    #  ",
		"  #  # #  #      #       #  #  #    #  #  #     #####     #####   ",
		"   ### ###       #       #   # #    #   # #     #         #   #   ",
		"   ##   ##       #       #   ###    #   ###     #         #    #  ",
		"   ##   ##       #       #    ##    #    ##     #         #    #  ",
		"   ##   ##      ###      #     #    #     #     ######    #     # ",
		"                                                                  ",
		"                                                                  "
	};
	int max_x = getmaxx(sub_win);

	wattrset(sub_win, COLOR_PAIR(3));
	for(int i = 0; i < 12; i++) {
		mvwprintw(sub_win, i + 1, (max_x - strlen(message[i])) / 2, "%s", message[i]);
	}
	wattrset(sub_win, 0);
	int msg_x_name = width / 2 - 25;
	int msg_x_score = width / 2 + 15;
	int msg_y = 13;
	// 勝利利メッセージを表示
	mvwprintw(sub_win, msg_y, msg_x_name, "[ %s ]", pl->name);
	mvwprintw(sub_win, msg_y, msg_x_score, "score : %d", calcTotalScore(pl));
	wrefresh(sub_win);
	// 2秒待ったらウィンドウを閉じる
	sleep(2);
	werase(sub_win);
	delwin(sub_win);
	wrefresh(win);
}

// 引き分けメッセージ
void displayDrawMessage(WINDOW *win) {
	int start_x, start_y;
	getMessagePlace(&start_x, &start_y);
	int width = 73;
	int height = 16;
	WINDOW *sub_win = derwin(win, height, width, start_y, start_x);
	werase(sub_win);
	box(sub_win, 0, 0);
	wrefresh(sub_win);
	char *message[12] = {
		"                                           ",
		" #####      #####         #     #         #",
		" #    ##    #    #       ###    ##   #   ##",
		" #     #    #    ##      # #     #  ###  # ",
		" #     ##   #    #       # #     #  # #  # ",
		" #     ##   #####       #   #    #  # #  # ",
		" #     ##   #   #       #####     ### ###  ",
		" #     #    #    #     #     #    ##   ##  ",
		" #     #    #    #     #     #    ##   ##  ",
		" #    ##    #    #     #     #    ##   ##  ",
		" #####      #     #    #     #    ##   ##  ",
		"                                           "
	};
	int max_x = getmaxx(sub_win);

	wattrset(sub_win, COLOR_PAIR(3));
	for(int i = 0; i < 12; i++) {
		mvwprintw(sub_win, i + 1, (max_x - strlen(message[i])) / 2, "%s", message[i]);
	}
	wrefresh(sub_win);
	// 2秒待ったらウィンドウを閉じる
	sleep(2);
	werase(sub_win);
	delwin(sub_win);
	wrefresh(win);
}

void displayWinner(WINDOW *win, Player *player[]) {
	if(calcTotalScore(player[0]) > calcTotalScore(player[1])) {
		displayWinMessage(win, player[0]);
	}
	else if(calcTotalScore(player[1]) > calcTotalScore(player[0])) {
		displayWinMessage(win, player[1]);
	}
	else {
		displayDrawMessage(win);
	}
}