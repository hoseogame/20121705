#include "Enemy.h"

// �� ��ũ ����
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

// ���͸� �ð����� ��
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

// �� ��ũ �̵� �κ�
void EnemyTank::Move( int key )
{
	clock_t curTime = clock();


	// ���� �ʾ����� �����̰ų� ȸ��
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
			if( nTemp != eDirect ) // ���� ������ �ƴϸ�
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
	{// �� ��ũ ����
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
	eDirect = ChangeIntToDirect(rand() % 4); // Note: ������ ���ǰ� ����
	nState = ENEMY_STOP;

	++count;
	if( count >= stage->nEnemyCount )
		count = 0;
}

// ����ũ �׸�
void EnemyTank::Draw()
{
	Tank::Draw();
	if( nLife > 0 )
		screen->ScreenPrint( nX * 2, nY, "��" );
}


bool EnemyTank::IsCollision( Object* coll )
{
	return Object::IsCollision( coll );
}

// ���ڸ� �������� �ٲ���
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

// �� ��ũ �ʱ�ȭ.
EnemyTank::EnemyTank()
{
	Init();
}