#include "ResultScene.h"
#include "DxLib.h"
#include "Game.h"
#include "Peripheral.h"
#include "TitleScene.h"
#include <cmath>

const float waitTime = 30.0f;
const int defInterval = 60;
const int ShortInterval = 10;

void ResultScene::FadeinUpdate(const Peripheral & p)
{
	_wait = max((_wait - 1), 0);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255 - 255 * (_wait / waitTime));
	Draw();
	if (_wait == 0) {
		_updater = &ResultScene::NormalUpdate;
	}
}

void ResultScene::NormalUpdate(const Peripheral & p)
{
	Draw();
	if (p.IsTrigger(PAD_INPUT_10)) {
		_Interval = ShortInterval;
		_updater = &ResultScene::FadeoutUpdate;
		_wait = waitTime;
	}
}

void ResultScene::FadeoutUpdate(const Peripheral & p)
{
	_wait = max((_wait - 1), 0);
	Draw();
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255 * (_wait / waitTime));
	if (_wait == 0) {
		Game::Instance().ChangeScene(new TitleScene());
	}
}

ResultScene::ResultScene()
{
	_resultImgH1 = LoadGraph("image/Result1.png");
	_resultImgH2 = LoadGraph("image/Result2.png");
	_wait = waitTime;
	_count = 0;
	_Interval = defInterval;
	_updater = &ResultScene::FadeinUpdate;
}


ResultScene::~ResultScene()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ResultScene::Update(const Peripheral & p)
{
	_count++;
	(this->*_updater)(p);
}

void ResultScene::Draw()
{
	DxLib::DrawRotaGraph(512 / 2, 480 / 2, 2, 0, _resultImgH1, true);

}
