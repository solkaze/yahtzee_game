#include <ncurses.h>
#include <stdbool.h>



static bool trans_keep_score = FALSE;
static bool trans_dice_score = FALSE;

void setTransKeepScore(bool b) {
    trans_keep_score = b;
}

bool getTransKeepScore(void) {
    return trans_keep_score;
}

void setTransDiceScore(bool b) {
    trans_dice_score = b;
}

bool getTransDiceScore(void) {
    return trans_dice_score;
}