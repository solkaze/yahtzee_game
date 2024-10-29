#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "player.h"
#include "op_score_list.h"
#include "error.h"

void initializeScoreList(ScoreList **head) {
	*head = NULL;
}

// 新しいノードを作成する関数
ScoreList* createNode(Player *players[]) {
	ScoreList *newNode = (ScoreList*)malloc(sizeof(ScoreList));
	if (!newNode) {
		printf("Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 2; i++) {
		newNode->players[i] = *players[i];
		newNode->players[i].name = strdup(players[i]->name); // 名前を複製する
	}
	newNode->next = NULL;
	return newNode;
}

// リストの先頭にノードを追加する関数
void addNodeBeginningPlayer(ScoreList** head, Player *players[]) {
	ScoreList *newNode = createNode(players);
	newNode->next = *head;
	*head = newNode;
}

// リストの末尾にノードを追加する
void addNodeEndPlayer(ScoreList** head, Player *players[]) {
	ScoreList *newNode = createNode(players);
	if (*head == NULL) {
		*head = newNode;
	} else {
		ScoreList *temp = *head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
}

// リストを表示する関数
void printScoreList(ScoreList *head) {
	ScoreList *temp = head;
	while (temp != NULL) {
		for (int i = 0; i < 2; i++) {
			printf("Name: %s\n", temp->players[i].name);
			printf("Ace: %d\n", temp->players[i].ace);
			printf("Deuce: %d\n", temp->players[i].deuce);
			printf("Trey: %d\n", temp->players[i].trey);
			printf("Four: %d\n", temp->players[i].four);
			printf("Five: %d\n", temp->players[i].five);
			printf("Six: %d\n", temp->players[i].six);
			printf("Choice: %d\n", temp->players[i].choice);
			printf("Four Dice: %d\n", temp->players[i].four_dice);
			printf("Full House: %d\n", temp->players[i].full_house);
			printf("Small Straight: %d\n", temp->players[i].small_straight);
			printf("Big Straight: %d\n", temp->players[i].big_straight);
			printf("Yahtzee: %d\n", temp->players[i].yahtzee);
			printf("\n");
		}
		temp = temp->next;
	}
}

// リストのメモリを解放する関数
void freeScoreList(ScoreList **head) {
	ScoreList *temp;
	while (*head != NULL) {
		temp = *head;
		*head = (*head)->next;
		free(temp->players[0].name);
		free(temp->players[1].name);
		free(temp);
	}
	head = NULL;
}

// リストの内容をファイルに書き込む関数
int writeListToFile(WINDOW *win, ScoreList **head, const char *filename) {
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		scoreFileError(win);
		return 0;
	}

	ScoreList *temp;
	temp = *head;
	while (temp != NULL) {
		for (int i = 0; i < 2; i++) {
			fprintf(file, "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
				temp->players[i].name,
				temp->players[i].ace,
				temp->players[i].deuce,
				temp->players[i].trey,
				temp->players[i].four,
				temp->players[i].five,
				temp->players[i].six,
				temp->players[i].choice,
				temp->players[i].four_dice,
				temp->players[i].full_house,
				temp->players[i].small_straight,
				temp->players[i].big_straight,
				temp->players[i].yahtzee
			);
		}
		temp = temp->next;
	}

	fclose(file);

	return 1;
}

// ListNodeの要素数を数えて返す関数
int countScoreNode(ScoreList *head) {
	int count = 0;
	ScoreList *temp = head;
	while (temp != NULL) {
		count++;
		temp = temp->next;
	}
	return count;
}

// リストの最後尾を解放する関数
void freeLastNode(ScoreList **head) {
	if (*head == NULL) {
		return;
	}

	ScoreList *temp = *head;
	ScoreList *prev = NULL;
	while (temp->next != NULL) {
		prev = temp;
		temp = temp->next;
	}

	free(temp->players[0].name);
	free(temp->players[1].name);
	free(temp);

	if (prev == NULL) {
		*head = NULL;
	} else {
		prev->next = NULL;
	}
}

// ListNodeの要素数を数えたうえで
// 要素数が50より上の場合は50になるまで解放する
void freeLastNodeIfOver50(ScoreList **head) {
	while (countScoreNode(*head) > 50) {
		freeLastNode(head);
	}
}

// ファイルからリストを読み込む関数
int readListFromFile(WINDOW *win, ScoreList **head, const char *filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		// ファイルが見つからなかった場合、新しく生成して再度開く
		file = fopen(filename, "w+");
		if (file == NULL) {
			// ファイルの生成に失敗した場合
			scoreFileError(win);
			return 0;
		}
	}

	char buffer[256];
	while (fgets(buffer, sizeof(buffer), file)) {
		Player players[2];
		char nameBuffer[2][50]; // 一時的に名前を保持するバッファ
		for (int i = 0; i < 2; i++) {
			if (sscanf(buffer, "%49[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
					nameBuffer[i],
					&players[i].ace,
					&players[i].deuce,
					&players[i].trey,
					&players[i].four,
					&players[i].five,
					&players[i].six,
					&players[i].choice,
					&players[i].four_dice,
					&players[i].full_house,
					&players[i].small_straight,
					&players[i].big_straight,
					&players[i].yahtzee) != 13) {
				break;
			}
			players[i].name = strdup(nameBuffer[i]); // 名前を動的に割り当てる
			if (i == 1) {
				// 最後のプレイヤーを読み込んだ後
				Player *playerPointers[2] = { &players[0], &players[1] };
				addNodeEndPlayer(head, playerPointers);
			}
			if(i == 0) {
				if (!fgets(buffer, sizeof(buffer), file)) {
					break;
				}
			}
		}
	}

	fclose(file);
	// 正常終了
	return 1;
}


// 指定された番目の要素を返す関数
Player* getElement(ScoreList *head, int index) {
	ScoreList *temp = head;
	int i = 0;
	while (temp != NULL) {
		if (i == index) {
			return temp->players;
		}
		temp = temp->next;
		i++;
	}
	return NULL;
}

void inputHistory(WINDOW *win, Player *pl[]) {
	ScoreList *temp;

	initializeScoreList(&temp);
	readListFromFile(win, &temp, "../data/score.txt");
	addNodeBeginningPlayer(&temp, pl);
	freeLastNodeIfOver50(&temp);
	writeListToFile(win, &temp, "../data/score.txt");
	freeScoreList(&temp);
}