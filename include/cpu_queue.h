#ifndef CPU_QUEUE_H
#define CPU_QUEUE_H

// ノードの定義
typedef struct Node {
	int data;
	struct Node* next;
} Node;

// キューの定義
typedef struct Queue {
	Node* front;
	Node* rear;
} Queue;

Queue* createQueue();

// ノードを生成する関数
Node* createNode(int data);

// キューにデータを追加
void enqueue(Queue* q, int value);

// キューからデータを取り出す
int dequeue(Queue* q);

// キューの先頭のデータを取得
int front(Queue* q);

// キューを空にする関数
void freeQueue(Queue* q);

// キューの内容を表示する
void printQueue(Queue* q);

#endif // CPU_QUEUE_H