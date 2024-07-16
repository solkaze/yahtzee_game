#ifndef OPERATION_BIT_H
#define OPERATION_BIT_H

#define MAX_BITS 5

// unsigned int型の値を5ビットで表示する関数
void printBinary5Bits(unsigned int num);

// ゼロの個数を計算し返す
int countZerosIn5bitBinary(int num);

// 一の個数を計算し返す
int countOnesIn5bitBinary(int num);

// 2つの整数を2進数で結合する関数
int concatenateBinary(int num1, int num2);

// 排他的論理和を返す関数
unsigned int calculateXOR(unsigned int num1, unsigned int num2);

// 論理積を返す関数
unsigned int calculateAND(unsigned int num1, unsigned int num2);

// 論理和を返す関数
unsigned int calculateOR(unsigned int num1, unsigned int num2);

// 指定の数だけ1を敷き詰める関数
int createBitMask(int num);

// 指定の数だけ先頭から1を敷き詰める関数
int createLeadingOnesMask(int num);

// 指定した上位ビットを抽出して整数を返す関数
int extractUpperBits(int num, unsigned int bit_count);

// 指定した下位ビットを抽出して整数を返す関数
int extractLowerBits(int num, unsigned int bit_count);

// 指定した位置のビットが1か0かを返す関数
int getBit(int num, int position);

// 上位ビットから指定番目のビットを抽出する
int getBitFromTop(int num, int position);

#endif //OPERATION_BIT_H