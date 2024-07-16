#include <ncurses.h>
#include <stdbool.h>

#include "mode_roll_dice.h"
#include "dice_list.h"
#include "cpu_queue.h"
#include "debug_mode.h"
#include "game_cursor.h"
#include "cpu.h"
#include "error.h"
#include "dice_cursor_flag.h"
#include "dice_struct.h"
#include "window_struct.h"

void rollDiceSelection(GameWin *wins, DiceStruct *dice, Queue *q, GValue *gv) {
	while(gv->input_key != '\n' && gv->mode_select == 1 && gv->input_key != 'q') {
		if(gv->input_key != ERR) {
			printDiceCursor(wins->main_win, gv->dice_cursor, countNodes(dice->roll));
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

		// 入力キーによって操作を変える
		switch(gv->input_key) {
			case KEY_LEFT:
				if(gv->dice_cursor != 0) {
					eraseDiceCursor(wins->main_win, gv->dice_cursor, gv->reroll_dice);
					(gv->dice_cursor)--;
				} else {
					eraseDiceCursor(wins->main_win, gv->dice_cursor, gv->reroll_dice);
					gv->mode_select = 3;
					//カーソル位置の初期化
					setTransDiceScore(TRUE);
				}
				break;

			case KEY_RIGHT:
				if(gv->dice_cursor != gv->reroll_dice - 1) {
					eraseDiceCursor(wins->main_win, gv->dice_cursor, gv->reroll_dice);
					(gv->dice_cursor)++;
				}
				break;
			case KEY_UP:
				if(gv->keep_dice != 0) {
					eraseDiceCursor(wins->main_win, gv->dice_cursor, gv->reroll_dice);
					gv->mode_select = 2;
					//カーソル位置の初期化
				}
				break;
			case KEY_DOWN:
				eraseDiceCursor(wins->main_win, gv->dice_cursor, gv->reroll_dice);
				gv->mode_select = 4;
				//カーソル位置の初期化
				break;
			case '\n':
				eraseDiceCursor(wins->main_win, gv->dice_cursor, gv->reroll_dice);
				break;
			default:
				break;
		}
	}
}
