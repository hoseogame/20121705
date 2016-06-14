#ifndef BALL_H_
#define BALL_H_

/*
	- Ball.h -
		* Ball Class
		* 공의 이동 및 충돌 검사
*/
#include <time.h>

class Ball
{
public :
	void BallUpdate( int nKey, int x, int y );	// 캐릭터의 좌표를 받음
	void BallDraw();
	bool IsGoal( const int* const line, int lineSize, int goalPostY );

private :
	void BallReset();
	void BallShoot();
	void BallMove();

	void Init();

private :
	bool	m_bIsReady;			// 준비 상태(1), 슛상태(0)
	int		m_nMoveX, m_nMoveY;		// 이동 좌표
	clock_t m_moveTime;			// 이동 시간 간격
	clock_t m_oldTime;			// 이전 이동 시간

	int		m_playerX, m_playerY;	// 플레이어 좌표를 받아온다.

public :
	Ball( int x, int y );
};

#endif /* BALL_H_ */