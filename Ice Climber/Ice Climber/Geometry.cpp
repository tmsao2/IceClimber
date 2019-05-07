#include "Geometry.h"
#include "DxLib.h"


Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}

Size::Size() : width(0), height(0) {}
Size::Size(int inx, int iny) {}

Rect::Rect() : center(0, 0), size(0, 0) {}
Rect::Rect(int x, int y, int w, int h) {}
Rect::Rect(Position2 & pos, Size & sz) : center(pos), size(sz) {}

const int Rect::Left() const
{
	return (center.x - size.width / 2);
}

const int Rect::Right() const
{
	return (center.x + size.width / 2);
}

const int Rect::Top() const
{
	return (center.y - size.height / 2);
}

const int Rect::Bottom() const
{
	return (center.y + size.height / 2);
}

void Rect::Draw(unsigned int color)
{
	DxLib::DrawBox(Left(), Right(), Top(), Bottom(), color, false);
}

void Rect::Draw(const Vector2 & offset, unsigned int color)
{
}
