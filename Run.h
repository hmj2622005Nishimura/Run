#pragma once

struct OBJECT
{
	int x;//x座標
	int y;//ｙ座標
	int vx;//x軸の移動速度
	int vy;//y軸の移動速度
	int image;//画像
	int state;
	int pattern;
	int wid;
	int hei;
	int timer;
};

void initGame(void);
void scrollRD(int spdRD);
void initVariable(void);
void drawImage(int img, int x, int y);
void movePlayer(void);
int setEnemy(int x, int y, int vx, int vy, int ptn, int img, int sld);
void moveOBS(void);
void distanceM(void);