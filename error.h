#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <ncurses.h>

#include "window_struct.h"

// コマンドライン引数エラー
void argumentsError(char *argv[]);

// 画面サイズエラー
void sizeError(GameWin *wins);

// スコアファイル参照エラー
void scoreFileError(WINDOW *win);

void notFoundError(WINDOW *win, const char *name);

void operationFileError(WINDOW *win);

#endif