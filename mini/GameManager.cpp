#include <conio.h>		// _kbhit 함수 사용
#include "GameManager.h"
#include "FootBall/FootBall.h"
#include "Tank\TankGame.h"
#include "Tetris\tetris.h"

#define EXT_KEY			0xffffffe0	//확장키 인식값 

// 입력 받은 키 상수로 지정
#define KEY_UP			0x48
#define KEY_DOWN		0x50
#define KEY_ENTER		0x0D

// 입력 받은 키 반환
int GameManager::KeyInput()
{
	int nKey = 0;

	if( _kbhit() )
	{
		nKey = _getch();
		if( nKey == EXT_KEY )	// 확장키 체크
		{
			nKey = _getch();
		}
	}

	return nKey;
}

void GameManager::Update()
{
	if( m_isPlay )
	{
		if( m_game[m_select]->Exit() )
			m_isPlay = false;
		else
			m_game[m_select]->Update();
	}
	else
	{
		int key = KeyInput();

		switch( key )
		{
		case KEY_UP:
			if( m_select > 0 )
				--m_select;
			break;
		case KEY_DOWN:
			if( m_select < 3 )
				++m_select;
			break;
		case KEY_ENTER:
			SelectGame();
			break;
		}

	}
}

void GameManager::Render()
{
	screen->ScreenClear();

	if( m_isPlay )
	{
		m_game[m_select]->Render();
	}
	else
	{
		SelectScreenDraw();
		SelectBoxDraw();
	}

	screen->ScreenFlipping();
}

bool GameManager::Exit()
{
	return m_exit;
}

void GameManager::Init()
{
}

void GameManager::Release()
{
	for( int i = 0; i < 3; ++i )
	{
		delete m_game[i];
		m_game[i] = nullptr;
	}
	delete *m_game;

	*m_game = nullptr;
}

void GameManager::SelectGame()
{
	switch( m_select )
	{
	case 0 :
	case 1 :
	case 2 :
		m_isPlay = true;
		break;
	case 3 :
		m_exit = true;
		break;
	}
}

void GameManager::SelectScreenDraw()
{
	screen->SetColor( Screen::GRAY );
	screen->ScreenPrint( 0, 0, "┏━━━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 0, 1, "┃                              ┃" );
	screen->ScreenPrint( 0, 2, "┃        1.TankGame            ┃  ↑↓ 로 게임 고르기" );
	screen->ScreenPrint( 0, 3, "┃                              ┃" );
	screen->ScreenPrint( 0, 4, "┃        2.Tetris              ┃  Enter 로 겜 시작" );
	screen->ScreenPrint( 0, 5, "┃                              ┃" );
	screen->ScreenPrint( 0, 6, "┃        3.FootBall            ┃" );
	screen->ScreenPrint( 0, 7, "┃                              ┃" );
	screen->ScreenPrint( 0, 8, "┃        4.Exit                ┃" );
	screen->ScreenPrint( 0, 9, "┃                              ┃" );
	screen->ScreenPrint( 0, 10, "┗━━━━━━━━━━━━━━━┛" );
}

void GameManager::SelectBoxDraw()
{
	screen->ScreenPrint( 8, 1 + m_select*2, "┏━━━━━━┓" );
	screen->ScreenPrint( 8, 2 + m_select*2, "┃" );	screen->ScreenPrint( 22, 2 + m_select*2, "┃" );
	screen->ScreenPrint( 8, 3 + m_select*2, "┗━━━━━━┛" );
}

void GameManager::ChangeGame()
{
}

GameManager::GameManager() : m_select( 0 ), m_exit( false ), m_isPlay( false )
{
	screen = Screen::Instance();
	m_game[0] = new TankGame();
	m_game[1] = new Tetris();
	m_game[2] = new FootBall();
}

GameManager::~GameManager()
{
	Release();
}