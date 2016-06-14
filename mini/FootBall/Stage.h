#ifndef STAGE_H_
#define STAGE_H_

/*
	- Stage.h -
		* Stage Class
		* �������� ������ ������
		* �̱������� ����
*/

#include <time.h>
#define ROUND 3		// �������� �ø��� ���� �� �ø��� �������� ����(42) �߰��� �ָ��.
#define INFO 7		// ���������� 7���� ������ ����ִ�.

class Stage
{
public :
	static Stage* Instance();
	void StageSet( int round );

	// �������� enumeration
	enum STAGE_INFO
	{
		GOALBALL,			// ���� �ؾ� �� �� ��
		GOALPOSTLEN,		// ����� ����
		GOALPOSX,			// ��� ���� x ��ǥ
		GOALPOSY,			// ��� ���� y ��ǥ
		DISTANCE,			// �̵� �Ÿ�
		MOVETIME,			// ��� �̵� �ð�, ���� ���� ����
		LIMITTIME			// ���� ���� �ð�
	};

	int m_nGoalBall;
	int m_nGoalPostLength;
	int m_nGoalPostX;		// ��� �̵� X ��ǥ
	int m_nGoalPostY;		// ��� �̵� Y ��ǥ 
	int m_nDist;			// ��� �̵� �Ÿ�
	clock_t m_moveTime;		// ��� �̵� �ð� ����
	clock_t m_limitTime;    // ���� �ð� 

	// �������� ����
	const int stageInfo[ROUND][INFO] = 	
	{
		// ���μ�, ������, ��� ���� ��ǥ, �̵� ����?
		{ 3, 2, 20, 5, 1, 300, 20 },	// 1 ����
		{ 3, 1, 20, 3, 1, 300, 20 },	// 2 ����
		{ 5, 1, 20, 3, 1, 200, 30}		// 3 ����
	};

private :

	void Init();
	void Release();
	static Stage* _instance;

	Stage();
	~Stage();
};

#endif /* STAGE_H_ */