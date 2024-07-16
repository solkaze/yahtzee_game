#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "dice_list.h"

// リストを初期化
void initializeDiceList(DiceList** head) {
	*head = NULL;
}

// 先頭にノードを追加
void addNodeAtBeginning(DiceList** head, int data) {
	DiceList* newNode = (DiceList*)malloc(sizeof(DiceList));
	if (!newNode) {
		printf("Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	newNode->data = data;
	newNode->next = *head;
	*head = newNode;
}

// 末尾にノードを追加
void addNodeAtEnd(DiceList** head, int data) {
	DiceList* newNode = (DiceList*)malloc(sizeof(DiceList));
	if (!newNode) {
		printf("Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	newNode->data = data;
	newNode->next = NULL;
	if (*head == NULL) {
		*head = newNode;
		return;
	}
	DiceList* temp = *head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newNode;
}

// 昇順を維持しつつ値を挿入する関数
void insertNodeInOrder(DiceList** head, int data) {
	DiceList* newNode = (DiceList*)malloc(sizeof(DiceList));
	if (!newNode) {
		printf("Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	newNode->data = data;
	newNode->next = NULL;

	// リストが空の場合、または新しいノードが先頭に挿入される場合
	if (*head == NULL || (*head)->data >= data) {
		newNode->next = *head;
		*head = newNode;
		return;
	}

	// 挿入位置を探す
	DiceList* current = *head;
	while (current->next != NULL && current->next->data < data) {
		current = current->next;
	}

	newNode->next = current->next;
	current->next = newNode;
}

// リストを解放
void freeList(DiceList** head) {
	DiceList* temp;
	while (*head != NULL) {
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	*head = NULL;
}

// リストを昇順にソート
void sortList(DiceList** head) {
	if (*head == NULL || (*head)->next == NULL) {
		return;
	}

	DiceList* sorted = NULL;

	while (*head != NULL) {
		DiceList* temp = *head;
		*head = (*head)->next;

		if (sorted == NULL || sorted->data >= temp->data) {
			temp->next = sorted;
			sorted = temp;
		} else {
			DiceList* current = sorted;
			while (current->next != NULL && current->next->data < temp->data) {
				current = current->next;
			}
			temp->next = current->next;
			current->next = temp;
		}
	}

	*head = sorted;
}

// 途中のノードを削除してその値を返す
int deleteDiceNode(DiceList** head, int data) {
	if (*head == NULL) {
		printf("List is empty\n");
		return -1; // リストが空の場合
	}

	DiceList* temp = *head;
	DiceList* prev = NULL;

	// 先頭のノードが対象の場合
	if (temp != NULL && temp->data == data) {
		*head = temp->next;
		int deletedData = temp->data;
		free(temp);
		return deletedData;
	}

	// 対象のノードを検索
	while (temp != NULL && temp->data != data) {
		prev = temp;
		temp = temp->next;
	}

	// 対象のノードが見つからない場合
	if (temp == NULL) {
		printf("Node with data %d not found\n", data);
		return -1;
	}

	// ノードを削除
	prev->next = temp->next;
	int deletedData = temp->data;
	free(temp);

	return deletedData;
}

// 指定したインデックスの要素を返す
int getNodeAt(DiceList* head, int index) {
	DiceList* current = head;
	int count = 0;
	while (current != NULL) {
		if (count == index) {
			return current->data;
		}
		count++;
		current = current->next;
	}
	printf("Index %d out of bounds\n", index);
	return -1; // インデックスが範囲外の場合
}

// 指定したインデックスの要素を削除してその値を返す
int deleteNodeAt(DiceList** head, int index) {
	if (*head == NULL) {
		printf("List is empty\n");
		return -1; // リストが空の場合
	}

	DiceList* temp = *head;

	// インデックス0の場合
	if (index == 0) {
		*head = temp->next;
		int data = temp->data;
		free(temp);
		return data;
	}

	// 指定インデックスのノードを探す
	for (int i = 0; temp != NULL && i < index - 1; i++) {
		temp = temp->next;
	}

	// インデックスがリストの範囲外の場合
	if (temp == NULL || temp->next == NULL) {
		printf("Index %d out of bounds\n", index);
		return -1;
	}

	DiceList* nodeToDelete = temp->next;
	temp->next = nodeToDelete->next;
	int data = nodeToDelete->data;
	free(nodeToDelete);
	return data;
}

// リストの要素の数をカウントして返す
int countNodes(DiceList* head) {
	int count = 0;
	DiceList* current = head;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

// 指定したインデックスの要素を取り出し、新しいリストの末尾に追加する
void transferNode(DiceList** currentList, DiceList** newList, int index) {
	// まず、currentListから指定されたインデックスの要素を取り出す
	int data = deleteNodeAt(currentList, index);
	if (data != -1) {  // 削除が成功した場合のみ
		// 新しいリストの末尾にその要素を追加する
		addNodeAtEnd(newList, data);
	}
}

// 昇順を維持するように挿入する
void transferInOrderNode(DiceList** currentList, DiceList** newList, int index) {
	// まず、currentListから指定されたインデックスの要素を取り出す
	int data = deleteNodeAt(currentList, index);
	if (data != -1) {  // 削除が成功した場合のみ
		// 新しいリストの末尾にその要素を追加する
		insertNodeInOrder(newList, data);
	}
}

// 元のリストの要素をすべて新しいリストにコピーする
void copyList(DiceList* sourceList, DiceList** destinationList) {
	// 元のリストを走査し、各要素を新しいリストの末尾に追加する
	DiceList* current = sourceList;
	while (current != NULL) {
		addNodeAtEnd(destinationList, current->data);
		current = current->next;
	}
}

// 2つのリストを統合する関数
void mergeLists(DiceList** mergedList,DiceList* list1, DiceList* list2) {

	// リスト1の要素を統合リストに追加
	DiceList* current = list1;
	while (current != NULL) {
		addNodeAtEnd(mergedList, current->data);
		current = current->next;
	}

	// リスト2の要素を統合リストに追加
	current = list2;
	while (current != NULL) {
		addNodeAtEnd(mergedList, current->data);
		current = current->next;
	}
}

// 指定したインデックスの要素を更新する関数
void updateNodeAt(DiceList* head, int index, int newData) {
	DiceList* current = head;
	int count = 0;
	while (current != NULL) {
		if (count == index) {
			current->data = newData;
			return;
		}
		count++;
		current = current->next;
	}
}

// 末尾から指定された数だけノードを削除する関数
void deleteNodesFromEnd(DiceList** head, int count) {
	if (*head == NULL || count <= 0) {
		return;
	}

	// リストの長さを取得
	int length = countNodes(*head);

	// 削除すべきノードの数がリストの長さ以上の場合、リスト全体を削除
	if (count >= length) {
		freeList(head);
		return;
	}

	// 削除を開始する位置を計算
	int deleteStartIndex = length - count;

	// 指定された位置まで進む
	DiceList* current = *head;
	for (int i = 0; i < deleteStartIndex - 1; i++) {
		current = current->next;
	}

	// 指定された位置から末尾までのノードを削除
	DiceList* temp = current->next;
	current->next = NULL;
	while (temp != NULL) {
		DiceList* next = temp->next;
		free(temp);
		temp = next;
	}
}

// リストの中身を全て表示する関数
void printList(DiceList* head) {
	DiceList* current = head;
	printf("List: ");
	while (current != NULL) {
		printf("%d ->", current->data);
		current = current->next;
	}
	printf("\n");
}
