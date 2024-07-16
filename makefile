#「ヨット」用makefile
CC = gcc
CFLAGS = -g -Wall -Wextra
LDLIBS := -lncursesw



yahtzee: calc_expected.o calc_score.o cpu_op_data.o cpu_op_dice.o cpu_queue.o cpu.o create.o \
	debug_mode.o dice_cursor_flag.o dice_list.o dice_struct.o dice.o error.o \
	game_cursor.o game_score.o game_screen.o game_value.o\
	help.o message.o mode_roll_dice.o mode_reroll_select.o mode_keep_dice.o mode_score_select.o name.o \
	operation_bit.o operation_dice.o operation_help.o operation_mode.o operation_score.o op_score_list.o \
	player.o score.o screen_place.o title.o window_struct.o yahtzee_game.o yahtzee.o

calc_expected.o:

calc_score.o:

cpu_op_data.o:

cpu_op_dice.o:

cpu_queue.o:

cpu.o:

create.o:

debug_mode.o:

dice_cursor_flag.o:

dice_list.o:

dice_struct.o:

dice.o:

error.o:

game_cursor.o:

game_score.o:

game_screen.o:

game_value.o:

help.o:

message.o:

mode_keep_dice.o:

mode_reroll_select.o:

mode_roll_dice.o:

mode_score_select.o:

name.o:

op_score_list.o:

operation_bit.o:

operation_dice.o:

operation_help.o:

operation_mode.o:

operation_score.o:

player.o:

score.o:

screen_place.o:

title.o:

window_struct.o:

yahtzee_game.o:

yahtzee.o:

clean:
	$(RM) *.o
	$(RM) yahtzee