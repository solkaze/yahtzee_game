#include "dice_list.h"
#include "player.h"
#include "calc_score.h"
#include "cpu_op_data.h"

// スコアのリストを生成する関数
// もしすでに埋まっているならばその行にはFULLを代入する
void searchScoreArray(Player *pl, DiceList *di, int score[SCORE_MAX_NUM], double weights[SCORE_MAX_NUM]) {
	// 配列内の各スコアに対する Player 構造体のメンバを指すポインタを設定
	int* player_scores[] = {&(pl->ace), &(pl->deuce), &(pl->trey), &(pl->four), &(pl->five), &(pl->six), &(pl->choice), &(pl->four_dice), &(pl->full_house), &(pl->small_straight), &(pl->big_straight), &(pl->yahtzee)};

	// 各スコアに対する計算関数へのポインタを設定
	int (*calc_functions[])(DiceList *) = {calcAce, calcDeuce, calcTrey, calcFour, calcFive, calcSix, calcChoice, calcFourDice, calcFullHouse, calcSmallStraight, calcBigStraight, calcYahtzee};

	for (int i = 0; i < SCORE_MAX_NUM; i++) {
		if (*(player_scores[i]) == EMPTY) {
			score[i] = calc_functions[i](di);
			// 重みを適用
			score[i] = (int)(score[i] * weights[i]);
		} else {
			score[i] = FULL;
		}
	}
}


// 配列内のスコアの場所を返す
int findScoreIndex(int score[SCORE_MAX_NUM], int target) {
	int countableIndex = 0;
	for (int i = 0; i < SCORE_MAX_NUM; i++) {
		if (score[i] != FULL) {
			if (score[i] == target) {
				return countableIndex;
			}
			countableIndex++;
		}
	}
	return -1;
}

// データの最大値を探す
double findMax(double arr[], int size) {
	double max = arr[0]; // 配列の最初の要素を最大値と仮定する
	for (int i = 1; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i]; // より大きい値が見つかった場合、最大値を更新する
		}
	}
	return max;
}

// scoreの最大値を探す
int findMaxScore(int arr[], int size) {
	int max = arr[0]; // 配列の最初の要素を最大値と仮定する
	for (int i = 1; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i]; // より大きい値が見つかった場合、最大値を更新する
		}
	}
	return max;
}
// データの最大値が何番目にあるか調べる関数
int findMaxIndex(double arr[], int size) {
	double max = arr[0];
	int max_index = 0;
	for (int i = 1; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
			max_index = i;
		}
	}
	return max_index;
}