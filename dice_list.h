#ifndef DICE_LIST_H
#define DICE_LIST_H

// ノードの定義
typedef struct DiceList {
	int data;
	struct DiceList* next;
} DiceList;

// リストを初期化
void initializeDiceList(DiceList** head);

// 先頭にノードを追加
void addNodeAtBeginning(DiceList** head, int data);

// 末尾にノードを追加
void addNodeAtEnd(DiceList** head, int data);

// 昇順になるように追加
void insertNodeInOrder(DiceList** head, int data);

// リストを解放
void freeList(DiceList** head);

// リストを昇順にソート
void sortList(DiceList** head);

// 途中のノードを削除してその値を返す
int deleteDiceNode(DiceList** head, int data);

// 指定したインデックスの要素を返す
int getNodeAt(DiceList* head, int index);

// 指定したインデックスの要素を削除してその値を返す
int deleteNodeAt(DiceList** head, int index);

// リストの要素をカウントして返す
int countNodes(DiceList* head);

// 指定した要素を抜き出し新しいリストの末尾に挿入する
void transferNode(DiceList** currentList, DiceList** newList, int index);

// 昇順を維持するように挿入する
void transferInOrderNode(DiceList** currentList, DiceList** newList, int index);

// リストをコピーする
void copyList(DiceList* sourceList, DiceList** destinationList);

// 二つのリストを結合する
void mergeLists(DiceList** mergedList, DiceList* list1, DiceList* list2);

// 指定したインデックスの要素を更新する関数
void updateNodeAt(DiceList* head, int index, int newData);

// 末尾から指定された数だけノードを削除する関数
void deleteNodesFromEnd(DiceList** head, int count);

// リストの中身を全て表示する関数
void printList(DiceList* head);

#endif // DICE_LIST_H
