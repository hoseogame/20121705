#ifndef GOALPOST_H_
#define GOALPOST_H_
#include <time.h>

/*
	- GoalPost.h -
		* GoalPost Class
		* 골대 이동
*/

class GoalPost
{
public :
	void	GoalPostUpdate();
	void	GoalPostDraw();
	int		GetLineLen() const;
	int		GetPosY() const;
	const	int* const GetGoalLine() const;

private :
	void Init();
	void Release();

private :
	int		m_nMoveX, m_nMoveY;	// 이동 좌표
	int		m_nLength;			// 골대 길이
	int		m_nDist;			// 이동 거리
	int*	m_nLineX;			// 골대 라인 x 좌표
	int		m_nLineSize;		// 골대 라인 배열 길이
	clock_t m_moveTime;			// 이동 시간 간격
	clock_t m_oldTime;			// 이전 이동 시간
	clock_t m_curTime;			// 현재 시간

public :
	GoalPost();
	~GoalPost();
};

#endif /* GOALPOST_H_ */
