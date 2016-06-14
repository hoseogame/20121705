#ifndef TANK_STAGE_H_
#define TANK_STAGE_H_

/*
	- TankStage.h -
		* Stage Class
		* 스테이지 정보를 관리함
		* 싱글톤으로 만듬
*/

#include <time.h>
#define ROUND 1		// 스테이지 추가시 늘려줌

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

	int nEnemyCount;				// 적 캐릭터 수
	int nEnemyPositionCount;		// 적 생성 위치 개수
	POS_XY *pEnemyPosition;			// 적 생성 위치 배열
	int nBossX, nBossY;				// 보스 초기 위치
	int nPlayerX, nPlayerY;			// 플레이어 초기 위치
	int nEnemyTypeCount;			// 적 캐릭터 종류 개수
	ENEMY_TYPE enemyType[10];		// 적 타입 설정
	int nEnemyIndex;				// 현재 생성된 적 수
	int nDeadEnemy;

	int nBossLife;

private :
	int nGrade;						// 현재 점수
	int nStage;						// 현재 스테이지 수

private :

	void Release();
	static TankStage* _instance;

	TankStage();
	~TankStage();
};

#endif /* TANK_STAGE_H_ */