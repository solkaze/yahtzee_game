#include <stdio.h>

// 5ビットの値をビットごとに配列に格納する関数
void storeFiveBitValueInArray(unsigned int value, unsigned int array[5]) {
    // ビットを分解して配列に格納
    for (int i = 0; i < 5; i++) {
        array[4 - i] = (value >> i) & 1;
    }
}

int main() {
    // テストする値
    unsigned int value = 17; // 13 = 01101 in binary

    // 5つのビットを格納する配列
    unsigned int bitArray[5];

    // 値をビット配列に変換
    storeFiveBitValueInArray(value, bitArray);

    // 結果を表示
    printf("Value: %u\n", value);
    printf("Bits: ");
    for (int i = 0; i < 5; i++) {
        printf("%u ", bitArray[i]);
    }
    printf("\n");

    return 0;
}