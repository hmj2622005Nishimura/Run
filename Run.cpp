#include"DxLib.h"
//#include"Run.h"
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

	while (1)
	{
		ClearDrawScreen();

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