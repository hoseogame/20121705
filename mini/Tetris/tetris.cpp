#include "tetris.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

// 블럭 상태 및 스테이지 업뎃
void Tetris::Update()
{
	int key = KeyInput();
	switch( stage )
	{
	case INIT :
		press_any_key( key );
		break;
	case READY :
		level_select( key );
		break;
	case RUNNING :
		m_block->Move( key );

		// 블럭이 바닥이나 다른 블럭에 닿았다면 합침
		if( m_block->GetBlockState() == 2 )
			merge_block( m_block->GetBlockX(), m_block->GetBlockY() );

		// 꽉 찬 라인이 있는지 확인
		m_full_line_num = check_full_line();
		if( m_full_line_num != 0 )
			full_line_Set();

		if( stage_data[m_level].clear_line == m_line )
		{
			++m_level;
			if( m_level >= MAX_STAGE )
			{
				stage = SUCCESS;
			}
			m_line = 0;
		}

		// 게임 오버~
		if( GameOver() )
			stage = FAILED;
		break;
	case SUCCESS:
	case FAILED:
		if( key == 'y' || key == 'Y' )
		{
			stage = READY;
			Init();
		}
		if( key == 'n' || key == 'N' )
			stage = RESULT;
		break;
	case RESULT:
			m_bIsGameOver = true;
		break;
	}
}

// 그래픽 출력-
void Tetris::Render()
{
	switch( stage )
	{
	case INIT: 
		show_logo();
		break;
	case READY:
		input_data();
		break;
	case RUNNING: 
		m_block->Draw();
		show_gamestat();
		if( m_full_line_num != 0 )
			full_line_erase();
		break;
	case SUCCESS:
		m_block->Draw();
		show_gamestat();
		show_cleargame();
		break;
	case FAILED:
		m_block->Draw();
		show_gamestat();
		show_gameover();
		break;
	case RESULT :
		break;
	}
}

bool Tetris::Exit()
{
	if( m_bIsGameOver )
	{
		stage = INIT;
		Init();
		return true;
	}
	return false;
}

// 게임 오버시 출력
void Tetris::show_gameover()
{
	screen->SetColor( Screen::RED );
	screen->ScreenPrint( 15, 8, "┏━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 15, 9, "┃**************************┃" );
	screen->ScreenPrint( 15, 10, "┃*        GAME OVER       *┃" );
	screen->ScreenPrint( 15, 11, "┃* Y : replay    N : exit *┃" );
	screen->ScreenPrint( 15, 12, "┃**************************┃" );
	screen->ScreenPrint( 15, 13, "┗━━━━━━━━━━━━━┛" );
}

// 게임 클리어시 출력
void Tetris::show_cleargame()
{
	screen->SetColor( Screen::GREEN );
	screen->ScreenPrint( 15, 8, "┏━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 15, 9, "┃**************************┃" );
	screen->ScreenPrint( 15, 10, "┃*       GAME CLEAR       *┃" );
	screen->ScreenPrint( 15, 11, "┃* Y : replay    N : exit *┃" );
	screen->ScreenPrint( 15, 12, "┃**************************┃" );
	screen->ScreenPrint( 15, 13, "┗━━━━━━━━━━━━━┛" );
}


// 게임 정보 스테이지, 점수 등 출력
void Tetris::show_gamestat()
{
	char string[50];
	screen->SetColor( Screen::GRAY );

	screen->ScreenPrint( 35, 7, "STAGE" );
	sprintf_s( string, "%d", m_level + 1 );
	screen->ScreenPrint( 41, 7, string );

	screen->ScreenPrint( 35, 9, "SCORE" );
	sprintf_s( string, "%d", m_score );
	screen->ScreenPrint( 35, 10, string );

	screen->ScreenPrint( 35, 12, "LINES" );
	sprintf_s( string, "%d", stage_data[m_level].clear_line - m_line );
	screen->ScreenPrint( 35, 13, string );
}

// 시작 할 때 로고 화면 출력
void Tetris::show_logo()
{
	clock_t curTime = clock();

	screen->SetColor( Screen::SKY_BLUE );
	screen->ScreenPrint( 13, 3, "┏━━━━━━━━━━━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 13, 4, "┃◆◆◆  ◆◆◆  ◆◆◆   ◆◆     ◆   ◆  ◆ ┃" );
	screen->ScreenPrint( 13, 5, "┃  ◆    ◆        ◆     ◆ ◆    ◆    ◆◆  ┃" );
	screen->ScreenPrint( 13, 6, "┃  ◆    ◆◆◆    ◆     ◆◆     ◆     ◆   ┃" );
	screen->ScreenPrint( 13, 7, "┃  ◆    ◆        ◆     ◆ ◆    ◆    ◆◆  ┃" );
	screen->ScreenPrint( 13, 8, "┃  ◆    ◆◆◆    ◆     ◆  ◆   ◆   ◆  ◆ ┃" );
	screen->ScreenPrint( 13, 9, "┗━━━━━━━━━━━━━━━━━━━━━━━┛" );

	screen->ScreenPrint( 28, 20, "Please Press Any Key~!" );
	if( curTime - m_oldTime > m_printTime )
	{
		for( int i = 0; i < 4; ++i )
		{
			angle[i] = rand() % 4;
			shape[i] = rand() % 7;
		}
		m_oldTime = curTime;
	}

	m_block->show_cur_block( shape[0], angle[0], 6, 14 );
	m_block->show_cur_block( shape[1], angle[1], 12, 14 );
	m_block->show_cur_block( shape[2], angle[2], 19, 14 );
	m_block->show_cur_block( shape[3], angle[3], 24, 14 );
		
}

// 키 입력 받으면 READY 로 넘어감
void Tetris::press_any_key( int nKey )
{
	if( nKey != 0 )
		stage = READY;
}

// 레벨 선택
void Tetris::level_select( int nKey )
{
	if( nKey != 0 && nKey != '0' && nKey <= '8')
	{
		char clevel = nKey;

		int level = atoi( &clevel );

		m_level = level - 1;
		stage = RUNNING;
		LevelSet();
	}
}

// 블럭 합치는 함수 
void Tetris::merge_block( int x, int y )
{
	int i, j;
	for( i = 0; i<4; i++ )
	{
		for( j = 0; j<4; j++ )
		{
			m_block->SetTotalBlock( y + i, x + j, m_block->GetTotalBlock( y + i, x + j ) | m_block->GetBlock( i, j ) );
				//m_total_block[y + i][x + j] |= m_block[shape][angle][i][j];
		}
	}
	m_block->NextBlockInit();
}

// 한줄 채워진 라인을 반환해줌
int Tetris::check_full_line()
{
	int i, j;
	for( i = 0; i<MAX_SIZE_Y - 1; i++ )
	{
		for( j = 1; j<MAX_SIZE_X - 1; j++ )
		{/*m_total_block[i][j]*/
			if( m_block->GetTotalBlock( i, j ) == 0 )
				break;
		}
		if( j == MAX_SIZE_X - 1 )	//한줄이 다 채워졌음
		{
			return i;
		}
	}
	return 0;
}

// 채워진 줄을 초기화 시킴
void Tetris::full_line_Set()
{
	++m_line;
	for( int k = m_full_line_num; k>0; k-- )
	{
		for( int j = 1; j < MAX_SIZE_X - 1; j++ )
			m_block->SetTotalBlock( k, j, m_block->GetTotalBlock( k - 1, j ) );
			//m_total_block[k][j] = m_total_block[k - 1][j];
	}
	for( int j = 1; j < MAX_SIZE_X - 1; j++ )
		m_block->SetTotalBlock( 0, j, 0 );
		//m_total_block[0][j] = 0;
	m_score += 100 + (m_level * 10) + (rand() % 10);
}

// 채워진 줄 지워줌
void Tetris::full_line_erase()
{
	int j;
	//show_total_block();
	screen->SetColor( Screen::BLUE );
	for( j = 1; j<MAX_SIZE_X - 1; j++ )
	{
		screen->ScreenPrint( (j * 2 + AB_X), m_full_line_num + AB_Y, "  " );
	}
	m_full_line_num = 0;
}

// 시작 레벨 설정 화면
void Tetris::input_data()
{
	screen->SetColor( Screen::GRAY );
	screen->ScreenPrint( 10, 7, "┏━━━━<GAME KEY>━━━━━┓" );
	screen->ScreenPrint( 10, 8, "┃ UP   : Rotate Block        ┃" );
	screen->ScreenPrint( 10, 9, "┃ DOWN : Move One-Step Down  ┃" );
	screen->ScreenPrint( 10, 10, "┃ SPACE: Move Bottom Down    ┃" );
	screen->ScreenPrint( 10, 11, "┃ LEFT : Move Left           ┃" );
	screen->ScreenPrint( 10, 12, "┃ RIGHT: Move Right          ┃" );
	screen->ScreenPrint( 10, 13, "┗━━━━━━━━━━━━━━┛" );

	screen->ScreenPrint( 10, 3, "Select Start level[1-8]:       \b\b\b\b\b\b\b" );
}

bool Tetris::GameOver()
{
	if( m_block->GetBlockState() == 1 )
	{
		return true;
	}
	return false;
}

// 클리어나 레벨 지정시 속도와 막대 모양이 나올 확률 조정
void Tetris::LevelSet()
{
	m_block->SetMoveTime( stage_data[m_level].speed );
	m_block->SetStickRate( stage_data[m_level].stick_rate );
}

// 게임 초기 설정
void Tetris::Init()
{
	m_block = new Block();

	stage = INIT;
	m_printTime = 1000;

	m_level = 0;
	m_line = 0;
	m_score = 0;
	m_full_line_num = 0;
	m_bIsGameOver = false;

	// 스테이지 초기화 ------------------
	stage_data[0].speed = 1000;
	stage_data[0].stick_rate = 20;
	stage_data[0].clear_line = 20;
	stage_data[1].speed = 1000;
	stage_data[1].stick_rate = 18;
	stage_data[1].clear_line = 20;
	stage_data[2].speed = 800;
	stage_data[2].stick_rate = 18;
	stage_data[2].clear_line = 20;
	stage_data[3].speed = 800;
	stage_data[3].stick_rate = 17;
	stage_data[3].clear_line = 20;
	stage_data[4].speed = 700;
	stage_data[4].stick_rate = 16;
	stage_data[4].clear_line = 20;
	stage_data[5].speed = 700;
	stage_data[5].stick_rate = 14;
	stage_data[5].clear_line = 20;
	stage_data[6].speed = 400;
	stage_data[6].stick_rate = 14;
	stage_data[6].clear_line = 20;
	stage_data[7].speed = 400;
	stage_data[7].stick_rate = 13;
	stage_data[7].clear_line = 20;
	stage_data[8].speed = 300;
	stage_data[8].stick_rate = 12;
	stage_data[8].clear_line = 20;
	stage_data[9].speed = 300;
	stage_data[9].stick_rate = 11;
	stage_data[9].clear_line = 100;
	// ------------------------------------


	// 초기 화면에 쓰일 블럭 만들어둠
	for( int i = 0; i < 4; ++i )
	{
		angle[i] = rand() % 4;
		shape[i] = rand() % 7;
	}
	LevelSet();
}

void Tetris::Release()
{
	if( m_block != nullptr )
		delete m_block;

	m_block = nullptr;
}