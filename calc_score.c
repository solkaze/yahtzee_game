//* 得点の計算を定義

#include "dice_list.h"
#include "calc_score.h"

#include <stdlib.h>
#include <stdio.h>

// リスト内のvalueの数を調べ返す
int countOccurrences(DiceList* head, int value) {
	int count = 0;
	while (head != NULL) {
		if (head->data == value) {
			count++;
		}
		head = head->next;
	}
	return count;
}

// サイコロの合計値を計算する
int sumDice(DiceList* head) {
	int sum = 0;
	while (head != NULL) {
		sum += head->data;
		head = head->next;
	}
	return sum;
}

// 1の目を計算する
int calcAce(DiceList* head) {
	return countOccurrences(head, 1);
}

// 2の目を計算する
int calcDeuce(DiceList* head) {
	return 2 * countOccurrences(head, 2);
}

// 3の目を計算する
int calcTrey(DiceList* head) {
	return 3 * countOccurrences(head, 3);
}

// 4の目を計算する
int calcFour(DiceList* head) {
	return 4 * countOccurrences(head, 4);
}

// 5の目を計算する
int calcFive(DiceList* head) {
	return 5 * countOccurrences(head, 5);
}

// 6の目を計算する
int calcSix(DiceList* head) {
	return 6 * countOccurrences(head, 6);
}

// チョイスの計算
int calcChoice(DiceList* head) {
	return sumDice(head);
}

int calcFourDice(DiceList* head) {
	for (int i = 1; i <= 6; i++) {
		if (countOccurrences(head, i) >= 4) {
			return sumDice(head);
		}
	}
	return 0;
}

// フルハウスの計算
int calcFullHouse(DiceList* head) {
	int hasThree = 0, hasTwo = 0;
	for (int i = 1; i <= 6; i++) {
		int count = countOccurrences(head, i);
		if (count == 3) {
			hasThree = 1;
		} else if (count == 2) {
			hasTwo = 1;
		}
	}
	return (hasThree && hasTwo) ? sumDice(head) : 0;
}

// スモールストレートの計算
int calcSmallStraight(DiceList* head) {
    if (head == NULL) {
        return 0;
    }
    
    int counts[6] = {0}; // インデックスは1から6に対応
    
    while (head != NULL) {
        if (head->data >= 1 && head->data <= 6) {
            counts[head->data - 1]++;
        }
        head = head->next;
    }
    
    if ((counts[0] && counts[1] && counts[2] && counts[3]) ||
        (counts[1] && counts[2] && counts[3] && counts[4]) ||
        (counts[2] && counts[3] && counts[4] && counts[5])) {
        return 15;
    }
    
    return 0;
}

// ビッグストレートの計算
int calcBigStraight(DiceList* head) {
    if (head == NULL) {
        return 0;
    }
    
    int counts[6] = {0}; // インデックスは1から6に対応
    
    while (head != NULL) {
        if (head->data >= 1 && head->data <= 6) {
            counts[head->data - 1]++;
        }
        head = head->next;
    }
    
    if ((counts[0] && counts[1] && counts[2] && counts[3] && counts[4]) ||
        (counts[1] && counts[2] && counts[3] && counts[4] && counts[5])) {
        return 30;
    }
    
    return 0;
}

// ヨットの計算
int calcYahtzee(DiceList* head) {
	for (int i = 1; i <= 6; i++) {
		if (countOccurrences(head, i) == 5) {
			return 50;
		}
	}
	return 0;
}

//エースからヨットまで全て計算し値の一番大きくなるスコアを返す
int calculateScore(DiceList* head) {
	int scores[] = {
		calcAce(head),
		calcDeuce(head),
		calcTrey(head),
		calcFour(head),
		calcFive(head),
		calcSix(head),
		calcChoice(head),
		calcFourDice(head),
		calcFullHouse(head),
		calcSmallStraight(head),
		calcBigStraight(head),
		calcYahtzee(head)
	};

	int maxScore = 0;
	for (int i = 0; i < 12; i++) {
		if (scores[i] > maxScore) {
			maxScore = scores[i];
		}
	}

	return maxScore;
}