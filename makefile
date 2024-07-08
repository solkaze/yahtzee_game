#「ヨット」用makefile
CC = gcc
CFLAGS = -g -Wall -Wextra
LDLIBS := -lncursesw



yahtzee: calc_expected.o calc_score.o cpu_op_data.o cpu_op_dice.o cpu_queue.o cpu.o \
	create.o debag_mode.o dice_list.o dice.o error.o game_cursor.o game_score.o game_screen.o \
	help.o message.o name.o operation_bit.o operation_dice.o operation_help.o operation_score.o \
	player.o score.o screen_place.o title.o yahtzee_game.o yahtzee.o

calc_expected.o:

calc_score.o:

cpu_op_data.o:

cpu_op_dice.o:

cpu_queue.o:

cpu.o:

create.o:

debag_mode.o:

dice_list.o:

dice.o:

error.o:

game_cursor.o:

game_score.o:

game_screen.o:

help.o:

message.o:

name.o:

operation_bit.o:

operation_dice.o:

operation_help.o:

operation_score.o:

player.o:

score.o:

screen_place.o:

title.o:

yahtzee_game.o:

yahtzee.o:

clean:
	$(RM) *.o
	$(RM) yahtzee