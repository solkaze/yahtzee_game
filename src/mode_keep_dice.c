#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#include "mode_keep_dice.h"
#include "dice_list.h"
#include "cpu_queue.h"
#include "debug_mode.h"
#include "game_cursor.h"
#include "cpu.h"
#include "error.h"
#include "dice_cursor_flag.h"
#include "dice_struct.h"
#include "window_struct.h"

void keepDiceSelection(GameWin *wins, DiceStruct *dice, Queue *q, GValue *gv) {
	while(gv->input_key != '\n' && gv->mode_select == 2 && gv->input_key != 'q') {
		if(gv->input_key != ERR) {
			printKeepDiceCursor(wins->main_win, gv->keep_cursor);
			if(getDebugMode()) {
				debugList(wins->second_win, dice);
				debugVariable(wins->second_win, gv);
			}
		}

		if(getComputer() && gv->p_turn == 1) {
			gv->input_key = CPUAction(q);
		} else {
			gv->input_key = wgetch(wins->main_win);
		}

		sizeError(wins);

		// 入力によって操作を変える
		switch(gv->input_key) {
			case KEY_LEFT:
				if( gv->keep_cursor != 0) {
					eraseKeepDiceCursor(wins->main_win,  gv->keep_cursor);
						(gv->keep_cursor)--;
				} else {
					// 左端の場合は得点表に移動する
					gv->mode_select = 3;

					eraseKeepDiceCursor(wins->main_win,  gv->keep_cursor);
					setTransKeepScore(TRUE);
				}
				break;
			case KEY_RIGHT:
				if( gv->keep_cursor != gv->keep_dice - 1) {
					eraseKeepDiceCursor(wins->main_win,  gv->keep_cursor);
						(gv->keep_cursor)++;
				}
				break;
			case KEY_DOWN:
				if(gv->reroll_dice != 0) {
					eraseKeepDiceCursor(wins->main_win, gv->keep_cursor);
					// サイコロ選択へ移動
					gv->mode_select = 1;
				}
				break;
			case '\n':
				eraseKeepDiceCursor(wins->main_win, gv->keep_cursor);
				break;
			default:
				break;
		}
	}
}
