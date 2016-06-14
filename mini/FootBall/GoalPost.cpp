#include "../Screen.h"
#include "GoalPost.h"
#include "Stage.h"

// 골대 이동
void GoalPost::GoalPostUpdate()
{
	m_curTime = clock();

	if( m_curTime - m_oldTime > m_moveTime )
	{
		m_oldTime = m_curTime;
		if( m_nMoveX + m_nDist >= 2 && ((m_nLineX[m_nLineSize - 1] + 3) + m_nDist) <= 43 )
		{
			m_nMoveX += m_nDist;
			for( int i = 0; i < m_nLineSize; ++i )
			{
				m_nLineX[i] = m_nMoveX + 2 * (i + 1);
			}
		}
		else
			m_nDist = m_nDist * -1; // -1 이 방향을 바꾸어 줌.
	}
}

// 골대 출력
void GoalPost::GoalPostDraw()
{
	Screen* inst = Screen::Instance();

	inst->ScreenPrint( m_nMoveX, m_nMoveY, "□" );

	for( int i = 0; i < m_nLineSize; ++i )
		inst->ScreenPrint( m_nLineX[i], m_nMoveY, "━" );

	inst->ScreenPrint( m_nLineX[m_nLineSize - 1] + 2, m_nMoveY, "□" );
}

// 골대 라인 정보를 반환해줌
const int* const GoalPost::GetGoalLine() const
{
	return m_nLineX;
}

// 골대 길이 반환
int GoalPost::GetLineLen() const
{
	return m_nLineSize;
}

// 골대의 y 값 반환
int GoalPost::GetPosY() const
{
	return m_nMoveY;
}

// 골대 초기화
void GoalPost::Init()
{
	Stage* stage = Stage::Instance();

	m_nMoveX = stage->m_nGoalPostX;
	m_nMoveY = stage->m_nGoalPostY;		
	m_nLength = stage->m_nGoalPostLength;	
	m_nDist = stage->m_nDist;
	m_moveTime = stage->m_moveTime;			
	m_oldTime = clock();			

	int nLength = m_nLength * 2 + 1;
	m_nLineX = new int[nLength];

	for( int i = 0; i < nLength; ++i )
	{
		m_nLineX[i] = m_nMoveX + 2 * (i + 1);
	}
	m_nLineSize = m_nLength * 2 + 1;
}

// 사용한 메모리 정리
void GoalPost::Release()
{
	if( m_nLineX != nullptr )
		delete[] m_nLineX;

	m_nLineX = nullptr;
}

GoalPost::GoalPost()
{
	Init();
}

GoalPost::~GoalPost()
{
	Release();
}