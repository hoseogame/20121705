#include "Object.h"
#include "TankStage.h"
#include <cstring>

// damage ��ŭ �������� ����
void Object::RecvDamage( int damage )
{
	nLife -= damage;
}

// �浹�n
bool Object::IsCollision( Object* coll )
{
	int map = TankGame::GetMap( nX, nY );

	// BLANK ���� ���� �浹ü�� �����ϰ� true ��ȯ
	if( map != BLANK && map != PLAYER && map != ENEMY )
		return true;
	return false;
	//if( map == BOSS )
	//	return BOSS;
	//nLife = 0;
	//if( map == ROCK )
	//	return ROCK;
	//if( map == BLOCK )
	//{
	//	TankGame::SetMap( nX, nY, BLANK );
	//	return BLOCK;
	//}

	//return BLANK;
}

// �׾����� üũ
bool Object::IsDead()
{
	// ������� 0���� ������ true
	if( nLife <= 0 )
		return true;
	return false;
}

// ����, �Ҹ���
Object::Object()
{
	TankStage* stage = TankStage::Instance();

	nX = 0, nY = 0;	
	eDirect = UP;	

	screen = Screen::Instance();
}

Object::~Object()
{
}