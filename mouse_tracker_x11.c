#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>

int main() {
    Display *display;
    Window root, child;
    int x, y;
    int root_x, root_y;
    unsigned int mask;

    // Xサーバへの接続
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Unable to open X display\n");
        return 1;
    }

    // ルートウィンドウの取得
    root = DefaultRootWindow(display);

    // メインループ
    while (1) {
        // マウスの位置を取得
        if (XQueryPointer(display, root, &root, &child, &root_x, &root_y, &x, &y, &mask)) {
            // 位置を表示
            printf("Mouse at: %d, %d\n", x, y);
        } else {
            fprintf(stderr, "Failed to query pointer position.\n");
        }

        // 100ms待つ
        usleep(100000);
    }

    // Xサーバの接続を閉じる
    XCloseDisplay(display);

    return 0;
}
