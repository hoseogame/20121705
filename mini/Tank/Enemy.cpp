#include "Enemy.h"

// 적 탱크 공격
void EnemyTank::Fire()
{
	clock_t curTime = clock();
	//if( nState == ENEMY_RUN )
	//{
		if( curTime - nOldFireTime > nFireTime )
		{
			nOldFireTime = curTime;
			bullet[bulletCount].SetPosition( nX, nY, eDirect );
			++bulletCount;
		}
	//}
	if( bulletCount >= BULLET )
		bulletCount = 0;
}

// 몬스터를 시간마다 뽑
void EnemyTank::EnemySpawn( clock_t startTime )
{
	clock_t curTime = clock();

	if( stage->nEnemyIndex < stage->nEnemyCount )
	{
		if( nState == ENEMY_STOP )
		{
			if( curTime - startTime >= nAppearanceTime )
			{
				nState = ENEMY_RUN;
				nMoveTime = curTime;
				++(stage->nEnemyIndex);
			}
		}
	}
}

// 적 탱크 이동 부분
void EnemyTank::Move( int key )
{
	clock_t curTime = clock();


	// 죽지 않았으면 움직이거나 회전
	if( !IsDead() )
	{
		switch( nState )
		{
		case ENEMY_RUN :
			if( curTime - nOldMoveTime >= nMoveTime )
			{
				nOldMoveTime = curTime;
				switch( eDirect )
				{
				case UP:
					--nY; if( IsCollision() ) { ++nY; nState = ENEMY_ROTATION; }
					break;
				case DOWN:
					++nY; if( IsCollision() ) { --nY; nState = ENEMY_ROTATION; }
					break;
				case LEFT:
					--nX; if( IsCollision() ) { ++nX; nState = ENEMY_ROTATION; }
					break;
				case RIGHT:
					++nX; if( IsCollision() ) { --nX; nState = ENEMY_ROTATION; }
					break;
				}
			}
			Fire();
			break;
		case ENEMY_ROTATION :
			DIRECT nTemp = ChangeIntToDirect( rand() % 4 );
			if( nTemp != eDirect ) // 같은 방향이 아니면
			{
				eDirect = nTemp;
				nState = ENEMY_RUN;
				nOldMoveTime = curTime;
				break;
			}
			break;
		}
	}
	else
	{// 적 탱크 죽음
		nState = ENEMY_STOP;
	}
}

void EnemyTank::Init()
{
	static int count = 0;
	bulletCount = 0;
	nLife = stage->enemyType[count%stage->nEnemyTypeCount].nLife;
	nX = stage->pEnemyPosition[count%stage->nEnemyPositionCount].nX;
	nY = stage->pEnemyPosition[count%stage->nEnemyPositionCount].nY;
	nMoveTime = stage->enemyType[count%stage->nEnemyTypeCount].nMoveTime;
	nFireTime = stage->enemyType[count%stage->nEnemyTypeCount].nFireTime;
	nTypeIndex = stage->enemyType[count%stage->nEnemyCount].nTypeIndex;
	nPosIndex = stage->enemyType[count%stage->nEnemyCount].nPosIndex;
	nAppearanceTime = stage->enemyType[count%stage->nEnemyCount].nAppearanceTime;
	nOldMoveTime = clock();
	eDirect = ChangeIntToDirect(rand() % 4); // Note: 방향은 임의값 설정
	nState = ENEMY_STOP;

	++count;
	if( count >= stage->nEnemyCount )
		count = 0;
}

// 적탱크 그림
void EnemyTank::Draw()
{
	Tank::Draw();
	if( nLife > 0 )
		screen->ScreenPrint( nX * 2, nY, "★" );
}


bool EnemyTank::IsCollision( Object* coll )
{
	return Object::IsCollision( coll );
}

// 숫자를 방향으로 바꿔줌
Object::DIRECT EnemyTank::ChangeIntToDirect( int num )
{
	switch( num )
	{
	case 0 :
		return UP;
	case 1 :
		return DOWN;
	case 2 :
		return LEFT;
	case 3 :
		return RIGHT;
	default :
		return UP;
	}
}

// 적 탱크 초기화.
EnemyTank::EnemyTank()
{
	Init();
}