#include "Tank.h"
#include <ctime>

// �߽�!
void Tank::Fire()
{
	if( nBulletIndex < BULLET )
		bullet[nBulletIndex++].SetPosition( nX, nY, eDirect );
	else
		nBulletIndex = 0;
}

// �Ѿ� �޾ƿ�
//const Bullet* const Tank::GetBullet( int index )
//{
//	if( index < BULLET )
//		return bullet + index;
//	return bullet + (BULLET - 1);
//}

// �̵� �̵�
void Tank::Move( int key )
{
	clock_t curTime = clock();

	switch( key )
	{
		if( curTime - nOldMoveTime >= nMoveTime )
		{
		case UP:
			--nY; if( IsCollision() ) ++nY;
			eDirect = UP;
			break;
		case DOWN:
			++nY; if( IsCollision() ) --nY;
			eDirect = DOWN;
			break;
		case LEFT:
			--nX; if( IsCollision() ) ++nX;
			eDirect = LEFT;
			break;
		case RIGHT:
			++nX; if( IsCollision() ) --nX;
			eDirect = RIGHT;
			break;
		case 's' :
			Fire();
			break;
		nOldMoveTime = curTime;
		}
	}
}

void Tank::Draw()
{
	for( int i = 0; i < BULLET; ++i )
		bullet[i].Draw();
}


//bool Tank::IsCollision( Object* coll )
//{
//	return Object::IsCollision();
//}

Tank::Tank() : nBulletIndex( 0 ) 
{
	stage = TankStage::Instance();
	nMoveTime = 200;
	nFireTime = 200;
	nOldMoveTime = clock();
	nOldFireTime = clock();
}