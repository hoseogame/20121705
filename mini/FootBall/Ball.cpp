#include "Ball.h"
#include "../Screen.h"

// �� �� ���¿� ���� ��ǥ ����
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
	inst->ScreenPrint( m_nMoveX, m_nMoveY, "��" );
}

// ���� ��ǥ�� ������ �ش�.
void Ball::BallMove()
{
	clock_t curTime = clock();

	if( curTime - m_oldTime > m_moveTime )
	{
		if( m_nMoveY - 1 > 0 )
		{
			--m_nMoveY;
			m_oldTime = curTime;	// ���� �̵� �ð��� ���ϱ� ���� ���� �ð��� ���� �ð� ������ ����
		}
		else
		{ // �� �ʱ�ȭ
			BallReset();
		}
	}
}

// �������� �ƴ��� ��ȯ
bool Ball::IsGoal( const int* const line, int lineSize, int goalPostY )
{
	if( m_nMoveY <= goalPostY )
	{	// ��� �� ���� �浹 == ����
		if( m_nMoveX >= line[0] && m_nMoveX + 1 <= line[lineSize - 1] + 1 )
		{
			BallReset();
			return true;
		}
		else if( // ��� �����ڸ� �浹
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

// ���� ���¸� ���� ��
void Ball::BallReset()
{
	m_bIsReady = true;
	m_nMoveX = m_playerX;
	m_nMoveY = m_playerY - 1;
}

// ���� �� ���·� �ٲ��ش�.
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