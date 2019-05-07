#include "CollisionDetector.h"
#include <cstdlib>
#include "CharacterObject.h"
#include "Game.h"


CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}

const bool CollisionDetector::IsCollided(const Rect& rcA, const Rect& rcB)
{
	Game& game = Game::Instance();

	return (abs(rcA.center.y - rcB.center.y) < (rcA.Height() + rcB.Height()) / 2) && (abs(rcA.center.x - rcB.center.x) < (rcA.Width() + rcB.Width()) / 2);
}
