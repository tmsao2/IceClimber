#pragma once
#include "Scene.h"
class TitleScene :
	public Scene
{
private:
	int _titleImgH;
	int _topnumImgH;
	int _pointnumImgH;
	int _mountainImgH;
	int _count;
	int _Interval;
	float _wait;

	void (TitleScene::*_updater)(const Peripheral&);
	void FadeinUpdate(const Peripheral&);
	void NormalUpdate(const Peripheral&);
	void FadeoutUpdate(const Peripheral&);

public:
	TitleScene();
	~TitleScene();
	void Update(const Peripheral& p);
	void Draw();
};

