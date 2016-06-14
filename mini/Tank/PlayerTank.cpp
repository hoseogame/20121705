#include "PlayerTank.h"

// 플레이어 드로우
void PlayerTank::Draw()
{
	Tank::Draw();
	screen->ScreenPrint( nX * 2, nY, "◈" );
}


bool PlayerTank::IsCollision( Object* coll )
{
	return Object::IsCollision( coll );
}

void PlayerTank::Init()
{
	// 초기 위치 지정
	nX = stage->nPlayerX;
	nY = stage->nPlayerY;

	// 체력 설정
	nLife = 3;
}

PlayerTank::PlayerTank()
{
	Init();
}