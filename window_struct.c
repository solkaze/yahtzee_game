#include <ncurses.h>
#include <unistd.h>

#include "window_struct.h"
#include "debug_mode.h"

// createWindow 関数の実装
void createWindow(GameWin **win) {
    // ウィンドウの作成処理
    int win_height = 50;
    int win_width = 186;
    int sub_win_width = 40;
    int start_y = (LINES - win_height) / 2; // 中央に配置
    int start_x;

    if(getDebugMode()) {
        start_x = (COLS - (win_width + sub_win_width)) / 2 + sub_win_width;
    }
    else {
        start_x = (COLS - win_width) / 2; // 中央に配置
    }

    // GameWin 構造体を動的に確保
    *win = (GameWin *)malloc(sizeof(GameWin));
    if (*win == NULL) {
        // エラー処理
        perror("Memory allocation failed");
        return;
    }

    // ウィンドウを作成
    (*win)->main_win = newwin(win_height, win_width, start_y, start_x);
    box((*win)->main_win, 0, 0);

    if(getDebugMode()) {
        int sub_start_x = (COLS - (win_width + sub_win_width)) / 2;
        (*win)->second_win = newwin(win_height, sub_win_width, start_y, sub_start_x);
        box((*win)->second_win, 0, 0);
    }
    else {
        (*win)->second_win = NULL;
    }

    // ウィンドウを画面に表示
    wrefresh((*win)->main_win);
    if ((*win)->second_win != NULL) {
        wrefresh((*win)->second_win);
    }
}

//ウィンドウのfree
void freeWindow(GameWin *win) {

    delwin(win->main_win);
    if (win->second_win != NULL) {
        delwin(win->second_win);
    }

    free(win);
}