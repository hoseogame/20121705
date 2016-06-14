#include "Bullet.h"
#include <cstring>
#include <ctime>

// ������ ��ȯ
int Bullet::TakeDamage()
{
	return nDamage;
}

// �Ѿ� ��ġ ����
void Bullet::SetPosition( int x, int y, DIRECT dir )
{
	// Ȱ��ȭ �Ǿ� ���� ������ ��ġ ����
	if( nLife == 0 )
	{
		nX = x;
		nY = y;
		eDirect = dir;
		nLife = 1;
	}
}

// �Ѿ� �̵�
void Bullet::Move( int key )
{
	clock_t curTime = clock();

	if( curTime - nOldMoveTime >= nMoveTime && nLife > 0)
	{
		nOldMoveTime = curTime;

		switch( eDirect )
		{
		case UP:	nY -= 1;break;
		case DOWN:	nY += 1;break;
		case LEFT:	nX -= 1;break;
		case RIGHT:	nX += 1;break;
		}
	}
}

// �Ѿ��� ������� �� ���
void Bullet::Draw()
{
	if( nLife > 0 )
	{
		if( eDirect == UP || eDirect == DOWN )
			screen->ScreenPrint( nX * 2, nY, "��" );
		else
			screen->ScreenPrint( nX * 2, nY, "��" );
	}
}

// ������Ʈ �浹 üũ
bool Bullet::IsCollision( Object* coll )
{
	if( nLife > 0 )
	{
		if( nullptr == coll )
		{
			// ������ �� : �� �ڸ� �� �������� ä��� �Ѿ� �����
			if( TankGame::GetMap( nX, nY ) == BLOCK )
			{
				nLife = 0;
				TankGame::SetMap( nX, nY, BLANK );
				return true;
			}

			// �ȱ����� �� : �Ѿ˸� �����
			else if( TankGame::GetMap( nX, nY ) == ROCK )
			{
				nLife = 0;
				return true;
			}

			// ����  : ���� ü�� ��
			else if( TankGame::GetMap( nX, nY ) == BOSS )
			{
				nLife = 0;
				--(stage->nBossLife);
			}
		}
		else
		{
			// �� ��ũor �� ��ũ�� �ε����� �Ѿ� �Ҹ� + ��ũ ������
			if( coll->GetX() == nX && coll->GetY() == nY && coll->GetLife() > 0)
			{
				nLife = 0;
				coll->RecvDamage( nDamage );
				return true;
			}
		}
	}

	// �ƹ��͵� �ȹ���
	return false;
}


// ������
Bullet::Bullet() : nDamage( 1 )
{
	stage = TankStage::Instance();
	nMoveTime = 100;
	nOldMoveTime = clock();
	nLife = 0;
	nX = 0;
	nY = 0;
}