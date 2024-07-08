#ifndef QUEUE_H
#define QUEUE_H

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

void initializeQueue(Queue* q);

// ノードを生成する関数
Node* createNode(int data);

// enqueue関数
void enqueue(Queue* q, int data);

// dequeue関数
int dequeue(Queue* q);

// キューが空かどうかをチェックする関数
int isQueueEmpty(Queue* q);

// キューの内容を表示する関数
void displayQueue(Queue* q);

#endif // QUEUE_H