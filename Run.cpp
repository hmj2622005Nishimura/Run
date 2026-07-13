#include"DxLib.h"
#include"Run.h"
#include"stdio.h"

	const int UpSpeed = 1;//↑キーを押した時の加速量
	const int DownSpeed = -1;//↓キーを押したときの減速量
	const int Life_MAX = 3;//ライフの最大値
	const int FPS = 60;
	const int WIDTH = 1200, HEIGHT = 720;//画面の幅、高さ
	const int obstancles_MAX = 2;//敵の種類
	const int OBS_MAX = 100;//障害物の最大数
	
	float distance = 0;//スタート地点からの移動距離
	float MoveSpeed = 30;//移動速度

	int Hyosiki = 0;//速度標識用
	int OverSpeed = 0;//速度超過分
	int BelowSpeed = 0;//速度が遅すぎた分
	int Goal = 10000;//GoalがあるモードでのGoalまでの距離
	int HIdistance = 0;//到達したことのある最高地点
	int imgPLC;//プレイヤーキャラ	
	int imgBackGround, imgRoad, imgRoad2, imgRoad3;//背景、道、道、道
	int imgCat, imgUni;//猫、ウニ
	int timer = 0;

	int imgOBS[obstancles_MAX];//障害物
	int imgHYOSIKI;//標識
	
	enum{cat,uni};//敵の種類一覧

	struct OBJECT PLC;//プレイヤーキャラの宣言
	struct OBJECT OBS[OBS_MAX];//障害物の宣言

int APIENTRY WinMain(_In_ HINSTANCE hinstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetWindowText("a");//タイトル
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	initGame();
	initVariable();

	while (1)
	{
		ClearDrawScreen();
		timer++;

		scrollRD(1);
		distanceM();
		if (timer % 30 == 1)
		{
			int x = 100 + rand() % (WIDTH - 200);
			int y = -50;
			int e = rand() % 2;
			if (e == cat)
			{
				setOBS(x, y, 0, 3, cat, imgCat,imgOBS[cat]);
			}
			if (e == uni)
			{
				setOBS(x, y, 0, 3, uni, imgUni,imgOBS[uni]);

			}
		}
		moveOBS();
		movePlayer();

		ScreenFlip();
		if (ProcessMessage() == -1)
		{
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}

	DxLib_End();
	return 0;
}

void initGame(void)
{
	//画像読み込み
	imgBackGround = LoadGraph("images/back_ground.png");
	imgRoad = LoadGraph("images/car_road.png");
	imgRoad3 = LoadGraph("images/car_road_copy2.png");
	imgPLC = LoadGraph("images/Playerchara.png");
	imgCat = LoadGraph("images/cat.png");
	imgUni = LoadGraph("images/ウニ.png");
}

void scrollRD(int spdRD)
{
	static int BackGroundY, RoadY;
	BackGroundY = (BackGroundY + spdRD) % HEIGHT;
	DrawExtendGraph(0, BackGroundY - HEIGHT,1200,720, imgBackGround, FALSE);
	DrawExtendGraph(0, BackGroundY,1200,720, imgBackGround, FALSE);
	RoadY = (RoadY + spdRD * 2) % 120;
	for (int i = -1; i < 6; i++)
	{
		DrawGraph(100, RoadY + i * 130, imgRoad, TRUE);
		DrawGraph(600, RoadY + i * 130, imgRoad, TRUE);
		DrawGraph(350, RoadY + i * 130, imgRoad3, TRUE);
	}
}

void initVariable(void)
{
	PLC.x = WIDTH / 2;//初期地点の横軸設定
	PLC.y = HEIGHT - 100;//初期地点の高さ設定
	PLC.vx = 8;//移動速度
	PLC.vy = 0;
}

void drawImage(int img, int x, int y)
{
	int w, h;
	GetGraphSize(img, &w, &h);
	DrawExtendGraph(x - w / 5, y - h / 5, x + w / 5, y + h / 5, img, TRUE);
}

void movePlayer(void)
{
	if (CheckHitKey(KEY_INPUT_LEFT))//移動キー設定　左
	{
		PLC.x -= PLC.vx;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))//移動キー設定　右
	{
		PLC.x += PLC.vx;
	}
	drawImage(imgPLC, PLC.x, PLC.y);
}

void distanceM(void)
{
	if (distance >= 0)
	{
		distance = distance + MoveSpeed * 0.005f;
	}
	DrawFormatString(0, 0, 0xffff00, "移動距離%f M", distance);
}

int setOBS(int x, int y, int vx, int vy, int ptn, int img, int sld)
{
	for (int i = 0; i < OBS_MAX; i++)
	{
		if (OBS[i].state == 0)
		{
			OBS[i].x = x;
			OBS[i].y = y;
			OBS[i].vx = vx;
			OBS[i].vy = vy;
			OBS[i].state = 1;
			OBS[i].pattern = ptn;
			OBS[i].image = img;
			return i;
		}
	}
}

void moveOBS(void)
{
	for (int i = 0; i < OBS_MAX; i++)
	{
		if (OBS[i].state == 0)
		{
			continue;
		}
		OBS[i].x += OBS[i].vx;
		OBS[i].y += OBS[i].vy;
		drawImage(OBS[i].image, OBS[i].x, OBS[i].y);
		if (OBS[i].y < -200 || HEIGHT + 200 < OBS[i].y)
		{
			OBS[i].state = 0;
		}
	}
}