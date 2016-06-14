#ifndef BASEGAME_H_
#define BASEGAME_H_

#include "Screen.h"
#include <ctime>
/*
	- BaseGame.h -
		* BaseGame Class
		* 게임의 업데이트, 렌더 등, 게임을 관리함
		* 추상 클래스로 상속할 때만 사용한다.
*/


class BaseGame
{
public:
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

	int KeyInput();	// 입력 받은 키 반환

public:
	// 순수 가상 함수로 상속 받을 클래스에서 재정의( 오버라이딩 ) 해야함 ---
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Init() = 0;
	virtual bool Exit() = 0;
	virtual void Release() = 0;
	// ---------------------------------------------------------------------

	Screen* screen;
protected:
	clock_t m_updateOldTime;		// 업뎃 타임
	clock_t m_gameStartTime;		// 시작 타임

public:
	BaseGame();
	virtual ~BaseGame();

};

#endif /*BASEGAME_H_*/