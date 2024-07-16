#include <ncurses.h>

#include "dice_list.h"
#include "player.h"
#include "cpu_queue.h"
#include "debug_mode.h"
#include "game_cursor.h"
#include "error.h"
#include "cpu.h"
#include "dice_cursor_flag.h"
#include"dice_struct.h"
#include "game_value.h"
#include "window_struct.h"

void scoreBoardSelection(GameWin *wins, DiceStruct *dice, Queue *q, Player *pl[], GValue *gv, SBPlace bp) {
    while (gv->input_key != '\n' && gv->mode_select == 3 && gv->input_key != 'q') {
        int temp_cursor = gv->score_cursor;

        if (getDebugMode()) {
            debugList(wins->second_win, dice);
			debugVariable(wins->second_win, gv);
        }

        if (gv->input_key != ERR) {
            printScoreCursor(wins->main_win, bp.x, bp.y, gv->score_cursor, gv->p_turn);
        }

        if (getComputer() && gv->p_turn == 1) {
            gv->input_key = CPUAction(q);
        } else {
            gv->input_key = wgetch(wins->main_win);
        }

        sizeError(wins);

        switch (gv->input_key) {
            case KEY_UP:
                gv->score_cursor = skipScoreCursor(pl[gv->p_turn], gv->score_cursor, gv->score_cursor, gv->input_key);
                if (temp_cursor != gv->score_cursor) {
                    eraseScoreCursor(wins->main_win, bp.x, bp.y, temp_cursor, gv->p_turn);
                }
                break;

            case KEY_DOWN:
                gv->score_cursor = skipScoreCursor(pl[gv->p_turn], gv->score_cursor, gv->score_cursor, gv->input_key);
                if (temp_cursor != gv->score_cursor) {
                    eraseScoreCursor(wins->main_win, bp.x, bp.y, temp_cursor, gv->p_turn);
                }
                break;

            case KEY_RIGHT:
                if (gv->reroll_count != 0) {
                    if (getTransDiceScore()) {
                        eraseScoreCursor(wins->main_win, bp.x, bp.y, gv->score_cursor, gv->p_turn);
                        gv->mode_select = 1;
                        setTransDiceScore(FALSE);
                    } else if (getTransKeepScore()) {
                        eraseScoreCursor(wins->main_win, bp.x, bp.y, gv->score_cursor, gv->p_turn);
                        gv->mode_select = 2;
                        setTransKeepScore(FALSE);
                    } else {
                        gv->mode_select = 4;
                    }
                }
                break;
            case '\n':
                eraseScoreCursor(wins->main_win, bp.x, bp.y, gv->score_cursor, gv->p_turn);
                break;
            default:
                break;
        }
    }
}
