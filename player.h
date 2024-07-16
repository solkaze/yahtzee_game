#ifndef PLAYER_H
#define PLAYER_H

#define EMPTY (-1)
#define SCORE_MAX_NUM 12


#include "dice_list.h"

typedef struct player{
	char *name;

	int ace;             // エース
	int deuce;           // デュース
	int trey;            // トレイ
	int four;            // フォー
	int five;            // ファイブ
	int six;             // シックス

	int choice;          // チョイス

	int four_dice;       // フォーダイス
	int full_house;      // フルハウス
	int small_straight;  // S.ストレート
	int big_straight;    // B.ストレート
	int yahtzee;         // ヨット

}Player;

Player *createPlayer();

// Playerの情報を初期化
void initializePlayer(Player *pl);

// Playerの得点表がすべて埋まっているかを確認
int isFull(Player *pl);

// Playerの総合得点を返す
int calcTotalScore(Player *pl);

// 小計の計算
int calcSubTotalScore(Player *pl);

void setScore(DiceList *dice, Player *pl, int select);

// エースを計算する
void setAce(DiceList *dice, Player *pl);

// デュースを計算する
void setDeuce(DiceList *dice, Player *pl);

// トレイを計算する
void setTrey(DiceList *dice, Player *pl);

// フォーを計算する
void setFour(DiceList *dice, Player *pl);

// ファイブを計算する
void setFive(DiceList *dice, Player *pl);

// シックスを計算する
void setSix(DiceList *dice, Player *pl);

// チョイスを計算する
void setChoice(DiceList *dice, Player *pl);

// フォーダイスを計算する
void setFourDice(DiceList *dice, Player *pl);

// フルハウスを計算する
void setFullHouse(DiceList *dice, Player *pl);

// スモールストレートを計算する
void setSmallStraight(DiceList *dice, Player *pl);

// ビッグストレートを計算する
void setBigStraight(DiceList *dice, Player *pl);

// ヨットを計算する
void setYahtzee(DiceList *dice, Player *pl);

void freePlayer(Player *pl);
#endif // PLAYER_H