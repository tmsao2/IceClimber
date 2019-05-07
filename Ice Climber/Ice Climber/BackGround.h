#pragma once
#include "Geometry.h"

class Camera;

class BackGround
{
private:
	const Camera& _camera;
	int bgimg1;
	int bgimg2;
	int bnimg;
	int unimg;
public:
	BackGround(const Camera& c);
	~BackGround();

	void Update();
	void Draw();
};

