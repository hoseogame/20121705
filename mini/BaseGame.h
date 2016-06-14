#ifndef BASEGAME_H_
#define BASEGAME_H_

#include "Screen.h"
#include <ctime>
/*
	- BaseGame.h -
		* BaseGame Class
		* ������ ������Ʈ, ���� ��, ������ ������
		* �߻� Ŭ������ ����� ���� ����Ѵ�.
*/


class BaseGame
{
public:
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

	int KeyInput();	// �Է� ���� Ű ��ȯ

public:
	// ���� ���� �Լ��� ��� ���� Ŭ�������� ������( �������̵� ) �ؾ��� ---
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Init() = 0;
	virtual bool Exit() = 0;
	virtual void Release() = 0;
	// ---------------------------------------------------------------------

	Screen* screen;
protected:
	clock_t m_updateOldTime;		// ���� Ÿ��
	clock_t m_gameStartTime;		// ���� Ÿ��

public:
	BaseGame();
	virtual ~BaseGame();

};

#endif /*BASEGAME_H_*/