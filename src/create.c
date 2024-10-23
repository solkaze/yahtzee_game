#include <time.h>
#include <stdlib.h>

#include "create.h"

// サイコロを降る関数
int rollDice();
// ランダム値をセットする関数
void initRandom();

int rollDice() {
	return (rand() % 6) + 1;
}

void initRandom() {
	srand(time(0));
}