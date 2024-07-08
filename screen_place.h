#ifndef SCREEN_PLACE_H
#define SCREEN_PLACE_H

#include <ncurses.h>

void getMenuPlace(WINDOW *win, int *y, int placeX[5]);

void getScorePlaceX(int x, int placeX[2]);

void getCursorPlaceX(int x, int placeX[2]);

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

void getScoreItemCursorPlace(WINDOW *win, int placeY[2],int *placeX);

void getHelpItemCursorPlace(WINDOW *win, int placeY[4], int *placeX);

void getRerollMessage(WINDOW *win, int *placeY, int *placeX);

void getMessagePlace(int *placeY, int *placeX);

void rerollButtonPlace(WINDOW *win, int *placeY, int *placeX);

#endif // SCREEN_PLACE_H