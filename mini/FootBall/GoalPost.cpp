#include "../Screen.h"
#include "GoalPost.h"
#include "Stage.h"

// ��� �̵�
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
			m_nDist = m_nDist * -1; // -1 �� ������ �ٲپ� ��.
	}
}

// ��� ���
void GoalPost::GoalPostDraw()
{
	Screen* inst = Screen::Instance();

	inst->ScreenPrint( m_nMoveX, m_nMoveY, "��" );

	for( int i = 0; i < m_nLineSize; ++i )
		inst->ScreenPrint( m_nLineX[i], m_nMoveY, "��" );

	inst->ScreenPrint( m_nLineX[m_nLineSize - 1] + 2, m_nMoveY, "��" );
}

// ��� ���� ������ ��ȯ����
const int* const GoalPost::GetGoalLine() const
{
	return m_nLineX;
}

// ��� ���� ��ȯ
int GoalPost::GetLineLen() const
{
	return m_nLineSize;
}

// ����� y �� ��ȯ
int GoalPost::GetPosY() const
{
	return m_nMoveY;
}

// ��� �ʱ�ȭ
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

// ����� �޸� ����
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