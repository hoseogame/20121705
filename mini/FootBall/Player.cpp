#include <string>
#include "Player.h"
#include "../Screen.h"

// �Է� ���� Ű�� ���� �� - ��� �̵�
void Player::PlayerUpdate( int nKey )
{
	// ��ü ���� - ( �߽� ��ǥ + 1 )�� ���� ����
	int nRemain = PLAYER_LEN - m_nCenterX + 1;

	switch( nKey )
	{
	case 'j' :
		if( m_nMoveX > 2 )	// ���� �浹 ��� ��ǥ üũ
		{
			--m_nMoveX;
			// Note: 2�÷��� �̵��ϱ� ���� �κ� ( ���� ��ģ ��� )
			if( m_nMoveX - m_nCenterX < 2 || m_nMoveX + nRemain > 43 )
				--m_nMoveX;

			DrawPositionSet();
		}
		break;
	case 'l' :
		if( m_nMoveX + 1 < 43 )	// ������ �浹 ��� ��ǥ üũ
		{
			++m_nMoveX;
			// Note: 2�÷��� �̵��ϱ� ���� �κ� ( ���� ��ģ ��� )
			if( m_nMoveX + nRemain > 43 || ( m_nMoveX - m_nCenterX < 2) )
				m_nMoveX++;

			DrawPositionSet();
		}
		break;
	}
}

// ĳ���͸� ȭ�鿡 ���
void Player::PlayerDraw()
{
	char string[100] = { 0, };

	Screen* inst = Screen::Instance();
	if( m_nX < 2 )  //  ���� Ŭ���� ó��
		inst->ScreenPrint( 2, m_nY, &m_pStrPlayer[(m_nX - 2)*-1] );	 // ��ǥ�� �迭 �ε��� 
	else if( m_nMoveX + (PLAYER_LEN - m_nCenterX + 1) > 43 ) // ������ Ŭ���� ó��
	{
		strncat_s( string, m_pStrPlayer, PLAYER_LEN - ((m_nMoveX + m_nCenterX + 1) - 43) );
		inst->ScreenPrint( m_nX, m_nY, string );
	}
	else { // 1 �÷��� �̵�
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

// ĳ���� �ʱ�ȭ
void Player::Init()
{
	m_pStrPlayer = new char[PLAYER_LEN];
	strcpy_s( m_pStrPlayer, PLAYER_LEN, "�����ܦ���" ); 
	m_nCenterX = ( PLAYER_LEN / 2 ) - 1;
	m_nCenterY = 0;
	m_nMoveX = 20;
	m_nMoveY = 22;
	DrawPositionSet();
}

// ��ü ��� ����� �޸� ����
void Player::Release()
{
	if( m_pStrPlayer != nullptr )
		delete[] m_pStrPlayer;

	m_pStrPlayer = nullptr;
}

// �׸� ����� ��ǥ ����
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