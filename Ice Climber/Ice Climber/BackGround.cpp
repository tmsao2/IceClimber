#include <DxLib.h>
#include "BackGround.h"
#include "Camera.h"

const int img_x_size = 256;


BackGround::BackGround(const Camera & c) :_camera(c)
{
	bgimg1 = DxLib::LoadGraph("image/Stage1.png");
	bgimg2 = DxLib::LoadGraph("image/Stage2.png");
	bnimg = DxLib::LoadGraph("image/Bonus.png");
	unimg = DxLib::LoadGraph("image/UnderGround.png");
}

BackGround::~BackGround()
{
}

void BackGround::Update()
{
}

void BackGround::Draw()
{
	auto _tmp = _camera.GetViewport();
	auto scroll = _tmp.Top();//上スクロール値算出
	scroll %= (bgimg_y_size + bnimg_y_size + unimg_y_size )* 2;
	DxLib::DrawRotaGraph(512 - img_x_size, 480 - unimg_y_size - scroll, 2, 0, unimg, true);
	DxLib::DrawRotaGraph(512 - img_x_size, 480 - bgimg_y_size - unimg_y_size * 2 - scroll, 2, 0, bgimg1, true);
	DxLib::DrawRotaGraph(512 - img_x_size, 480 - (bgimg_y_size * 2) - bnimg_y_size - (unimg_y_size * 2) - scroll, 2, 0, bnimg, true);
}
