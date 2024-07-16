#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "calc_score.h"

// 小計を計算する
int calcSubTotalScore(Player *pl);

Player *createPlayer() {
	Player *pl = (Player *)malloc(sizeof(Player));
	if (pl == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	initializePlayer(pl);

	return pl;
}

// プレイヤーの点数を初期化する
void initializePlayer(Player *pl) {
	pl->name = NULL;

	pl->ace = EMPTY;
	pl->deuce = EMPTY;
	pl->trey = EMPTY;
	pl->four = EMPTY;
	pl->five = EMPTY;
	pl->six = EMPTY;

	pl->choice = EMPTY;
	pl->four_dice = EMPTY;
	pl->full_house = EMPTY;
	pl->small_straight = EMPTY;
	pl->big_straight = EMPTY;
	pl->yahtzee = EMPTY;
}

// 得点がすべて埋まったかどうか確認
int isFull(Player *pl) {
	if (pl->ace == EMPTY ||
		pl->deuce == EMPTY ||
		pl->trey == EMPTY ||
		pl->four == EMPTY ||
		pl->five == EMPTY ||
		pl->six == EMPTY ||
		pl->choice == EMPTY ||
		pl->four_dice == EMPTY ||
		pl->full_house == EMPTY ||
		pl->small_straight == EMPTY ||
		pl->big_straight == EMPTY ||
		pl->yahtzee == EMPTY) {
		return 0;
	}
	return 1;
}

// 総合得点を計算する関数
int calcTotalScore(Player *pl) {
	int total = 0;
	int bonus_line = 63;
	int bonus = 35;

	if (pl->ace != EMPTY) {
		total += pl->ace;
	}
	if (pl->deuce != EMPTY) {
		total += pl->deuce;
	}
	if (pl->trey != EMPTY) {
		total += pl->trey;
	}
	if (pl->four != EMPTY) {
		total += pl->four;
	}
	if (pl->five != EMPTY) {
		total += pl->five;
	}
	if (pl->six != EMPTY) {
		total += pl->six;
	}
	if (pl->choice != EMPTY) {
		total += pl->choice;
	}
	if (pl->four_dice != EMPTY) {
		total += pl->four_dice;
	}
	if (pl->full_house != EMPTY) {
		total += pl->full_house;
	}
	if (pl->small_straight != EMPTY) {
		total += pl->small_straight;
	}
	if (pl->big_straight != EMPTY) {
		total += pl->big_straight;
	}
	if (pl->yahtzee != EMPTY) {
		total += pl->yahtzee;
	}
	// ボーナス点に達すると35点加算する
	if(calcSubTotalScore(pl) >= bonus_line) {
		total += bonus;
	}

	// 総合得点に追加する
	return total;
}

// 小計を計算する
int calcSubTotalScore(Player *pl) {
	int total = 0;

	if (pl->ace != EMPTY) {
		total += pl->ace;
	}
	if (pl->deuce != EMPTY) {
		total += pl->deuce;
	}
	if (pl->trey != EMPTY) {
		total += pl->trey;
	}
	if (pl->four != EMPTY) {
		total += pl->four;
	}
	if (pl->five != EMPTY) {
		total += pl->five;
	}
	if (pl->six != EMPTY) {
		total += pl->six;
	}

	return total;
}

void setScore(DiceList *dice, Player *pl, int select) {
	switch (select) {
	case 0:
		setAce(dice, pl);
		break;
	case 1:
		setDeuce(dice, pl);
		break;
	case 2:
		setTrey(dice, pl);
		break;
	case 3:
		setFour(dice, pl);
		break;
	case 4:
		setFive(dice, pl);
		break;
	case 5:
		setSix(dice, pl);
		break;
	case 6:
		setChoice(dice, pl);
		break;
	case 7:
		setFourDice(dice, pl);
		break;
	case 8:
		setFullHouse(dice, pl);
		break;
	case 9:
		setSmallStraight(dice, pl);
		break;
	case 10:
		setBigStraight(dice, pl);
		break;
	case 11:
		setYahtzee(dice, pl);
		break;
	default:
		break;
	}
}

// ��イ����ンドを計算する

// エースを計算する
void setAce(DiceList *dice, Player *pl) {
	pl->ace = calcAce(dice);
}

// デュースを計算する
void setDeuce(DiceList *dice, Player *pl) {
	pl->deuce = calcDeuce(dice);
}

// トレイを計算する
void setTrey(DiceList *dice, Player *pl) {
	pl->trey = calcTrey(dice);
}

// フォーを計算する
void setFour(DiceList *dice, Player *pl) {
	pl->four = calcFour(dice);
}

// ファイブを計算する
void setFive(DiceList *dice, Player *pl) {
	pl->five = calcFive(dice);
}

// シックスを計算する
void setSix(DiceList *dice, Player *pl) {
	pl->six = calcSix(dice);
}

// チョイスを計算する
void setChoice(DiceList *dice, Player *pl) {
	pl->choice = calcChoice(dice);
}

// フォーダイスを計算する
void setFourDice(DiceList *dice, Player *pl) {
	pl->four_dice = calcFourDice(dice);
}

// フルハウスを計算する
void setFullHouse(DiceList *dice, Player *pl) {
	pl->full_house = calcFullHouse(dice);
}

// スモールストレートを計算する
void setSmallStraight(DiceList *dice, Player *pl) {
	pl->small_straight = calcSmallStraight(dice);
}

// ビッグストレートを計算する
void setBigStraight(DiceList *dice, Player *pl) {
	pl->big_straight = calcBigStraight(dice);
}

// ヨットを計算する
void setYahtzee(DiceList *dice, Player *pl) {
	pl->yahtzee = calcYahtzee(dice);
}

void freePlayer(Player *pl) {
	if (pl != NULL) {
		if (pl->name != NULL) {
			free(pl->name);
		}
		free(pl);
	}
}
