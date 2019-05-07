#pragma once
#include "Geometry.h"


class Ground
{
public:
	Ground();
	~Ground();
	int GetCurrentGroundY() const;

	void DebugDraw();
};

