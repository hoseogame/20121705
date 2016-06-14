#ifndef GOALPOST_H_
#define GOALPOST_H_
#include <time.h>

/*
	- GoalPost.h -
		* GoalPost Class
		* ��� �̵�
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
	int		m_nMoveX, m_nMoveY;	// �̵� ��ǥ
	int		m_nLength;			// ��� ����
	int		m_nDist;			// �̵� �Ÿ�
	int*	m_nLineX;			// ��� ���� x ��ǥ
	int		m_nLineSize;		// ��� ���� �迭 ����
	clock_t m_moveTime;			// �̵� �ð� ����
	clock_t m_oldTime;			// ���� �̵� �ð�
	clock_t m_curTime;			// ���� �ð�

public :
	GoalPost();
	~GoalPost();
};

#endif /* GOALPOST_H_ */
