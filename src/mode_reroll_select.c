#include <ncurses.h>
#include <unistd.h>

#include "mode_reroll_select.h"
#include "dice_list.h"
#include "create.h"
#include "player.h"
#include "cpu_queue.h"
#include "debug_mode.h"
#include "game_cursor.h"
#include "error.h"
#include "cpu.h"
#include "dice_cursor_flag.h"
#include "dice_struct.h"
#include "game_value.h"
#include "window_struct.h"
#include "time_sleep.h"

// 振り直しの処理
void rerollSelection(GameWin *wins, DiceStruct *dice, Queue *q, GValue *gv) {
	while(gv->input_key != '\n' && gv->mode_select == 4 && gv->input_key != 'q') {

		if(gv->input_key != ERR) {
			printRerollCursor(wins->main_win);
		}

		// サイコロを振る
		if(countNodes(dice->temp) == 0) {
			for(int i = 0; i < gv->reroll_dice; i++) {
				addNodeAtBeginning(&(dice->temp), rollDice());
			}
		}
		else {
			for(int i = 0; i < gv->reroll_dice; i++) {
				updateNodeAt(dice->temp, i, rollDice());
			}
		}
		sleep_microseconds(30000);
		if(getDebugMode()) {
			debugList(wins->second_win, dice);
			debugVariable(wins->second_win, gv);
		}

		if(getComputer() && gv->p_turn == 1) {
			gv->input_key = CPUAction(q);
		}
		else {
			gv->input_key = wgetch(wins->main_win);
		}

		// エンターキーが入力されたら値を保持して抜ける
		if(gv->input_key == '\n' || gv->input_key == 'q') {
			break;
		}
		if(gv->input_key == KEY_UP && countNodes(dice->roll) != 0) {
			freeList(&(dice->temp));
			eraseRerollCursor(wins->main_win);
			if(getDebugMode()) {
				debugListReset(wins->second_win);
			}
			gv->mode_select = 1;
		}

		sizeError(wins);
	}
}