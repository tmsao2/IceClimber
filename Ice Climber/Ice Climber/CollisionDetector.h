#pragma once
#include "Geometry.h"

class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	const static bool IsCollided(const Rect& rcA, const Rect& rcB);
};
