#include "player.h"
#include "calc_score.h"
#include "dice_list.h"
#include "game_screen.h"
#include "game_score.h"
#include "screen_place.h"

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

void displayPredictionScore(WINDOW *win, int x, int y, DiceList *dice, Player *pl, int turn);

// 桁数を数える
int digit_count(int num) {
	int count = 0;

	if(num == 0) {
		return 1;
	}

	if(num < 0) {
		num = -num;
	}

	while(num != 0) {
		num /= 10;

		count++;
	}

	return count;
}

void displayPredictionScore(WINDOW *win, int x, int y, DiceList *dice, Player *pl, int turn) {
	int placeX[2];
	int placeY[12];
	getScorePlaceX(x, placeX);
	getScorePlaceY(y, placeY);



	//青色を設定
	wattrset(win, COLOR_PAIR(4)); // 青色を設定

	if(pl->ace == EMPTY) {
		mvwprintw(win, placeY[0], placeX[turn], "%2d", calcAce(dice));
	}
	if(pl->deuce == EMPTY) {
		mvwprintw(win, placeY[1], placeX[turn], "%2d", calcDeuce(dice));
	}
	if(pl->trey == EMPTY) {
		mvwprintw(win, placeY[2], placeX[turn], "%2d", calcTrey(dice));
	}
	if(pl->four == EMPTY) {
		mvwprintw(win, placeY[3], placeX[turn], "%2d", calcFour(dice));
	}
	if(pl->five == EMPTY) {
		mvwprintw(win, placeY[4], placeX[turn], "%2d", calcFive(dice));
	}
	if(pl->six == EMPTY) {
		mvwprintw(win, placeY[5], placeX[turn], "%2d", calcSix(dice));
	}
	if(pl->choice == EMPTY) {
		mvwprintw(win, placeY[6], placeX[turn], "%2d", calcChoice(dice));
	}
	if(pl->four_dice == EMPTY) {
		mvwprintw(win, placeY[7], placeX[turn], "%2d", calcFourDice(dice));
	}
	if(pl->full_house == EMPTY) {
		mvwprintw(win, placeY[8], placeX[turn], "%2d", calcFullHouse(dice));
	}
	if(pl->small_straight == EMPTY) {
		mvwprintw(win, placeY[9], placeX[turn], "%2d", calcSmallStraight(dice));
	}
	if(pl->big_straight == EMPTY) {
		mvwprintw(win, placeY[10], placeX[turn], "%2d", calcBigStraight(dice));
	}
	if(pl->yahtzee == EMPTY) {
		mvwprintw(win, placeY[11], placeX[turn], "%2d", calcYahtzee(dice));
	}

	wattrset(win, 0); // 初期色に戻す
	wrefresh(win);
}

void erasePredictionScore(WINDOW *win, int x, int y, Player *pl, int turn) {
	int placeX[2];
	int placeY[12];
	
	getScorePlaceX(x, placeX);
	getScorePlaceY(y, placeY);

	int scores[] = {pl->ace, pl->deuce, pl->trey, pl->four, pl->five, pl->six, 
				pl->choice, pl->four_dice, pl->full_house, pl->small_straight, 
				pl->big_straight, pl->yahtzee};

	for (int i = 0; i < 12; i++) {
		if (scores[i] == EMPTY) {
			mvwprintw(win, placeY[i], placeX[turn], "   ");
		}
	}
	wrefresh(win);
}


// 得点を表示する
void displayScore(WINDOW *win, int x, int y, Player *pl, int turn) {
	int placeX[2];
	int placeY[12];
	getScorePlaceX(x, placeX);
	getScorePlaceY(y, placeY);

	int scores[] = {pl->ace, pl->deuce, pl->trey, pl->four, pl->five, pl->six, 
				pl->choice, pl->four_dice, pl->full_house, pl->small_straight, 
				pl->big_straight, pl->yahtzee};
				
	for (int i = 0; i < 12; i++) {
		if (scores[i] != EMPTY) {
			mvwprintw(win, placeY[i], placeX[turn], "%2d", scores[i]);
		}
	}

}

// 総合得点を表示する
int displayTotalScoreAnimate(WINDOW *win, int x, int y, int total, Player *pl, int turn) {
	int placeX[2];
	int placeY[3];
	int total_score = calcTotalScore(pl);
	getScorePlaceX(x, placeX);
	getTotalScorePlaceY(y, placeY);
	while(total < total_score) {
		total++;
		mvwprintw(win, placeY[2], placeX[turn] - 1, "%3d", total);
		wrefresh(win);
		usleep(34000);
	}

	return total;
}

// 小計を計算し表示する
int displaySubTotalScoreAnimate(WINDOW *win, int x, int y, int total, Player *pl, int turn) {
	int placeX[2];
	int placeY[3];
	int delay = (-2);
	getScorePlaceX(x, placeX);

	int sub_total = calcSubTotalScore(pl);
	getTotalScorePlaceY(y, placeY);
	while(total < sub_total) {
		total++;
		mvwprintw(win, placeY[0], placeX[turn] + delay, "%2d", total);
		wrefresh(win);
		usleep(34000);
	}

	return total;
}

void initDisplayTotalScore(WINDOW *win, int x, int y, int point) {
	int delay_x = (-2);
	int placeX[2];

	int placeY[3];
	getScorePlaceX(x, placeX);
	getTotalScorePlaceY(y, placeY);
	mvwprintw(win, placeY[0], placeX[0] + delay_x, "%2d / %2d", 0, point);
	mvwprintw(win, placeY[0], placeX[1] + delay_x, "%2d / %2d", 0, point);
	mvwprintw(win, placeY[2], placeX[0], "%2d", 0);
	mvwprintw(win, placeY[2], placeX[1], "%2d", 0);
}

void displayBonusScore(WINDOW *win, int x, int y, int point, int turn) {
	int placeX[2];
	int placeY[3];
	getScorePlaceX(x, placeX);
	getTotalScorePlaceY(y, placeY);
	int loop = 3;
	for(int i = 0; i < loop; i++) {
		wattrset(win, COLOR_PAIR(3)); // 黄色を設定
		mvwprintw(win, placeY[1], placeX[turn], "+%2d", point);
		wrefresh(win);
		usleep(500000);

		wattrset(win, 0); // 初期色に戻す
		mvwprintw(win, placeY[1], placeX[turn], "+%2d", point);
		wrefresh(win);
		usleep(500000);
	}

}
