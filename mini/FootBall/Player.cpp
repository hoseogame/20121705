#include <string>
#include "Player.h"
#include "../Screen.h"

// 입력 받은 키에 따라 좌 - 우로 이동
void Player::PlayerUpdate( int nKey )
{
	// 전체 길이 - ( 중심 좌표 + 1 )은 남은 길이
	int nRemain = PLAYER_LEN - m_nCenterX + 1;

	switch( nKey )
	{
	case 'j' :
		if( m_nMoveX > 2 )	// 왼쪽 충돌 경계 좌표 체크
		{
			--m_nMoveX;
			// Note: 2컬럼씩 이동하기 위한 부분 ( 팔이 걸친 경우 )
			if( m_nMoveX - m_nCenterX < 2 || m_nMoveX + nRemain > 43 )
				--m_nMoveX;

			DrawPositionSet();
		}
		break;
	case 'l' :
		if( m_nMoveX + 1 < 43 )	// 오른쪽 충돌 경계 좌표 체크
		{
			++m_nMoveX;
			// Note: 2컬럼씩 이동하기 위한 부분 ( 팔이 걸친 경우 )
			if( m_nMoveX + nRemain > 43 || ( m_nMoveX - m_nCenterX < 2) )
				m_nMoveX++;

			DrawPositionSet();
		}
		break;
	}
}

// 캐릭터를 화면에 출력
void Player::PlayerDraw()
{
	char string[100] = { 0, };

	Screen* inst = Screen::Instance();
	if( m_nX < 2 )  //  왼쪽 클리핑 처리
		inst->ScreenPrint( 2, m_nY, &m_pStrPlayer[(m_nX - 2)*-1] );	 // 좌표를 배열 인덱스 
	else if( m_nMoveX + (PLAYER_LEN - m_nCenterX + 1) > 43 ) // 오른쪽 클리핑 처리
	{
		strncat_s( string, m_pStrPlayer, PLAYER_LEN - ((m_nMoveX + m_nCenterX + 1) - 43) );
		inst->ScreenPrint( m_nX, m_nY, string );
	}
	else { // 1 컬럼씩 이동
		inst->ScreenPrint( m_nX, m_nY, m_pStrPlayer );
	}

}

int Player::GetMoveX()
{
	return m_nMoveX;
}

int Player::GetMoveY()
{
	return m_nMoveY;
}

// 캐릭터 초기화
void Player::Init()
{
	m_pStrPlayer = new char[PLAYER_LEN];
	strcpy_s( m_pStrPlayer, PLAYER_LEN, "┗━●━┛" ); 
	m_nCenterX = ( PLAYER_LEN / 2 ) - 1;
	m_nCenterY = 0;
	m_nMoveX = 20;
	m_nMoveY = 22;
	DrawPositionSet();
}

// 객체 사용 종료시 메모리 정리
void Player::Release()
{
	if( m_pStrPlayer != nullptr )
		delete[] m_pStrPlayer;

	m_pStrPlayer = nullptr;
}

// 그림 출력할 좌표 세팅
void Player::DrawPositionSet()
{
	m_nX = m_nMoveX - m_nCenterX;
	m_nY = m_nMoveY - m_nCenterY;
}

Player::Player()
{
	Init();
}

Player::~Player()
{
	Release();
}