#ifndef STAGE_H_
#define STAGE_H_

/*
	- Stage.h -
		* Stage Class
		* 스테이지 정보를 관리함
		* 싱글톤으로 만듬
*/

#include <time.h>
#define ROUND 3		// 스테이지 늘리고 싶을 때 늘리고 스테이지 정보(42) 추가해 주면됨.
#define INFO 7		// 스테이지에 7개의 정보가 들어있다.

class Stage
{
public :
	static Stage* Instance();
	void StageSet( int round );

	// 스테이지 enumeration
	enum STAGE_INFO
	{
		GOALBALL,			// 골인 해야 할 공 수
		GOALPOSTLEN,		// 골대의 길이
		GOALPOSX,			// 골대 시작 x 좌표
		GOALPOSY,			// 골대 시작 y 좌표
		DISTANCE,			// 이동 거리
		MOVETIME,			// 골대 이동 시간, 작을 수록 빠름
		LIMITTIME			// 게임 제한 시간
	};

	int m_nGoalBall;
	int m_nGoalPostLength;
	int m_nGoalPostX;		// 골대 이동 X 좌표
	int m_nGoalPostY;		// 골대 이동 Y 좌표 
	int m_nDist;			// 골대 이동 거리
	clock_t m_moveTime;		// 골대 이동 시간 간격
	clock_t m_limitTime;    // 제한 시간 

	// 스테이지 정보
	const int stageInfo[ROUND][INFO] = 	
	{
		// 골인수, 골대길이, 골대 시작 좌표, 이동 간격?
		{ 3, 2, 20, 5, 1, 300, 20 },	// 1 라운드
		{ 3, 1, 20, 3, 1, 300, 20 },	// 2 라운드
		{ 5, 1, 20, 3, 1, 200, 30}		// 3 라운드
	};

private :

	void Init();
	void Release();
	static Stage* _instance;

	Stage();
	~Stage();
};

#endif /* STAGE_H_ */