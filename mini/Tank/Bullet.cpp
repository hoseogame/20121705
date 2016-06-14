#include "Bullet.h"
#include <cstring>
#include <ctime>

// 데미지 반환
int Bullet::TakeDamage()
{
	return nDamage;
}

// 총알 위치 설정
void Bullet::SetPosition( int x, int y, DIRECT dir )
{
	// 활성화 되어 있지 않으면 위치 설정
	if( nLife == 0 )
	{
		nX = x;
		nY = y;
		eDirect = dir;
		nLife = 1;
	}
}

// 총알 이동
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

// 총알이 살아있을 때 출력
void Bullet::Draw()
{
	if( nLife > 0 )
	{
		if( eDirect == UP || eDirect == DOWN )
			screen->ScreenPrint( nX * 2, nY, "┃" );
		else
			screen->ScreenPrint( nX * 2, nY, "━" );
	}
}

// 오브젝트 충돌 체크
bool Bullet::IsCollision( Object* coll )
{
	if( nLife > 0 )
	{
		if( nullptr == coll )
		{
			// 깨지는 벽 : 벽 자리 빈 공간으로 채우고 총알 사라짐
			if( TankGame::GetMap( nX, nY ) == BLOCK )
			{
				nLife = 0;
				TankGame::SetMap( nX, nY, BLANK );
				return true;
			}

			// 안깨지는 벽 : 총알만 사라짐
			else if( TankGame::GetMap( nX, nY ) == ROCK )
			{
				nLife = 0;
				return true;
			}

			// 보스  : 보스 체력 깎
			else if( TankGame::GetMap( nX, nY ) == BOSS )
			{
				nLife = 0;
				--(stage->nBossLife);
			}
		}
		else
		{
			// 적 탱크or 내 탱크와 부딪히면 총알 소멸 + 탱크 데미지
			if( coll->GetX() == nX && coll->GetY() == nY && coll->GetLife() > 0)
			{
				nLife = 0;
				coll->RecvDamage( nDamage );
				return true;
			}
		}
	}

	// 아무것도 안박음
	return false;
}


// 생성자
Bullet::Bullet() : nDamage( 1 )
{
	stage = TankStage::Instance();
	nMoveTime = 100;
	nOldMoveTime = clock();
	nLife = 0;
	nX = 0;
	nY = 0;
}