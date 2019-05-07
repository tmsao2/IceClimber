#include "TitleScene.h"
#include "DxLib.h"
#include "Game.h"
#include "Peripheral.h"
#include "GameScene.h"
#include <cmath>

const float waitTime = 30.0f;
const int defInterval = 60;
const int ShortInterval = 10;
const int chipsize = 8;

void TitleScene::FadeinUpdate(const Peripheral & p)
{
	_wait = max((_wait - 1), 0);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255 - 255 * (_wait / waitTime));
	Draw();
	if (_wait == 0) {
		_updater = &TitleScene::NormalUpdate;
	}
}

void TitleScene::NormalUpdate(const Peripheral & p)
{
	Draw();
	if (p.IsTrigger(PAD_INPUT_10)) {
		_Interval = ShortInterval;
		_updater = &TitleScene::FadeoutUpdate;
		_wait = waitTime;
	}
}

void TitleScene::FadeoutUpdate(const Peripheral & p)
{
	_wait = max((_wait - 1), 0);
	Draw();
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255 * (_wait / waitTime));
	if (_wait == 0) {
		Game::Instance().ChangeScene(new GameScene());
	}
}

TitleScene::TitleScene()
{
	_titleImgH = LoadGraph("image/Title.png");
	_topnumImgH = LoadGraph("image/TopNum.png");
	_pointnumImgH = LoadGraph("image/PointNum.png");
	_mountainImgH = LoadGraph("image/MountainNum.png");
	_wait = waitTime;
	_count = 0;
	_Interval = defInterval;
	_updater = &TitleScene::FadeinUpdate;
}


TitleScene::~TitleScene()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::Update(const Peripheral & p)
{
	_count++;
	(this->*_updater)(p);
}

void TitleScene::Draw()
{
	DrawRotaGraph(512 / 2, 480 / 2, 2, 0, _titleImgH, true);
	DrawRectRotaGraph(310 + chipsize * 2 , 328, 0, 0, chipsize*2, chipsize, 2, 0, _mountainImgH, true);
	for (int i = 0; i < 6; i++) {
		DrawRectRotaGraph(220 + chipsize * 2 * i, 360, 0, 0, chipsize, chipsize, 2, 0, _topnumImgH, true);
		DrawRectRotaGraph(105 + chipsize * 2 * i, 392, 0, 0, chipsize, chipsize, 2, 0, _pointnumImgH, true);
		DrawRectRotaGraph(330 + chipsize * 2 * i, 392, 0, 0, chipsize, chipsize, 2, 0, _pointnumImgH, true);
	}
}
