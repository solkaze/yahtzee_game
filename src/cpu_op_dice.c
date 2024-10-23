#include <stdio.h>
#include <stdlib.h>

#include "cpu_op_dice.h"
#include "dice_list.h"

// 指定された配列の値に基づいてリストの要素をDELに書き換える関数
void replaceNodesByBit(DiceList* head, int num, int size, unsigned int replaceIfBitIs);
// DELの要素をすべて削除する関数
void deleteDelNodes(DiceList** head);
// 置き換えと削除を同時に行う関数
void deleteByBit(DiceList** head, int num, int size, unsigned int replaceIfBitIs);

// 指定されたビットの値に基づいてリストの要素をDELに書き換える関数
void replaceNodesByBit(DiceList* head, int num, int size, unsigned int replaceIfBitIs) {
    DiceList* current = head;
    int index = 0;
    // sizeは二進数値のビット数と同じ
    while (current != NULL && index < size) {
        // numの上位ビットから順にチェック
        if (((num >> (size - 1 - index)) & 1) == replaceIfBitIs) {
            current->data = DEL;
        }
        current = current->next;
        index++;
    }
}

// リストからDELの値を持つノードを全て削除する関数
// ノードを削除する関数
void deleteDelNodes(DiceList** head_ref) {
    DiceList* current = *head_ref;
    DiceList* prev = NULL;

    // 先頭のノードに対象の値がある場合
    while (current != NULL && current->data == DEL) {
        *head_ref = current->next; // ヘッドを次に進める
        free(current); // 現在のノードを解放
        current = *head_ref; // 新しいヘッドをセット
    }

     // 先頭以外のノードに対して
    prev = current;
    if (current != NULL) {
        current = current->next;
    }

    while (current != NULL) {
        if (current->data == DEL) {
            prev->next = current->next;
            free(current);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// 置き換えと削除を同時に行う関数
void deleteByBit(DiceList** head, int num, int size, unsigned int replaceIfBitIs) {
    replaceNodesByBit(*head, num, size, replaceIfBitIs);
    deleteDelNodes(head);
}