#ifndef TANK_STAGE_H_
#define TANK_STAGE_H_

/*
	- TankStage.h -
		* Stage Class
		* �������� ������ ������
		* �̱������� ����
*/

#include <time.h>
#define ROUND 1		// �������� �߰��� �÷���

struct POS_XY
{
	int nX, nY;
};

struct ENEMY_TYPE
{
	int nLife;
	int nMoveTime;
	int nFireTime;
	int nTypeIndex;
	int nPosIndex;
	int nAppearanceTime;
};

class TankStage
{
public :
	static TankStage* Instance();
	void StageReset( int round );
	void Init();
	int GetGrade() { return nGrade; }
	int GetStage() { return nStage; }

	void SetGrade( int score );

	int nEnemyCount;				// �� ĳ���� ��
	int nEnemyPositionCount;		// �� ���� ��ġ ����
	POS_XY *pEnemyPosition;			// �� ���� ��ġ �迭
	int nBossX, nBossY;				// ���� �ʱ� ��ġ
	int nPlayerX, nPlayerY;			// �÷��̾� �ʱ� ��ġ
	int nEnemyTypeCount;			// �� ĳ���� ���� ����
	ENEMY_TYPE enemyType[10];		// �� Ÿ�� ����
	int nEnemyIndex;				// ���� ������ �� ��
	int nDeadEnemy;

	int nBossLife;

private :
	int nGrade;						// ���� ����
	int nStage;						// ���� �������� ��

private :

	void Release();
	static TankStage* _instance;

	TankStage();
	~TankStage();
};

#endif /* TANK_STAGE_H_ */