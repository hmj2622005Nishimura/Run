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
