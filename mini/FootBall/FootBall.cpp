#include <iostream>
#include "FootBall.h"
#include "Player.h"
#include "Ball.h"
#include "GoalPost.h"
#include "Effect.h"
#include "Stage.h"

#define SAFE_DELETE( x ); if( x != nullptr ) { delete x; x = nullptr; }

/* public �Լ� ------------------------ */

// ĳ����, ��, ����� ��ǥ, ���� ���� ������Ʈ
void FootBall::Update()
{
	clock_t curTime = clock();
	int key = KeyInput();

	switch( m_currentStage )
	{
	case INIT :
		if( key == ' ' && m_nStage == STARTSTAGE )
		{
			m_currentStage = READY;
			m_updateOldTime = clock();
		}
		break;
	case READY :
		if( curTime - m_updateOldTime > 2000 )
		{
			m_currentStage = RUNNING;
			m_gameStartTime = curTime;
		}
		break;
	case RUNNING :
		if( curTime - m_gameStartTime > m_limitTime )
		{
			m_currentStage = STOP;
		}
		else
		{
			m_player->PlayerUpdate( key );
			m_goalPost->GoalPostUpdate();
			m_ball->BallUpdate( key, m_player->GetMoveX(), m_player->GetMoveY() );
			// ���� �ߴ��� Ȯ��
			if( m_ball->IsGoal( m_goalPost->GetGoalLine(), m_goalPost->GetLineLen(), m_goalPost->GetPosY() ) )
			{
				++m_nGoalCount;
				// ������ ���� ��ǥ�� ���� ������ �� ����
				if( m_nBallCount == m_nGoalCount )
				{
					m_currentStage = STOP;
					m_bGoal = true;
				}
				// ����Ʈ
				if( !m_bEffect )
				{
					m_bEffect = true;
					m_effect->SetStartTime( curTime );
				}
			}

			if( m_bEffect )
			{
				if( curTime - m_effect->GetStartTime() > m_effect->GetStayTime() )
					m_bEffect = false;
			}
		}
		break;
	case STOP :
		if( m_bGoal )
		{
			m_currentStage = SUCCESS;
			m_updateOldTime = curTime;
		}
		else
		{
			m_currentStage = FAILED;
		}
		break;
	case SUCCESS :
		if( curTime - m_updateOldTime > 3000 )
		{
			m_updateOldTime = curTime;
			++m_nStage;
			Init();
			m_currentStage = READY;
		}
		break;
	case FAILED :
		if( key == 'y' || key == 'Y' )
		{
			Init();
			m_currentStage = READY;
		}
		if( key == 'n' || key == 'N' )
			m_currentStage = RESULT;
		break;
	}
}

// ������Ʈ �Լ����� ���ŵ� ����� ȭ���� ���
void FootBall::Render()
{
	switch( m_currentStage )
	{
	case INIT :
		if( m_nStage == STARTSTAGE )
			InitScreen();
		break;

	case READY :
		ReadyScreen();
		break;

	case RUNNING : 
		BackScreen();
		m_player->PlayerDraw();
		m_ball->BallDraw();
		m_goalPost->GoalPostDraw();
		// ����Ʈ On ������ �� ���
		if( m_bEffect )
			m_effect->EffectDraw( 10, 10 );
		break;

	case SUCCESS :
		SuccessScreen();
		break;

	case FAILED :
		FailureScreen();
		break;

	case RESULT : 
		ResultScreen();
		break;
	}
}

// ���� ������ �����Ǹ� true�� ��ȯ�ϴ� �Լ�
// ��� ȭ���� �Ǹ� ������.
bool FootBall::Exit()
{
	if( m_currentStage == RESULT )
	{
		Init();
		m_currentStage = READY;
		return true;
	}

	return false;
}


/* private �Լ� ----------------------- */
// �ʱ� ����
void FootBall::Init()
{
	// ��������
	if( m_nStage == -1 )
	{
		m_nStage = STARTSTAGE;
	}
	m_stageInfo = Stage::Instance();
	m_stageInfo->StageSet( m_nStage );

	// �÷��̾�
	m_player = new Player();

	// ��
	m_ball = new Ball( m_player->GetMoveX(), m_player->GetMoveY() );

	// ���
	m_goalPost = new GoalPost();

	// ����Ʈ
	m_effect = new Effect();

	// ���� �⺻ ����
	m_bGoal = false;
	m_limitTime = m_stageInfo->m_limitTime;
	m_nBallCount = m_stageInfo->m_nGoalBall;
	m_nGoalCount = 0;
	m_updateOldTime = clock();
}

// ��� �Ǿ��� �޸� ����
void FootBall::Release()
{
	SAFE_DELETE( m_player );
	SAFE_DELETE( m_ball );
	SAFE_DELETE( m_goalPost );
	SAFE_DELETE( m_effect );
}

// �ʱ� ȭ�� ���
void FootBall::InitScreen()
{
	screen->ScreenPrint( 0, 0, "����������������������������������������������" );
	screen->ScreenPrint( 0, 1, "��                                          ��" );
	screen->ScreenPrint( 0, 2, "��             �ব������                   ��" );
	screen->ScreenPrint( 0, 3, "��                                          ��" );
	screen->ScreenPrint( 0, 4, "��                        ///.   ��~~~      ��" );
	screen->ScreenPrint( 0, 5, "��                       (^.^)              ��" );
	screen->ScreenPrint( 0, 6, "��                      ���� ����           ��" );
	screen->ScreenPrint( 0, 7, "��                         ����             ��" );
	screen->ScreenPrint( 0, 8, "��                     ��  ����             ��" );
	screen->ScreenPrint( 0, 9, "��                                          ��" );
	screen->ScreenPrint( 0, 10, "��                                          ��" );
	screen->ScreenPrint( 0, 11, "��       �� ���� ����  Go! Go!              ��" );
	screen->ScreenPrint( 0, 12, "��                                          ��" );
	screen->ScreenPrint( 0, 13, "��                                          ��" );
	screen->ScreenPrint( 0, 14, "��       j :���� l : ������ k :��           ��" );
	screen->ScreenPrint( 0, 15, "��                                          ��" );
	screen->ScreenPrint( 0, 16, "��                                          ��" );
	screen->ScreenPrint( 0, 17, "��                                          ��" );
	screen->ScreenPrint( 0, 18, "��        ���ܦ�  space Ű�� �����ּ���     ��" );
	screen->ScreenPrint( 0, 19, "��                                          ��" );
	screen->ScreenPrint( 0, 20, "��                                          ��" );
	screen->ScreenPrint( 0, 21, "��                                          ��" );
	screen->ScreenPrint( 0, 22, "����������������������������������������������" );
}

// �غ� ȭ�� ���
void FootBall::ReadyScreen()
{
	char string[100];

	screen->ScreenPrint( 0, 0, "����������������������������������������������" );
	screen->ScreenPrint( 0, 1, "�����������������������᦭" );
	screen->ScreenPrint( 0, 2, "�����������������������᦭" );
	screen->ScreenPrint( 0, 3, "�����������������������᦭" );
	screen->ScreenPrint( 0, 4, "�����������������������᦭" );
	screen->ScreenPrint( 0, 5, "�����������������������᦭" );
	screen->ScreenPrint( 0, 6, "�����������������������᦭" );
	screen->ScreenPrint( 0, 7, "�����������������������᦭" );
	screen->ScreenPrint( 0, 8, "�����������������������᦭" );
	screen->ScreenPrint( 0, 9, "�����������������������᦭" );
	screen->ScreenPrint( 0, 10, "��������                    ������᦭" );
	sprintf_s( string, "��������     %d   ��������   ������᦭", m_nStage + 1 );
	screen->ScreenPrint( 0, 11, string );
	screen->ScreenPrint( 0, 12, "��������                    ������᦭" );
	screen->ScreenPrint( 0, 13, "�����������������������᦭" );
	screen->ScreenPrint( 0, 14, "�����������������������᦭" );
	screen->ScreenPrint( 0, 15, "�����������������������᦭" );
	screen->ScreenPrint( 0, 16, "�����������������������᦭" );
	screen->ScreenPrint( 0, 17, "�����������������������᦭" );
	screen->ScreenPrint( 0, 18, "�����������������������᦭" );
	screen->ScreenPrint( 0, 19, "�����������������������᦭" );
	screen->ScreenPrint( 0, 20, "�����������������������᦭" );
	screen->ScreenPrint( 0, 21, "�����������������������᦭" );
	screen->ScreenPrint( 0, 22, "�����������������������᦭" );
	screen->ScreenPrint( 0, 23, "����������������������������������������������" );
}

// ���� ���� �� ���ʿ� �׷��� ȭ��
void FootBall::BackScreen()
{
	char string[100];

	screen->ScreenPrint( 0, 0, "����������������������������������������������" );
	screen->ScreenPrint( 0, 1, "��                                          ��" );
	screen->ScreenPrint( 0, 2, "��                                          ��" );
	screen->ScreenPrint( 0, 3, "��                                          ��" );
	sprintf_s( string, "��                                          ����������: %d", m_nStage + 1 );
	screen->ScreenPrint( 0, 4, string );
	screen->ScreenPrint( 0, 5, "��                                          ��" );
	sprintf_s( string, "�������������������������������������������������� �ð�: %d", m_stageInfo->m_limitTime / 1000);
	screen->ScreenPrint( 0, 6, string );
	screen->ScreenPrint( 0, 7, "��                                          ��" );
	sprintf_s( string, "��                                          ������ �ð�: %d", (clock() - m_gameStartTime) / 1000 );
	screen->ScreenPrint( 0, 8, string );
	screen->ScreenPrint( 0, 9, "��                                          ��" );
	sprintf_s( string, "��                                          ����ǥ ����: %d ", m_stageInfo->m_nGoalBall );
	screen->ScreenPrint( 0, 10, string );
	screen->ScreenPrint( 0, 11, "��                                          ��" );
	sprintf_s( string, "��                                          ������ �� ����: %d ", m_nGoalCount );
	screen->ScreenPrint( 0, 12, string );

	screen->ScreenPrint( 0, 13, "��                                          ��" );
	sprintf_s( string, "��                                          ��" );
	screen->ScreenPrint( 0, 14, string );
	screen->ScreenPrint( 0, 15, "��                                          ��" );
	sprintf_s( string, "��                                          ��" );
	screen->ScreenPrint( 0, 16, string );
	screen->ScreenPrint( 0, 17, "��                                          ��" );
	screen->ScreenPrint( 0, 18, "��                                          ��" );
	screen->ScreenPrint( 0, 19, "��                                          ��" );
	screen->ScreenPrint( 0, 20, "��                                          ��" );
	screen->ScreenPrint( 0, 21, "��                                          ��" );
	screen->ScreenPrint( 0, 22, "��                                          ��" );
	screen->ScreenPrint( 0, 23, "����������������������������������������������" );
}

// ���� Ŭ����� ȭ�� ���
void FootBall::SuccessScreen()
{
	screen->ScreenPrint( 0, 0, "����������������������������������������������" );
	screen->ScreenPrint( 0, 1, "��                                          ��" );
	screen->ScreenPrint( 0, 2, "��                                          ��" );
	screen->ScreenPrint( 0, 3, "��                                          ��" );
	screen->ScreenPrint( 0, 4, "��                                          ��" );
	screen->ScreenPrint( 0, 5, "��                                          ��" );
	screen->ScreenPrint( 0, 6, "��                ////����                  ��" );
	screen->ScreenPrint( 0, 7, "��               q ��  �� p                 ��" );
	screen->ScreenPrint( 0, 8, "��               (��������)                 ��" );
	screen->ScreenPrint( 0, 9, "��             �� �̼� ���� ��              ��" );
	screen->ScreenPrint( 0, 10, "��                                          ��" );
	screen->ScreenPrint( 0, 11, "��                                          ��" );
	screen->ScreenPrint( 0, 12, "��                                          ��" );
	screen->ScreenPrint( 0, 13, "��                                          ��" );
	screen->ScreenPrint( 0, 14, "��                                          ��" );
	screen->ScreenPrint( 0, 15, "��                                          ��" );
	screen->ScreenPrint( 0, 16, "��                                          ��" );
	screen->ScreenPrint( 0, 17, "��                                          ��" );
	screen->ScreenPrint( 0, 18, "��                                          ��" );
	screen->ScreenPrint( 0, 19, "��                                          ��" );
	screen->ScreenPrint( 0, 20, "��                                          ��" );
	screen->ScreenPrint( 0, 21, "��                                          ��" );
	screen->ScreenPrint( 0, 22, "��                                          ��" );
	screen->ScreenPrint( 0, 23, "����������������������������������������������" );
}

// ���� ���� �� ȭ��
void FootBall::FailureScreen()
{
	screen->ScreenPrint( 0, 0, "����������������������������������������������" );
	screen->ScreenPrint( 0, 1, "��                                          ��" );
	screen->ScreenPrint( 0, 2, "��                                          ��" );
	screen->ScreenPrint( 0, 3, "��                                          ��" );
	screen->ScreenPrint( 0, 4, "��                                          ��" );
	screen->ScreenPrint( 0, 5, "��                                          ��" );
	screen->ScreenPrint( 0, 6, "��                                          ��" );
	screen->ScreenPrint( 0, 7, "��                                          ��" );
	screen->ScreenPrint( 0, 8, "��                                          ��" );
	screen->ScreenPrint( 0, 9, "��                                          ��" );
	screen->ScreenPrint( 0, 10, "��                                          ��" );
	screen->ScreenPrint( 0, 11, "��                    �̼� ���� !!!!        ��" );
	screen->ScreenPrint( 0, 12, "��                                          ��" );
	screen->ScreenPrint( 0, 13, "��                                          ��" );
	screen->ScreenPrint( 0, 14, "��                 �ܦ�����                 ��" );
	screen->ScreenPrint( 0, 15, "��                   ��  ��                 ��" );
	screen->ScreenPrint( 0, 16, "��                  �����                ��" );
	screen->ScreenPrint( 0, 17, "��                                          ��" );
	screen->ScreenPrint( 0, 18, "��        �ٽ� �Ͻðڽ��ϱ�? (y/n)          ��" );
	screen->ScreenPrint( 0, 19, "��                                          ��" );
	screen->ScreenPrint( 0, 20, "��                                          ��" );
	screen->ScreenPrint( 0, 21, "��                                          ��" );
	screen->ScreenPrint( 0, 22, "����������������������������������������������" );
}

// ��� ȭ��
void FootBall::ResultScreen()
{
	char string[100];
	screen->ScreenPrint( 0, 0, "����������������������������������������������" );
	screen->ScreenPrint( 0, 1, "��                                          ��" );
	screen->ScreenPrint( 0, 2, "��                                          ��" );
	screen->ScreenPrint( 0, 3, "��             �ব������                   ��" );
	screen->ScreenPrint( 0, 4, "��                                          ��" );
	screen->ScreenPrint( 0, 5, "��                                          ��" );
	screen->ScreenPrint( 0, 6, "��                                          ��" );
	screen->ScreenPrint( 0, 7, "��                                          ��" );
	sprintf_s( string, "��      ������ �������� :  %2d               ��", m_nStage + 1 );
	screen->ScreenPrint( 0, 8, string );
	screen->ScreenPrint( 0, 9, "��                                          ��" );
	screen->ScreenPrint( 0, 10, "��                                          ��" );
	screen->ScreenPrint( 0, 11, "��   ___�ƢƢ�___                           ��" );
	screen->ScreenPrint( 0, 12, "��     (*^  ^*)                             ��" );
	screen->ScreenPrint( 0, 13, "�� =====��==��=====                         ��" );
	screen->ScreenPrint( 0, 14, "��                                          ��" );
	screen->ScreenPrint( 0, 15, "��                                          ��" );
	screen->ScreenPrint( 0, 16, "��                                          ��" );
	screen->ScreenPrint( 0, 17, "��                                          ��" );
	screen->ScreenPrint( 0, 18, "��                      ���ܦ�              ��" );
	screen->ScreenPrint( 0, 19, "��                                          ��" );
	screen->ScreenPrint( 0, 20, "��                                          ��" );
	screen->ScreenPrint( 0, 21, "��                                          ��" );
	screen->ScreenPrint( 0, 22, "����������������������������������������������" );
}

FootBall::FootBall() :
	m_nStage( -1 ), m_currentStage( INIT ) 
{
	Init();
}

FootBall::~FootBall()
{
	Release();
}