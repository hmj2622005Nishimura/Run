#include"DxLib.h"
#include"Run.h"
#include"stdio.h"

	const int UpSpeed = 1;//↑キーを押した時の加速量
	const int DownSpeed = -1;//↓キーを押したときの減速量
	const int Life_MAX = 3;//ライフの最大値
	const int FPS = 60;
	const int WIDTH = 1200, HEIGHT = 720;//画面の幅、高さ
	const int obstancles_MAX = 2;//敵の種類
	
	int MoveSpeed = 30;//移動速度
	int Hyosiki = 0;//速度標識用
	int OverSpeed = 0;//速度超過分
	int BelowSpeed = 0;//速度が遅すぎた分
	int distance = 0;//スタート地点からの移動距離
	int Goal = 10000;//GoalがあるモードでのGoalまでの距離
	int HIdistance = 0;//到達したことのある最高地点
	int imgBackGround, imgRoad, imgRoad2, imgRoad3;//背景、道、道、道
	int imgPLC;//プレイヤーキャラ
	int imgObstancles[obstancles_MAX];//障害物
	int imgHYOSIKI;//標識
	
	enum{};

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

	while (1)
	{
		ClearDrawScreen();

		scrollRD(1);

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
	imgRoad2 = LoadGraph("images/car_road_copy.png");
	imgRoad3 = LoadGraph("images/car_road_copy2.png");
	imgPLC = LoadGraph("images/Playerchara.png");
}

void scrollRD(int spdRD)
{
	static int BackGroundY, RoadY;
	/*/BackGroundY = (BackGroundY + spdRD) % HEIGHT;
	DrawExtendGraph(0, BackGroundY - HEIGHT,1200,720, imgBackGround, FALSE);*/
	DrawExtendGraph(0, BackGroundY,1200,720, imgBackGround, FALSE);
	RoadY = (RoadY + spdRD * 2) % 120;
	for (int i = -1; i < 6; i++)
	{
		DrawGraph(100, RoadY + i * 130, imgRoad, TRUE);
		DrawGraph(600, RoadY + i * 130, imgRoad2, TRUE);
		DrawGraph(350, RoadY + i * 130, imgRoad3, TRUE);
	}
}