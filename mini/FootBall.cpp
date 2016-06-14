#include <iostream>
#include "FootBall\FootBall.h"

#define SAFE_DELETE( x ); if( x != nullptr ) { delete x; x = nullptr; }

/* public 함수 ------------------------ */

// 캐릭터, 공, 골대의 좌표, 값에 대한 업데이트
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
			// 골인 했는지 확인
			if( m_ball->IsGoal( m_goalPost->GetGoalLine(), m_goalPost->GetLineLen(), m_goalPost->GetPosY() ) )
			{
				++m_nGoalCount;
				// 골인한 수가 목표한 수와 같으면 겜 성공
				if( m_nBallCount == m_nGoalCount )
				{
					m_currentStage = STOP;
					m_bGoal = true;
				}
				// 이펙트
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

// 업데이트 함수에서 갱신된 값들로 화면을 출력
void FootBall::Render()
{
	screen->ScreenClear();

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
		// 이펙트 On 상태일 때 출력
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

	screen->ScreenFlipping();
}

// 종료 조건이 충족되면 true를 반환하는 함수
// 결과 화면이 되면 꺼진다.
bool FootBall::Exit()
{
	if( m_currentStage == RESULT )
		return true;

	return false;
}


/* private 함수 ----------------------- */
// 초기 설정
void FootBall::Init()
{
	// 스테이지
	if( m_nStage == -1 )
	{
		m_nStage = STARTSTAGE;
	}
	m_stageInfo = Stage::Instance();
	m_stageInfo->StageSet( m_nStage );

	// 플레이어
	m_player = new Player();

	// 공
	m_ball = new Ball( m_player->GetMoveX(), m_player->GetMoveY() );

	// 골대
	m_goalPost = new GoalPost();

	// 이펙트
	m_effect = new Effect();

	// 게임 기본 설정
	m_bGoal = false;
	m_limitTime = m_stageInfo->m_limitTime;
	m_nBallCount = m_stageInfo->m_nGoalBall;
	m_nGoalCount = 0;
	m_updateOldTime = clock();
}

// 사용 되었던 메모리 정리
void FootBall::Release()
{
	SAFE_DELETE( m_player );
	SAFE_DELETE( m_ball );
	SAFE_DELETE( m_goalPost );
	SAFE_DELETE( m_effect );
}

// 초기 화면 출력
void FootBall::InitScreen()
{
	screen->ScreenPrint( 0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 0, 1, "┃                                          ┃" );
	screen->ScreenPrint( 0, 2, "┃             □━━━□                   ┃" );
	screen->ScreenPrint( 0, 3, "┃                                          ┃" );
	screen->ScreenPrint( 0, 4, "┃                        ///.   슛~~~      ┃" );
	screen->ScreenPrint( 0, 5, "┃                       (^.^)              ┃" );
	screen->ScreenPrint( 0, 6, "┃                      ┗┫ ┣┓           ┃" );
	screen->ScreenPrint( 0, 7, "┃                         ┏┛             ┃" );
	screen->ScreenPrint( 0, 8, "┃                     ⊙  ┛＼             ┃" );
	screen->ScreenPrint( 0, 9, "┃                                          ┃" );
	screen->ScreenPrint( 0, 10, "┃                                          ┃" );
	screen->ScreenPrint( 0, 11, "┃       슛 골인 게임  Go! Go!              ┃" );
	screen->ScreenPrint( 0, 12, "┃                                          ┃" );
	screen->ScreenPrint( 0, 13, "┃                                          ┃" );
	screen->ScreenPrint( 0, 14, "┃       j :왼쪽 l : 오른쪽 k :슛           ┃" );
	screen->ScreenPrint( 0, 15, "┃                                          ┃" );
	screen->ScreenPrint( 0, 16, "┃                                          ┃" );
	screen->ScreenPrint( 0, 17, "┃                                          ┃" );
	screen->ScreenPrint( 0, 18, "┃        ┗●┛  space 키를 눌러주세요     ┃" );
	screen->ScreenPrint( 0, 19, "┃                                          ┃" );
	screen->ScreenPrint( 0, 20, "┃                                          ┃" );
	screen->ScreenPrint( 0, 21, "┃                                          ┃" );
	screen->ScreenPrint( 0, 22, "┗━━━━━━━━━━━━━━━━━━━━━┛" );
}

// 준비 화면 출력
void FootBall::ReadyScreen()
{
	char string[100];

	screen->ScreenPrint( 0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 0, 1, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 2, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 3, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 4, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 5, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 6, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 7, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 8, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 9, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 10, "┃■■■■■                    ■■■■■■┃" );
	sprintf_s( string, "┃■■■■■     %d   스테이지   ■■■■■■┃", m_nStage + 1 );
	screen->ScreenPrint( 0, 11, string );
	screen->ScreenPrint( 0, 12, "┃■■■■■                    ■■■■■■┃" );
	screen->ScreenPrint( 0, 13, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 14, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 15, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 16, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 17, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 18, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 19, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 20, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 21, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 22, "┃■■■■■■■■■■■■■■■■■■■■■┃" );
	screen->ScreenPrint( 0, 23, "┗━━━━━━━━━━━━━━━━━━━━━┛" );
}

// 게임 시작 시 뒤쪽에 그려질 화면
void FootBall::BackScreen()
{
	char string[100];

	screen->ScreenPrint( 0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 0, 1, "┃                                          ┃" );
	screen->ScreenPrint( 0, 2, "┃                                          ┃" );
	screen->ScreenPrint( 0, 3, "┃                                          ┃" );
	sprintf_s( string, "┃                                          ┃스테이지: %d", m_nStage + 1 );
	screen->ScreenPrint( 0, 4, string );
	screen->ScreenPrint( 0, 5, "┃                                          ┃" );
	sprintf_s( string, "┣━━━━━━━━━━━━━━━━━━━━━┫제한 시간: %d", m_stageInfo->m_limitTime / 1000);
	screen->ScreenPrint( 0, 6, string );
	screen->ScreenPrint( 0, 7, "┃                                          ┃" );
	sprintf_s( string, "┃                                          ┃현재 시간: %d", (clock() - m_gameStartTime) / 1000 );
	screen->ScreenPrint( 0, 8, string );
	screen->ScreenPrint( 0, 9, "┃                                          ┃" );
	sprintf_s( string, "┃                                          ┃목표 골인: %d ", m_stageInfo->m_nGoalBall );
	screen->ScreenPrint( 0, 10, string );
	screen->ScreenPrint( 0, 11, "┃                                          ┃" );
	sprintf_s( string, "┃                                          ┃골인 공 개수: %d ", m_nGoalCount );
	screen->ScreenPrint( 0, 12, string );

	screen->ScreenPrint( 0, 13, "┃                                          ┃" );
	sprintf_s( string, "┃                                          ┃" );
	screen->ScreenPrint( 0, 14, string );
	screen->ScreenPrint( 0, 15, "┃                                          ┃" );
	sprintf_s( string, "┃                                          ┃" );
	screen->ScreenPrint( 0, 16, string );
	screen->ScreenPrint( 0, 17, "┃                                          ┃" );
	screen->ScreenPrint( 0, 18, "┃                                          ┃" );
	screen->ScreenPrint( 0, 19, "┃                                          ┃" );
	screen->ScreenPrint( 0, 20, "┃                                          ┃" );
	screen->ScreenPrint( 0, 21, "┃                                          ┃" );
	screen->ScreenPrint( 0, 22, "┃                                          ┃" );
	screen->ScreenPrint( 0, 23, "┗━━━━━━━━━━━━━━━━━━━━━┛" );
}

// 게임 클리어시 화면 출력
void FootBall::SuccessScreen()
{
	screen->ScreenPrint( 0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 0, 1, "┃                                          ┃" );
	screen->ScreenPrint( 0, 2, "┃                                          ┃" );
	screen->ScreenPrint( 0, 3, "┃                                          ┃" );
	screen->ScreenPrint( 0, 4, "┃                                          ┃" );
	screen->ScreenPrint( 0, 5, "┃                                          ┃" );
	screen->ScreenPrint( 0, 6, "┃                ////＼＼                  ┃" );
	screen->ScreenPrint( 0, 7, "┃               q ∧  ∧ p                 ┃" );
	screen->ScreenPrint( 0, 8, "┃               (└──┘)                 ┃" );
	screen->ScreenPrint( 0, 9, "┃             ♬ 미션 성공 ♪              ┃" );
	screen->ScreenPrint( 0, 10, "┃                                          ┃" );
	screen->ScreenPrint( 0, 11, "┃                                          ┃" );
	screen->ScreenPrint( 0, 12, "┃                                          ┃" );
	screen->ScreenPrint( 0, 13, "┃                                          ┃" );
	screen->ScreenPrint( 0, 14, "┃                                          ┃" );
	screen->ScreenPrint( 0, 15, "┃                                          ┃" );
	screen->ScreenPrint( 0, 16, "┃                                          ┃" );
	screen->ScreenPrint( 0, 17, "┃                                          ┃" );
	screen->ScreenPrint( 0, 18, "┃                                          ┃" );
	screen->ScreenPrint( 0, 19, "┃                                          ┃" );
	screen->ScreenPrint( 0, 20, "┃                                          ┃" );
	screen->ScreenPrint( 0, 21, "┃                                          ┃" );
	screen->ScreenPrint( 0, 22, "┃                                          ┃" );
	screen->ScreenPrint( 0, 23, "┗━━━━━━━━━━━━━━━━━━━━━┛" );
}

// 게임 실패 시 화면
void FootBall::FailureScreen()
{
	screen->ScreenPrint( 0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 0, 1, "┃                                          ┃" );
	screen->ScreenPrint( 0, 2, "┃                                          ┃" );
	screen->ScreenPrint( 0, 3, "┃                                          ┃" );
	screen->ScreenPrint( 0, 4, "┃                                          ┃" );
	screen->ScreenPrint( 0, 5, "┃                                          ┃" );
	screen->ScreenPrint( 0, 6, "┃                                          ┃" );
	screen->ScreenPrint( 0, 7, "┃                                          ┃" );
	screen->ScreenPrint( 0, 8, "┃                                          ┃" );
	screen->ScreenPrint( 0, 9, "┃                                          ┃" );
	screen->ScreenPrint( 0, 10, "┃                                          ┃" );
	screen->ScreenPrint( 0, 11, "┃                    미션 실패 !!!!        ┃" );
	screen->ScreenPrint( 0, 12, "┃                                          ┃" );
	screen->ScreenPrint( 0, 13, "┃                                          ┃" );
	screen->ScreenPrint( 0, 14, "┃                 ●┳━┓                 ┃" );
	screen->ScreenPrint( 0, 15, "┃                   ┛  ┗                 ┃" );
	screen->ScreenPrint( 0, 16, "┃                  ■■■■                ┃" );
	screen->ScreenPrint( 0, 17, "┃                                          ┃" );
	screen->ScreenPrint( 0, 18, "┃        다시 하시겠습니까? (y/n)          ┃" );
	screen->ScreenPrint( 0, 19, "┃                                          ┃" );
	screen->ScreenPrint( 0, 20, "┃                                          ┃" );
	screen->ScreenPrint( 0, 21, "┃                                          ┃" );
	screen->ScreenPrint( 0, 22, "┗━━━━━━━━━━━━━━━━━━━━━┛" );
}

// 결과 화면
void FootBall::ResultScreen()
{
	char string[100];
	screen->ScreenPrint( 0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 0, 1, "┃                                          ┃" );
	screen->ScreenPrint( 0, 2, "┃                                          ┃" );
	screen->ScreenPrint( 0, 3, "┃             □━━━□                   ┃" );
	screen->ScreenPrint( 0, 4, "┃                                          ┃" );
	screen->ScreenPrint( 0, 5, "┃                                          ┃" );
	screen->ScreenPrint( 0, 6, "┃                                          ┃" );
	screen->ScreenPrint( 0, 7, "┃                                          ┃" );
	sprintf_s( string, "┃      성공한 스테이지 :  %2d               ┃", m_nStage + 1 );
	screen->ScreenPrint( 0, 8, string );
	screen->ScreenPrint( 0, 9, "┃                                          ┃" );
	screen->ScreenPrint( 0, 10, "┃                                          ┃" );
	screen->ScreenPrint( 0, 11, "┃   ___▒▒▒___                           ┃" );
	screen->ScreenPrint( 0, 12, "┃     (*^  ^*)                             ┃" );
	screen->ScreenPrint( 0, 13, "┃ =====○==○=====                         ┃" );
	screen->ScreenPrint( 0, 14, "┃                                          ┃" );
	screen->ScreenPrint( 0, 15, "┃                                          ┃" );
	screen->ScreenPrint( 0, 16, "┃                                          ┃" );
	screen->ScreenPrint( 0, 17, "┃                                          ┃" );
	screen->ScreenPrint( 0, 18, "┃                      ┗●┛              ┃" );
	screen->ScreenPrint( 0, 19, "┃                                          ┃" );
	screen->ScreenPrint( 0, 20, "┃                                          ┃" );
	screen->ScreenPrint( 0, 21, "┃                                          ┃" );
	screen->ScreenPrint( 0, 22, "┗━━━━━━━━━━━━━━━━━━━━━┛" );
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