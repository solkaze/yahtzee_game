#include <ncurses.h>

void getMenuPlace(WINDOW *win, int *y, int placeX[5]) {
	int menuInterval = 20;
	int menuLength = 16;
	int screen_x, screen_y;
	getmaxyx(win, screen_y, screen_x);

	*y = screen_y / 2 + 15;
	placeX[0] = (screen_x - (menuInterval*4 + menuLength)) / 2;
	placeX[1] = placeX[0] + menuInterval;
	placeX[2] = placeX[1] + menuInterval;
	placeX[3] = placeX[2] + menuInterval;
	placeX[4] = placeX[3] + menuInterval;
}

void getScorePlaceX(int x, int placeX[2]) {
	int player_first_place = x + 27;
	int player_second_place = player_first_place + 15;

	placeX[0] = player_first_place;
	placeX[1] = player_second_place;
}

void getScorePlaceY(int y, int placeY[12]) {
	int delay = 2;
	// 表の頂点のy座標
	placeY[0] = y + 4;
	placeY[1] = placeY[0] + delay;
	placeY[2] = placeY[1] + delay;
	placeY[3] = placeY[2] + delay;
	placeY[4] = placeY[3] + delay;
	placeY[5] = placeY[4] + delay;

	placeY[6] = placeY[5] + delay + 5;

	placeY[7] = placeY[6] + delay + 1;
	placeY[8] = placeY[7] + delay;
	placeY[9] = placeY[8] + delay;
	placeY[10] = placeY[9] + delay;
	placeY[11] = placeY[10] + delay;
}

void getTotalScorePlaceY(int y, int placeY[3]) {
	int delay = 16;
	int shift_y = 2;
	placeY[0] = y + delay;
	placeY[1] = placeY[0] + shift_y;
	placeY[2] = placeY[1] + delay + shift_y;
}

void getCursorPlaceX(int x, int placeX[2]) {
			// 表の頂点のx座標
	int player_first_place = x + 22;
	int player_second_place = player_first_place + 15;

	placeX[0] = player_first_place;
	placeX[1] = player_second_place;
}

void getCursorPlaceY(int y, int placeY[12]) {
	int delay = 2;
	// 表の頂点のy座標
	placeY[0] = y + 4;
	placeY[1] = placeY[0] + delay;
	placeY[2] = placeY[1] + delay;
	placeY[3] = placeY[2] + delay;
	placeY[4] = placeY[3] + delay;
	placeY[5] = placeY[4] + delay;

	placeY[6] = placeY[5] + delay + 5;

	placeY[7] = placeY[6] + delay + 1;
	placeY[8] = placeY[7] + delay;
	placeY[9] = placeY[8] + delay;
	placeY[10] = placeY[9] + delay;
	placeY[11] = placeY[10] + delay;
}

// サイコロのx座標を取得する
// 画面のx座標、要素番目、全体のサイコロの数
int getDiceX(int size_x,int el, int num) {
	int max_dice_line = 100;
	int delay_x_dice = 24;	// サイコロの間隔
	int shift_x = 5;
	int adjust_dice = ( max_dice_line - ( num * delay_x_dice ) ) / 2 - delay_x_dice + shift_x;

	return size_x / 2 + delay_x_dice * el + adjust_dice;
}

// サイコロのy座標を取得する
int getDiceY(int size_y) {
	return size_y / 2 - 5;
}

int getKeepDiceX(int size_x, int el) {
	int max_dice_line = 100;
	int delay_x_dice = 24;	// サイコロの間隔
	int num = 5;
	int shift_x = 5;
	int adjust_dice = ( max_dice_line - ( num * delay_x_dice ) ) / 2 - delay_x_dice + shift_x;

	return size_x / 2 + delay_x_dice * el + adjust_dice;
}

int getKeepDiceY(int size_y) {
	return size_y / 2 - 20;
}

int getNamePlaceX(int x, int turn) {
		// 表の頂点のx座標
	int player_first_place = x + 22;
	int player_second_place = player_first_place + 15;

		// Playerによって変える
	int placeX;

	if(turn == 0) {
		placeX = player_first_place;
	} else {
		placeX = player_second_place;
	}

	return placeX;
}

int getNamePlaceY(int y) {
	return y + 1;
}

void setInitNamePlace(WINDOW *win, int place[2]) {
	int window_x, window_y;
	getmaxyx(win, window_y, window_x);
	int center_x = window_x / 2;
	int center_y = window_y / 2;
	place[0] = center_y - 4;
	place[1] = center_x - 7;
}

void getScoreItemCursorPlace(WINDOW *win, int placeY[2], int *placeX) {
	int screen_x;
	int screen_y;

	getmaxyx(win, screen_y, screen_x);
	int x = screen_x/2;
	int y = screen_y/2;
	int adjust_item_x = (-70);
	int item_delay_y = 6;
	*placeX = x + adjust_item_x;

	placeY[0] = y - item_delay_y;
	placeY[1] = placeY[0] + item_delay_y;
}

void getHelpItemCursorPlace(WINDOW *win, int placeY[4], int *placeX) {
	int screen_x;
	int screen_y;

	getmaxyx(win, screen_y, screen_x);
	int x = screen_x/2;
	int y = screen_y/2;
	int adjust_item_x = (-80);
	int item_delay_y = 6;
	*placeX = x + adjust_item_x;

	placeY[0] = y - item_delay_y*2;
	placeY[1] = placeY[0] + item_delay_y;
	placeY[2] = placeY[1] + item_delay_y;
	placeY[3] = placeY[2] + item_delay_y;
}

void getRerollMessage(WINDOW *win, int *placeY, int *placeX) {
	int screen_x, screen_y;

	getmaxyx(win, screen_y, screen_x);
	int center_y = screen_y / 2;
	int delay_x = -28;
	int delay_y = 16;

	*placeX = screen_x + delay_x;
	*placeY = center_y + delay_y;

}

void getMessagePlace(int *placeY, int *placeX) {

	*placeX = 84;
	*placeY = 17;

}

void rerollButtonPlace(WINDOW *win, int *placeY, int *placeX) {
	int screen_y, screen_x;
	getmaxyx(win, screen_y, screen_x);
	int center_y = screen_y / 2;
	int delay_x = -28;
	int delay_y = 10;

	*placeX = screen_x + delay_x;
	*placeY = center_y + delay_y;
}