#include "Ball.h"
#include "../Screen.h"

// 공 의 상태에 따른 좌표 업뎃
void Ball::BallUpdate( int nKey, int x, int y )
{
	m_playerX = x;
	m_playerY = y;

	if( !m_bIsReady )
	{
		BallMove();
	}
	else
	{
		BallReset();
		if( nKey == 'k' )
		{
			BallShoot();
		}
	}
}

void Ball::BallDraw()
{
	Screen* inst = Screen::Instance();
	inst->ScreenPrint( m_nMoveX, m_nMoveY, "⊙" );
}

// 공의 좌표를 움직여 준다.
void Ball::BallMove()
{
	clock_t curTime = clock();

	if( curTime - m_oldTime > m_moveTime )
	{
		if( m_nMoveY - 1 > 0 )
		{
			--m_nMoveY;
			m_oldTime = curTime;	// 다음 이동 시각과 비교하기 위해 현재 시간을 이전 시간 변수에 저장
		}
		else
		{ // 공 초기화
			BallReset();
		}
	}
}

// 골인인지 아닌지 반환
bool Ball::IsGoal( const int* const line, int lineSize, int goalPostY )
{
	if( m_nMoveY <= goalPostY )
	{	// 골대 안 선과 충돌 == 골인
		if( m_nMoveX >= line[0] && m_nMoveX + 1 <= line[lineSize - 1] + 1 )
		{
			BallReset();
			return true;
		}
		else if( // 골대 가장자리 충돌
			(m_nMoveX >= line[0] - 2 && m_nMoveX <= line[0] - 1) ||
			(m_nMoveX + 1 >= line[0] - 2 && m_nMoveX + 1 <= line[0] - 1) ||
			(m_nMoveX >= line[lineSize - 1] + 2 && m_nMoveX <= line[lineSize - 1] + 3) ||
			(m_nMoveX + 1 >= line[lineSize - 1] + 2 && m_nMoveX + 1 <= line[lineSize - 1] + 3) )
		{
			BallReset();
		}
	}
	return false;
}

// 공의 상태를 리셋 함
void Ball::BallReset()
{
	m_bIsReady = true;
	m_nMoveX = m_playerX;
	m_nMoveY = m_playerY - 1;
}

// 공을 슛 상태로 바꿔준다.
void Ball::BallShoot()
{
	m_oldTime = clock();
	m_bIsReady = false;
}

void Ball::Init()
{
	m_bIsReady = true;
	m_moveTime = 100;
}

Ball::Ball( int x, int y ) : m_nMoveX( x ), m_nMoveY( y - 1 )
{
	Init();
}