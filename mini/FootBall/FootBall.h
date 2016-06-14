#ifndef FOOTBALL_H_
#define FOOTBALL_H_

/*
	- FootBall.h -
		* FootBall Class
		* �� ���� ������ �����Ų��.
		* Scene ��� ����
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

public :
	void Update() override;
	void Render() override;
	bool Exit() override;

private :
	void Init() override;	// �ʱ�ȭ ������
	void Release() override;

private :
	GAME_STAGE	m_currentStage;	// ���� �������� ���¸� ��Ÿ��
	Player*		m_player;		// �÷��̾�
	Ball*		m_ball;			// ��
	GoalPost*	m_goalPost;		// ���
	Effect*		m_effect;		// ����Ʈ
	Stage*		m_stageInfo;	// �������� ����

	const int STARTSTAGE = 0;
	int		m_nStage;		// ���� �������� -1 �� �ʱ�ȭ ���� ���¸� ����
	int		m_nBallCount;	// �������Ѿ� �� �� ��
	int		m_nGoalCount;	// ���� ���� ��Ų �� ��
	bool	m_bGoal;		// ��ǥ �޼� or ����
	bool	m_bEffect;		// ����Ʈ ����� ����

	// �ð� ���� ������, ���� �ð�, ���۵� �ð�, ������Ʈ �ð�
	clock_t m_limitTime, m_gameStartTime, m_updateOldTime;

	// ȭ�� ��� ���� �Լ�
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