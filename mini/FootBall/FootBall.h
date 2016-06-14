#ifndef FOOTBALL_H_
#define FOOTBALL_H_

/*
	- FootBall.h -
		* FootBall Class
		* 슛 골인 게임을 실행시킨다.
		* Scene 상속 받음
*/

#include <time.h>
#include "../BaseGame.h"

class Player;
class Ball;
class GoalPost;
class Effect;
class Stage;

class FootBall : public BaseGame
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

public :
	void Update() override;
	void Render() override;
	bool Exit() override;

private :
	void Init() override;	// 초기화 시켜줌
	void Release() override;

private :
	GAME_STAGE	m_currentStage;	// 현재 스테이지 상태를 나타냄
	Player*		m_player;		// 플레이어
	Ball*		m_ball;			// 공
	GoalPost*	m_goalPost;		// 골대
	Effect*		m_effect;		// 이펙트
	Stage*		m_stageInfo;	// 스테이지 정보

	const int STARTSTAGE = 0;
	int		m_nStage;		// 현재 스테이지 -1 은 초기화 전의 상태를 뜻함
	int		m_nBallCount;	// 성공시켜야 할 공 수
	int		m_nGoalCount;	// 현재 골인 시킨 공 수
	bool	m_bGoal;		// 목표 달성 or 실패
	bool	m_bEffect;		// 이펙트 띄울지 말지

	// 시간 관련 변수들, 제한 시간, 시작된 시간, 업데이트 시간
	clock_t m_limitTime, m_gameStartTime, m_updateOldTime;

	// 화면 출력 관련 함수
	void InitScreen();
	void ReadyScreen();
	void BackScreen();
	void SuccessScreen();
	void FailureScreen();
	void ResultScreen();

public :
	FootBall();

	~FootBall();
};

#endif /* FOOTBALL_H_ */