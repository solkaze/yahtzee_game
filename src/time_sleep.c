#include <time.h>

#include "time_sleep.h"

void sleep_microseconds(long microseconds) {
    struct timespec req, rem;

    // 秒部分とナノ秒部分を分けて設定
    req.tv_sec = microseconds / 1000000;  // 秒部分
    req.tv_nsec = (microseconds % 1000000) * 1000;  // ナノ秒部分

    // nanosleepの呼び出し
    nanosleep(&req, &rem);
}