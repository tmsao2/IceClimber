#include "Ground.h"
#include <DxLib.h>

const int screen_x_size = 512;
const int ground_line = 480-(16+8)*2;

Ground::Ground()
{
}

Ground::~Ground()
{
}

int Ground::GetCurrentGroundY() const
{
	return ground_line;
}

void Ground::DebugDraw()
{
	DxLib::DrawLine(0, ground_line, screen_x_size, ground_line, 0xff0000);
}
