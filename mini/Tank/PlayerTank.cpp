#include "PlayerTank.h"

// �÷��̾� ��ο�
void PlayerTank::Draw()
{
	Tank::Draw();
	screen->ScreenPrint( nX * 2, nY, "��" );
}


bool PlayerTank::IsCollision( Object* coll )
{
	return Object::IsCollision( coll );
}

void PlayerTank::Init()
{
	// �ʱ� ��ġ ����
	nX = stage->nPlayerX;
	nY = stage->nPlayerY;

	// ü�� ����
	nLife = 3;
}

PlayerTank::PlayerTank()
{
	Init();
}