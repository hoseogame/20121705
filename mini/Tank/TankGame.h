#ifndef TANKGAME_H_
#define	TANKGAME_H_

#include "../BaseGame.h"
//#include "Object.h"	// 계속 에러가 나기에 검색해 보니 상호 참조 오류라는 키워드를

class Tank;
class TankStage;
class EnemyTank;

class TankGame : public BaseGame
{
public :
	virtual void Update() override;
	virtual void Render() override;
	virtual bool Exit() override;
	virtual void Init() override;
	virtual void Release() override;

	static int GetMap( int x, int y );				// 맵 정보를 받아온다.
	static void SetMap( int x, int y, int map );	// 맵 수정

	// BLANK : 빈공간, BLOCK : 깨지는 벽, ROCK : 깨지지 않는 벽, BOSS : 보스
	enum OBJECT { BLANK = 0, BLOCK = 1, ROCK = 2, PLAYER = 3, BOSS = 4, ENEMY = 5 };

private :
	enum MAPSIZE { MAP_COL = 23, MAP_ROW = 18 };	// 맵 크기 결정
	static int nMap[MAP_ROW][MAP_COL];
	char m_tile[6][3] = { "  ", "■", "▥", "◎", "♨", "◈" };

	GAME_STAGE m_currentstage;		// 현재 스테이지 상태를 저장
	Tank* m_player;
	EnemyTank* m_enemy;

	TankStage* stage;

	void StageLoad(int _stage);		// 스테이지 불러오기
	void GameClearCheck();	// 게임 성공 여부 체크
	void ResetGame();

	// << 화면 출력 관련 함수  >>
	void DrawMap();			// 맵을 그림
	void Box();				
	void InitScreen();
	void ReadyScreen();
	void StateScreen();
	void SuccessScreen();
	void FailureScreen();
	void ResultScreen();

public :
	TankGame();
	virtual ~TankGame();
};

template <typename T >
inline void SAFE_DELETE( T* p )
{
	if( nullptr == p )	return;

	delete p;
	p = nullptr;
}

template <typename T>
inline void SAFE_DELETE_ARRAY( T* p )
{
	if( nullptr == p ) return;

	delete[] p;
	p = nullptr;
}
#endif // !TANKGAME_H_
