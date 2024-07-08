#include <ncurses.h>

int main() {
    initscr();            // ncursesの初期化
    cbreak();             // 入力を即座に受け取る
    noecho();             // 入力文字を表示しない
    keypad(stdscr, TRUE); // 特殊キーを有効にする

    // 新しいウィンドウを作成
    WINDOW *win = newwin(10, 20, 5, 5); // 高さ10、幅20、座標(5, 5)に作成

    // ウィンドウの左上の座標を取得
    int startx, starty;
    getbegyx(win, starty, startx);

    // 座標を表示
    mvprintw(0, 0, "Window start position: (%d, %d)", starty, startx);
    refresh();
    
    // キー入力を待つ
    getch();

    // 終了処理
    delwin(win);          // ウィンドウを削除
    endwin();             // ncursesの終了

    return 0;
}
