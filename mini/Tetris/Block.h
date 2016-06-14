#ifndef BLOCK_H_
#define BLOCK_H_

#define MAX_SIZE_X 14
#define MAX_SIZE_Y 21
#define AB_X 5
#define AB_Y 1
#define BLOCK_VOL 7
#include "../Screen.h"
#include <time.h>

class Block
{
public :
	// 블럭 모양 0-6
	enum SHAPE
	{
		STICK,		// 0 : 막대모양
		SQUARE,		// 1 : 네모모양
		T_SHAPE,	// 2 : 'ㅓ'모양
		J_SHAPE,	// 3 : 'ㄱ'모양
		L_SHAPE,	// 4 : 'ㄴ'모양
		Z_SHAPE,	// 5 : 'Z' 모양
		S_SHAPE		// 6 : 'S' 모양
	};

	// update
	void Move( int nKey );
	// render
	void Draw();
	void show_cur_block( int shape, int angle, int x, int y );

	// 블럭 상태 0 : 아무것도 아님 1: 게임오버 2: 바닥이나 다른 블럭에 닿음
	int GetBlockState() { return m_block_state; }
	int GetBlockX() { return m_x; }
	int GetBlockY() { return m_y; }
	char GetBlock( int y, int x ) { return m_block[m_shape][m_angle][y][x]; }
	char GetTotalBlock( int y, int x ) { return m_total_block[y][x]; }

	void SetTotalBlock( int y, int x, char data );
	void NextBlockInit();

	void SetMoveTime( clock_t time ) { m_moveTime = time; }
	void SetStickRate( int rate ) { m_stick_rate = rate; }

private :
	int MakeBlock();
	// update
	int BlockDown( int* shape, int* angle, int* x, int* y, int* next_shape );
	void Rotation();
	void block_start( int* angle, int* x, int* y );
	bool strike_check( int shape, int angle, int x, int y );

	// render
	void erase_cur_block( int shape, int angle, int x, int y );
	void show_total_block();
	void show_next_block( int shape );

	void Init();

public :
	// 블럭 모양 미리 만들어 둠.
	const char m_block[BLOCK_VOL][4][4][4] = {
		//막대모양
		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

		//네모모양
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

		//'ㅓ' 모양
		0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'ㄱ'모양
		1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'ㄴ' 모양
		1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

		//'Z' 모양
		1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

		//'S' 모양
		0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0

	};

private :
	char m_total_block[MAX_SIZE_Y][MAX_SIZE_X];
	const int ab_x, ab_y;	//화면중 블럭이 나타나는 좌표의 절대위치

	// 블럭 상태 0 : 아무것도 아님 1: 게임오버 2: 바닥이나 다른 블럭에 닿음
	int m_block_state;	

	// 블럭 정보
	int m_shape, m_angle, m_x, m_y;
	int next_block_shape;
	int m_stick_rate;

	clock_t m_oldTime;	// 이전 이동했던 시간
	clock_t m_moveTime;	// 블럭이 내려가는 속도? 시간

	Screen* screen;

public:
	Block() :ab_x( AB_X ), ab_y( AB_Y ), m_stick_rate( 15 ) { Init(); }
	~Block() {}
};

#endif // !BLOCK_H_
