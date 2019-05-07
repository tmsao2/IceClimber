#pragma once
#include "Scene.h"
class ResultScene :
	public Scene
{
private:
	int _resultImgH1;
	int _resultImgH2;
	int _count;
	int _Interval;
	float _wait;

	void (ResultScene::*_updater)(const Peripheral&);
	void FadeinUpdate(const Peripheral&);
	void NormalUpdate(const Peripheral&);
	void FadeoutUpdate(const Peripheral&);

public:
	ResultScene();
	~ResultScene();
	void Update(const Peripheral& p);
	void Draw();
};