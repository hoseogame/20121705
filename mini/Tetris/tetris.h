#ifndef TETRIS_H_
#define TETRIS_H_

#include "../BaseGame.h"
#include "Block.h"
#define MAX_STAGE 10

class Tetris : public BaseGame
{
public :
	// 게임 스테이지 enumeration
	enum GAME_STAGE
	{
		INIT,		// 0 : 초기 화면 출력
		READY,		// 1 : 준비 화면 출력, RUNNING으로 밖에 못감
		RUNNING,	// 2 : 게임 시작, 조건 충족 시 STOP 으로 넘어간다.
		STOP,		// 3 : 목표 달성에 따라 SUCCESS or FAILED 로
		SUCCESS,	// 4 : 성공 화면이 출력되고 READY 상태로 돌아간다.
		FAILED,		// 5 : 실패 화면으로 재시작, 종료 결정을 한다.
		RESULT		// 6 : 최종 결과 화면으로 출력하고 게임이 종료된다.
	};

	virtual void Update();
	virtual void Render();
	virtual bool Exit();

private :
	virtual void Init();
	virtual void Release();

private:
	// 화면 출력 함수들
	void show_gameover();
	void show_cleargame();
	void show_gamestat();
	void show_logo();
	void input_data();

	bool GameOver();	// 게임 오버시 상태를 RESULT 로 바꿈
	void merge_block( int x, int y );	// 블럭들을 합친다.

	// 라인 이 꽉차면 실행되는 함수들
	void full_line_Set();		// 꽉찬 라인 정리 해줌 update
	int check_full_line();		// 꽉찬 라인 반환
	void full_line_erase();		// 꽉찬 라인 지워줌 render

	void press_any_key( int nkey );
	void level_select( int nKey );

	void LevelSet();

	Block* m_block;
	GAME_STAGE stage;

	clock_t m_oldTime;
	clock_t m_printTime;

	int m_level;
	int m_line;
	int m_score;
	int m_full_line_num;	// 한줄이 채워진 줄의 번호
	bool m_bIsGameOver;

	struct STAGE {			//각 스테이지마다의 난이도 설정
		clock_t	speed;		//숫자가 낮을수록 속도가 빠르다
		int stick_rate;		//막대가 나오는 확률 0~99 , 99면 막대기만 나옴
		int clear_line;
	};
	struct STAGE stage_data[MAX_STAGE];


	// 처음 초기화면 출력용 블럭에 사용
	int shape[4];
	int angle[4];
public :
	Tetris() { Init(); }
	~Tetris() override { Release(); }
};


#endif/*TETRIS_H_*/
