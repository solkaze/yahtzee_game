#include <stdio.h>
#include <unistd.h>

#include "dice_list.h"
#include "player.h"
#include "calc_score.h"

int calcWeightedMaxScore(DiceList* head, Player *pl);
double calcDiceZero(DiceList *dice, Player *pl);
double calcDiceOne(DiceList *dice, Player *pl);
double calcDiceTwo(DiceList *dice, Player *pl);
double calcDiceThree(DiceList *dice, Player *pl);
double calcDiceFour(DiceList *dice, Player *pl);
double calcDiceFive(DiceList *dice, Player *pl);


//エースからヨットまで全て計算し値の一番大きくなるスコアを返す
// エースからヨットまで全て計算し、プレイヤーのスコアがEMPTYである場合のみ最大スコアを返す
int calcWeightedMaxScore(DiceList* head, Player *pl) {
    int scores[] = {
        (pl->ace == EMPTY ? calcAce(head) : EMPTY),
        (pl->deuce == EMPTY ? calcDeuce(head) : EMPTY),
        (pl->trey == EMPTY ? calcTrey(head) : EMPTY),
        (pl->four == EMPTY ? calcFour(head) : EMPTY),
        (pl->five == EMPTY ? calcFive(head) : EMPTY),
        (pl->six == EMPTY ? calcSix(head) : EMPTY),
        (pl->choice == EMPTY ? calcChoice(head) : EMPTY),
        (pl->four_dice == EMPTY ? calcFourDice(head) : EMPTY),
        (pl->full_house == EMPTY ? calcFullHouse(head) : EMPTY),
        (pl->small_straight == EMPTY ? calcSmallStraight(head) : EMPTY),
        (pl->big_straight == EMPTY ? calcBigStraight(head) : EMPTY),
        (pl->yahtzee == EMPTY ? calcYahtzee(head) : EMPTY)
    };

    // 各計算の重みを設定
    double weights[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 0.9, 1.0, 0.8, 0.7, 1.0}; // 例: 各計算に対して異なる重みを設定

    int maxWeightedScore = 0;
    for (int i = 0; i < 12; i++) {
        if (scores[i] != EMPTY) {
            int weightedScore = scores[i] * weights[i];
            if (weightedScore > maxWeightedScore) {
                maxWeightedScore = weightedScore;
            }
        }
    }

    return maxWeightedScore;
}

double calcDiceZero(DiceList *dice, Player *pl) {
	DiceList *con_list;
	initializeDiceList(&con_list);
	copyList(dice, &con_list);
	int max = calcWeightedMaxScore(con_list, pl);
	freeList(&con_list);

	return max;
}


// 1つだけ振りなおす場合の処理
double calcDiceOne(DiceList *dice, Player *pl) {
	DiceList *con_list;
	double total_point = 0.0;
	int divide_dice_num = 6;
	initializeDiceList(&con_list);

	// リストをすべてコピーする
	copyList(dice, &con_list);
	addNodeAtBeginning(&con_list, 1);

	// サイコロの数だけ試行する
	for(int i = 1; i <= 6; i++) {
		// リストの要素番目をiに更新する
		updateNodeAt(con_list, 0, i);

		// 最大となるものをすべて足し合わせる
		total_point += calcWeightedMaxScore(con_list, pl);
	}
	freeList(&con_list);

	return total_point / divide_dice_num;
}

// 2つ振りなおす場合
double calcDiceTwo(DiceList *dice, Player *pl) {
	DiceList *con_list;
	double total_point = 0.0;
	int divide_dice_num = 6 * 6;
	initializeDiceList(&con_list);

	// リストをすべてコピーする
	copyList(dice, &con_list);
	addNodeAtBeginning(&con_list, 1);
	addNodeAtBeginning(&con_list, 1);

	for(int i = 1; i <= 6; i++) {
		for(int j = 1; j <= 6; j++) {
			// リストの要素番目を更新する
			updateNodeAt(con_list, 0, i);
			updateNodeAt(con_list, 1, j);

			// 最大となるものをすべて足し合わせる
			total_point += calcWeightedMaxScore(con_list, pl);
		}
	}
	freeList(&con_list);

	return total_point / divide_dice_num;
}

// 3つ振りなおす場合の処理
double calcDiceThree(DiceList *dice, Player *pl) {
	DiceList *con_list;
	double total_point = 0.0;
	int divide_dice_num = 6 * 6 * 6;
	initializeDiceList(&con_list);

	// リストをすべてコピーする
	copyList(dice, &con_list);
	addNodeAtBeginning(&con_list, 1);
	addNodeAtBeginning(&con_list, 1);
	addNodeAtBeginning(&con_list, 1);

	for(int i = 1; i <= 6; i++) {
		for(int j = 1; j <= 6; j++) {
			for(int k = 1; k <= 6; k++) {
				// リストの要素番目を更新する
				updateNodeAt(con_list, 0, i);
				updateNodeAt(con_list, 1, j);
				updateNodeAt(con_list, 2, k);

				// 最大となるものをすべて足し合わせる
				total_point += calcWeightedMaxScore(con_list, pl);
			}
		}
	}
	freeList(&con_list);

	return total_point / divide_dice_num;
}

// 4つ振りなおす場合の処理
double calcDiceFour(DiceList *dice, Player *pl) {
	DiceList *con_list;
	double total_point = 0.0;
	int divide_dice_num = 6 * 6 * 6 * 6;
	initializeDiceList(&con_list);

	// リストをすべてコピーする
	copyList(dice, &con_list);
	addNodeAtBeginning(&con_list, 1);
	addNodeAtBeginning(&con_list, 1);
	addNodeAtBeginning(&con_list, 1);
	addNodeAtBeginning(&con_list, 1);

	for(int i = 1; i <= 6; i++) {
		for(int j = 1; j <= 6; j++) {
			for(int k = 1; k <= 6; k++) {
				for(int l = 1; l <= 6; l++) {
					// リストの要素番目を更新する
					updateNodeAt(con_list, 0, i);
					updateNodeAt(con_list, 1, j);
					updateNodeAt(con_list, 2, k);
					updateNodeAt(con_list, 3, l);

					// 最大となるものをすべて足し合わせる
					total_point += calcWeightedMaxScore(con_list, pl);
				}
			}
		}
	}
	freeList(&con_list);

	return total_point / divide_dice_num;
}

// 5つ振りなおす場合の処理
double calcDiceFive(DiceList *dice, Player *pl) {
	DiceList *con_list;
	double total_point = 0.0;
	int divide_dice_num = 6 * 6 * 6 * 6 * 6;
	initializeDiceList(&con_list);

	// リストをすべてコピーする
	copyList(dice, &con_list);
	addNodeAtBeginning(&con_list, 1);
	addNodeAtBeginning(&con_list, 1);
	addNodeAtBeginning(&con_list, 1);
	addNodeAtBeginning(&con_list, 1);
	addNodeAtBeginning(&con_list, 1);

	for(int i = 1; i <= 6; i++) {
		for(int j = 1; j <= 6; j++) {
			for(int k = 1; k <= 6; k++) {
				for(int l = 1; l <= 6; l++) {
					for(int m = 1; m <= 6; m++) {
						// リストの要素番目を更新する
						updateNodeAt(con_list, 0, i);
						updateNodeAt(con_list, 1, j);
						updateNodeAt(con_list, 2, k);
						updateNodeAt(con_list, 3, l);
						updateNodeAt(con_list, 4, m);

						// 最大となるものをすべて足し合わせる
						total_point += calcWeightedMaxScore(con_list, pl);
					}
				}
			}
		}
	}
	freeList(&con_list);

	return total_point / divide_dice_num;
}