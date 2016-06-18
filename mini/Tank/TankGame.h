#ifndef TANKGAME_H_
#define	TANKGAME_H_

#include "../BaseGame.h"
//#include "Object.h"	// ��� ������ ���⿡ �˻��� ���� ��ȣ ���� ������� Ű���带

class Tank;
class TankStage;
class EnemyTank;

class TankGame : public BaseGame
{
public :
	void Update() override;
	void Render() override;
	bool Exit() override;
	void Init() override;
	void Release() override;

	static int GetMap( int x, int y );				// �� ������ �޾ƿ´�.
	static void SetMap( int x, int y, int map );	// �� ����

	// BLANK : �����, BLOCK : ������ ��, ROCK : ������ �ʴ� ��, BOSS : ����
	enum OBJECT { BLANK = 0, BLOCK = 1, ROCK = 2, PLAYER = 3, BOSS = 4, ENEMY = 5 };

private :
	enum MAPSIZE { MAP_COL = 23, MAP_ROW = 18 };	// �� ũ�� ����
	static int nMap[MAP_ROW][MAP_COL];
	char m_tile[6][3] = { "  ", "��", "��", "��", "��", "��" };

	GAME_STAGE m_currentstage;		// ���� �������� ���¸� ����
	Tank* m_player;
	EnemyTank* m_enemy;

	TankStage* stage;

	void StageLoad(int _stage);		// �������� �ҷ�����
	void GameClearCheck();	// ���� ���� ���� üũ
	void ResetGame();

	// << ȭ�� ��� ���� �Լ�  >>
	void DrawMap();			// ���� �׸�
	void Box();				
	void InitScreen();
	void ReadyScreen();
	void StateScreen();
	void SuccessScreen();
	void FailureScreen();
	void ResultScreen();

public :
	TankGame();
	~TankGame() override;
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
