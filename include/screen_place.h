#ifndef SCREEN_PLACE_H
#define SCREEN_PLACE_H

#include <ncurses.h>

void getScorePlaceX(int x, int placeX[2]);

void getScorePlaceY(int y, int placeY[12]);

void getTotalScorePlaceY(int y, int placeY[3]);

void getCursorPlaceX(int x, int placeX[2]);

void getCursorPlaceY(int y, int placeY[12]);

int getNamePlaceX(int x, int turn);

int getNamePlaceY(int y);

// 指定番目のサイコロのx座標を取得する関数
int getDiceX(int size_x, int el, int num);
// 指定番目のサイコロのy座標を取得する
int getDiceY(int size_y);

// キープ用のサイコロのx座標の取得
int getKeepDiceX(int size_x, int el);
// キープ用のサイコロのy座標を取得
int getKeepDiceY(int size_y);

void getMenuPlace(WINDOW *win, int placeX[5], int *y);

void getScoreItemCursorPlace(WINDOW *win,int *placeX, int placeY[2]);

void getHelpItemCursorPlace(WINDOW *win, int *placeX, int placeY[4]);

void getRerollMessage(WINDOW *win, int *placeX, int *placeY);

void getMessagePlace(int *placeX, int *placeY);

void rerollButtonPlace(WINDOW *win, int *placeX, int *placeY);

#endif // SCREEN_PLACE_H