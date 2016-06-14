#ifndef TETRIS_H_
#define TETRIS_H_

#include "../BaseGame.h"
#include "Block.h"
#define MAX_STAGE 10

class Tetris : public BaseGame
{
public :
	// ���� �������� enumeration
	enum GAME_STAGE
	{
		INIT,		// 0 : �ʱ� ȭ�� ���
		READY,		// 1 : �غ� ȭ�� ���, RUNNING���� �ۿ� ����
		RUNNING,	// 2 : ���� ����, ���� ���� �� STOP ���� �Ѿ��.
		STOP,		// 3 : ��ǥ �޼��� ���� SUCCESS or FAILED ��
		SUCCESS,	// 4 : ���� ȭ���� ��µǰ� READY ���·� ���ư���.
		FAILED,		// 5 : ���� ȭ������ �����, ���� ������ �Ѵ�.
		RESULT		// 6 : ���� ��� ȭ������ ����ϰ� ������ ����ȴ�.
	};

	virtual void Update();
	virtual void Render();
	virtual bool Exit();

private :
	virtual void Init();
	virtual void Release();

private:
	// ȭ�� ��� �Լ���
	void show_gameover();
	void show_cleargame();
	void show_gamestat();
	void show_logo();
	void input_data();

	bool GameOver();	// ���� ������ ���¸� RESULT �� �ٲ�
	void merge_block( int x, int y );	// ������ ��ģ��.

	// ���� �� ������ ����Ǵ� �Լ���
	void full_line_Set();		// ���� ���� ���� ���� update
	int check_full_line();		// ���� ���� ��ȯ
	void full_line_erase();		// ���� ���� ������ render

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
	int m_full_line_num;	// ������ ä���� ���� ��ȣ
	bool m_bIsGameOver;

	struct STAGE {			//�� �������������� ���̵� ����
		clock_t	speed;		//���ڰ� �������� �ӵ��� ������
		int stick_rate;		//���밡 ������ Ȯ�� 0~99 , 99�� ����⸸ ����
		int clear_line;
	};
	struct STAGE stage_data[MAX_STAGE];


	// ó�� �ʱ�ȭ�� ��¿� ���� ���
	int shape[4];
	int angle[4];
public :
	Tetris() { Init(); }
	~Tetris() override { Release(); }
};


#endif/*TETRIS_H_*/
