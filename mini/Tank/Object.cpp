#include "Object.h"
#include "TankStage.h"
#include <cstring>

// damage 만큼 데미지를 받음
void Object::RecvDamage( int damage )
{
	nLife -= damage;
}

// 충돌쳌
bool Object::IsCollision( Object* coll )
{
	int map = TankGame::GetMap( nX, nY );

	// BLANK 외의 것은 충돌체로 간주하고 true 반환
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

// 죽었는지 체크
bool Object::IsDead()
{
	// 생명력이 0보다 작으면 true
	if( nLife <= 0 )
		return true;
	return false;
}

// 생성, 소멸자
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