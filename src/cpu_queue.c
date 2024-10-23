#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "cpu_queue.h"

// キューの初期化
Queue* createQueue() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->front = q->rear = NULL;
	return q;
}

// キューが空かどうかを確認
int isEmpty(Queue* q) {
	return q->front == NULL;
}

// キューにデータを追加
void enqueue(Queue* q, int value) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = value;
	temp->next = NULL;
	if (q->rear == NULL) {
		q->front = q->rear = temp;
		return;
	}
	q->rear->next = temp;
	q->rear = temp;
}

// キューからデータを取り出す
int dequeue(Queue* q) {
	if (isEmpty(q)) {
		printf("Queue is empty\n");
		return -1;
	}
	Node* temp = q->front;
	int value = temp->data;
	q->front = q->front->next;
	if (q->front == NULL) {
		q->rear = NULL;
	}
	free(temp);
	return value;
}

// キューの先頭のデータを取得
int front(Queue* q) {
	if (isEmpty(q)) {
		printf("Queue is empty\n");
		return -1;
	}
	return q->front->data;
}

void freeQueue(Queue* q) {
	while (!isEmpty(q)) {
		dequeue(q);
	}
	free(q);
}

// キューの内容を表示する
void printQueue(Queue* q) {
	Node* temp = q->front;
	while (temp != NULL) {
		if(temp->data == KEY_DOWN) {
			printf("下");
		}else if(temp->data == KEY_UP) {
			printf("上");
		}else if(temp->data == KEY_LEFT) {
			printf("左");
		}else if(temp->data == KEY_RIGHT) {
			printf("右");
		}
		else if(temp->data == '\n') {
			printf("決");
		}
		else {
			printf("%d ", temp->data);
		}
		temp = temp->next;
	}
	printf("\n");
}