#ifndef BALL_H_
#define BALL_H_

/*
	- Ball.h -
		* Ball Class
		* ���� �̵� �� �浹 �˻�
*/
#include <time.h>

class Ball
{
public :
	void BallUpdate( int nKey, int x, int y );	// ĳ������ ��ǥ�� ����
	void BallDraw();
	bool IsGoal( const int* const line, int lineSize, int goalPostY );

private :
	void BallReset();
	void BallShoot();
	void BallMove();

	void Init();

private :
	bool	m_bIsReady;			// �غ� ����(1), ������(0)
	int		m_nMoveX, m_nMoveY;		// �̵� ��ǥ
	clock_t m_moveTime;			// �̵� �ð� ����
	clock_t m_oldTime;			// ���� �̵� �ð�

	int		m_playerX, m_playerY;	// �÷��̾� ��ǥ�� �޾ƿ´�.

public :
	Ball( int x, int y );
};

#endif /* BALL_H_ */