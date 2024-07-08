#include "operation_bit.h"

#include <stdio.h>

// unsigned int型の値を5ビットで表示する関数
void printBinary5Bits(unsigned int num) {

	// 各ビットをチェックし、表示
	for (int i = MAX_BITS - 1; i >= 0; i--) {
		unsigned int bit = (num >> i) & 1;
		printf("%u", bit);
	}
	printf("\n");
}

// ゼロの個数を計算し返す
int countZerosIn5bitBinary(int num) {
	int count = 0;
	for (int i = 0; i < MAX_BITS; i++) {
		if ((num & (1 << i)) == 0) {
			count++;
		}
	}
	return count;
}

// 一の個数を計算し返す
int countOnesIn5bitBinary(int num) {
	int count = 0;
	for (int i = 0; i < MAX_BITS; i++) {
		if ((num & (1 << i)) != 0) {
			count++;
		}
	}
	return count;
}
// 2つの整数を2進数で結合する関数
int concatenateBinary(int num1, int num2) {
    // num2のビット数を求める
    int num2_bits = 0;
    int temp = num2;
    while (temp > 0) {
        temp >>= 1;
        num2_bits++;
    }

    // num1をnum2のビット数だけ左シフトし、num2を結合
    return (num1 << num2_bits) | num2;
}

// 指定の数だけ1を敷き詰める関数
int createBitMask(int n) {
    if (n <= 0) {
        return 0;
    }
    return (1 << n) - 1;
}

// 指定の数だけ先頭から1を敷き詰める関数
int createLeadingOnesMask(int n) {
    if (n <= 0) {
        return 0;
    }
    if (n > MAX_BITS) {
        n = MAX_BITS;
    }
    return ((1 << n) - 1) << (MAX_BITS - n);
}

// 排他的論理和を返す関数
unsigned int calculateXOR(unsigned int num1, unsigned int num2) {
	return (num1 | num2) & (~(num1 & num2));
}

// 論理積を返す関数
unsigned int calculateAND(unsigned int num1, unsigned int num2) {
	return num1 & num2;
}

// 論理和を返す関数
unsigned int calculateOR(unsigned int num1, unsigned int num2) {
	return num1 | num2;
}

// 指定した上位ビットを抽出して整数を返す関数
int extractUpperBits(int num, unsigned int bit_count) {
	// numを上位bit_countビットだけ残すように右シフトし、左シフトせずそのまま返す
	int total_bits = sizeof(num) * 8;
	return (num >> (total_bits - bit_count)) & ((1 << bit_count) - 1);
}

// 指定した下位ビットを抽出して整数を返す関数
int extractLowerBits(int num, int bit_count) {
	// numの下位bit_countビットだけを残す
	return num & ((1 << bit_count) - 1);
}

// 指定した位置のビットが1か0かを返す関数
int getBit(int num, int position) {
	// 指定した位置のビットを取得するために、右シフトして1と論理積を取る
	return (num >> position) & 1;
}

// 上位ビットから指定番目のビットを抽出する
int getBitFromTop(int num, int position) {
    // 指定位置が範囲外の場合はエラーを返す（ここでは-1をエラー値とします）
    if (position < 0 || position >= MAX_BITS) {
        return -1;
    }

    // 上位からのビット位置を計算します
    int actualPosition = MAX_BITS - 1 - position;
    return (num >> actualPosition) & 1;
}
