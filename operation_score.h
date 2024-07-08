#ifndef OPERATION_SCORE_H
#define OPERATION_SCORE_H

#include "player.h"

#include <ncurses.h>

// リストのノードの定義
typedef struct ListNode {
	Player players[2]; // プレイヤーの配列を要素とする
	struct ListNode *next;
}ScoreList;

void initializeScoreList(ScoreList **head);

// リストの先頭にノードを追加する
void addNodeBeginningPlayer(ScoreList** head, Player *players[]);

// リストの末尾にノードを追加する
void addNodeEndPlayer(ScoreList** head, Player *players[]);

// リストを表示する関数
void printScoreList(ScoreList *head);

// リストのメモリを解放する関数
void freeScoreList(ScoreList **head);

// リストの内容をファイルに書き込む関数
int writeListToFile(WINDOW *win, ScoreList **head, const char *filename);

// ListNodeの要素数を数えて返す関数
int countScoreNode(ScoreList *head);

// ListNodeの要素数を数えたうえで
// 要素数が50より上の場合は50になるまで解放する
void freeLastNodeIfOver50(ScoreList **head);

// ファイルからリストを読み込む関数
int readListFromFile(WINDOW *win, ScoreList **head, const char *filename);

// 指定された番目の要素を返す関数
Player* getElement(ScoreList *head, int index);

// Playerの構造体を受け取り、ファイルへ書き込みまで行う
void inputHistory(WINDOW *win, Player *pl[]);

#endif