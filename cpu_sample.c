#include "cpu_queue.h"
#include "dice_list.h"
#include "calc_score.h"
#include "player.h"
#include "cpu.h"
#include "calc_expected.h"
#include "game_cursor.h"
#include "cpu_op_dice.h"
#include "operation_bit.h"
#include "cpu_op_data.h"

#include <stdio.h>
#include <unistd.h>

// void playCpu(DiceList *dice, Player *pl) {
//     int trial_bit_array[MAX_TRIAL];
// }

void scoreDecisionAction(Queue *q, DiceList *dice, Player *pl) {
	int score[SCORE_MAX_NUM];
	float weight[SCORE_MAX_NUM] = {1.03, 1.02, 1.01, 1.0, 1.1, 1.2, 0.6, 1.0, 1.0, 1.0, 1.0, 1.0};
	// サイコロとプレイヤーの点数から配列を生成する
	searchScoreArray(pl, dice, score, weight);
	// どれだけ下ればいいかを決定する
	int max_value = findMaxScore(score, SCORE_MAX_NUM);
	int down_count = findScoreIndex(score, max_value);

	for(int i = 0; i < down_count; i++) {
		enqueue(q, KEY_DOWN);
	}
	// 最後に点数を決定するためにエンターを入れる
	enqueue(q, '\n');
}

// 最大期待値の特定
void choiceHighest(DiceList *dice, Player *pl, double *max_value, unsigned int *max_index) {

	double total = 0.0;
	unsigned int bit_count;
	double expected[MAX_TRIAL];

	// 代替え用のリストを生成
	DiceList *temp;
	initializeDiceList(&temp);

	// 全32通りの一番点数が獲得できる確率の高いものを探す
	for(int i = 0; i < MAX_TRIAL; i++) {

		// 1の値の個数を調べる
		bit_count = countOnesIn5bitBinary(i);
		copyList(dice, &temp);
		// 消去処理
		deleteByBit(&temp, i, MAX_BITS, 1);
		// ビットに応じて処理を変える
		switch(bit_count) {
			case 0:
				total = calcDiceZero(temp, pl);
				break;
			case 1:
				total = calcDiceOne(temp, pl);
				break;
			case 2:
				total = calcDiceTwo(temp, pl);
				break;
			case 3:
				total = calcDiceThree(temp, pl);
				break;
			case 4:
				total = calcDiceFour(temp, pl);
				break;
			case 5:
				total = calcDiceFive(temp, pl);
				break;
			default:
				break;
		}
		expected[i] = total;
		freeList(&temp);
		//usleep(10000);
	}

	// 最大値
	*max_value = findMax(expected, MAX_TRIAL);
	// 最大値の要素番目
	*max_index = findMaxIndex(expected, MAX_TRIAL);
}

// 行動決定処理
void CPUActionDecision(Queue *q, DiceList *dice, DiceList *keep, Player *pl, int reroll_count) {
	DiceList *all;
	initializeDiceList(&all);
	mergeLists(&all, keep, dice);

	DiceList *temp;
	initializeDiceList(&temp);

	DiceList *roll_temp;
	initializeDiceList(&roll_temp);
		// ここからが実際の処理
	double max_value;
	unsigned int max_index;

	choiceHighest(all, pl, &max_value, &max_index);


	// 振り直す処理
	// 振りなおすほうが期待値が高い
	// キープのダイスの数を計算する
	// キープを表している位置を特定する
	// 5ビットでキープの部分を1で表す
	unsigned int keep_dice_col = createLeadingOnesMask(countNodes(keep));
	// 振ったサイコロの数を計算する
	unsigned int roll_dice_col = createBitMask(countNodes(dice));

	// キープするか戻すかの動かすか否かを決定する
	unsigned int move_bit = calculateXOR(max_index, roll_dice_col);

	// もう振り直せないなら点数をいれるしかない
	if(reroll_count == 0) {
		// 点数表に移行して処理をする
		scoreDecisionAction(q, all, pl);
	}
	else {
		// 点数をつける処理
		if(max_index == 0) {

			// 点数を記入する場合の処理
			enqueue(q, KEY_LEFT);

			scoreDecisionAction(q, all, pl);
		}
		else {
			// * キープの処理
			// キープと合わせて数字を得る
			// キープしているサイコロが一つ以上あるとき
			// キープしているサイコロに入れ替え対象があるときとないとき

			// 動かす対象からキープの部分だけ抽出する
			unsigned int keep_reroll = calculateAND(keep_dice_col, move_bit);
			printf("ch\n");

			// サイコロが一つ以上動かす必要がある
			if(keep_reroll != 0) {
				copyList(all, &temp);

				deleteByBit(&temp, keep_reroll, MAX_BITS, 0);
				// キープから振り直すべきサイコロが存在する
				// 上入力を行って
				enqueue(q, KEY_UP);

				while(temp != NULL) {
					if(all->data == temp->data) {
						enqueue(q, '\n');
						temp = temp->next;
					}
					else {
						enqueue(q, KEY_RIGHT);
					}
					all = all->next;
				}

				// 全てキープから戻さない場合は下入力を挟む必要がある
				if(countNodes(keep) > countOnesIn5bitBinary(keep_reroll)) {
					enqueue(q, KEY_DOWN);
				}
				//!キープに対する処理終了
				freeList(&all);
				freeList(&temp);
				mergeLists(&all, keep, dice);
			}
			copyList(all, &roll_temp);
			copyList(all, &temp);

			// キープから移動したあとのサイコロ欄を示す
			unsigned int after_move = calculateOR(roll_dice_col, move_bit);
			deleteByBit(&roll_temp, after_move, MAX_BITS, 0);

			// サイコロ欄からキープすべきものを示す
			unsigned int move_keep = calculateAND(roll_dice_col, move_bit);
			deleteByBit(&temp, move_keep, MAX_BITS, 0);
			printList(temp);

			sortList(&roll_temp);

			while(temp != NULL) {
				if(roll_temp->data == temp->data) {
					enqueue(q, '\n');
					temp = temp->next;
				}
				else {
					enqueue(q, KEY_RIGHT);
				}
				roll_temp = roll_temp->next;
			}

			// 振り直す最後の処理
			// 下に移動して決定
			enqueue(q, KEY_DOWN);
			enqueue(q, '\n');
		}
	}
	// 処理が終わると解放
	freeList(&all);
	freeList(&temp);
	freeList(&roll_temp);
}

// CPUの行動をゲーム本体処理へ渡す
// dequeueの仲介
int CPUAction(Queue *q) {
	usleep(100000);
	return dequeue(q);
}

void initCPUActionQueue(Queue *q) {
	// 初期化
	// 最初にエンターでサイコロを振る処理
	enqueue(q, '\n');
}

// テスト用メイン関数
int main() {
	Queue *q = createQueue();

	DiceList *dice;
	initializeDiceList(&dice);
	DiceList *keep;
	initializeDiceList(&keep);
	addNodeAtEnd(&dice, 4);
	addNodeAtEnd(&dice, 6);
	addNodeAtEnd(&dice, 3);
	addNodeAtEnd(&dice, 1);
	addNodeAtEnd(&dice, 6);

	Player *pl;
	initializePlayer(&pl);

	CPUActionDecision(q, dice, keep, pl, 3);

	printQueue(q);

	freeQueue(q);
	freeList(&dice);
	freeList(&keep);
	freePlayer(pl);
	return 0;
}