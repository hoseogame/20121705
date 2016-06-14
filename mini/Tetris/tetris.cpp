#include "tetris.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

// �� ���� �� �������� ����
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

		// ���� �ٴ��̳� �ٸ� ���� ��Ҵٸ� ��ħ
		if( m_block->GetBlockState() == 2 )
			merge_block( m_block->GetBlockX(), m_block->GetBlockY() );

		// �� �� ������ �ִ��� Ȯ��
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

		// ���� ����~
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

// �׷��� ���-
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

// ���� ������ ���
void Tetris::show_gameover()
{
	screen->SetColor( Screen::RED );
	screen->ScreenPrint( 15, 8, "������������������������������" );
	screen->ScreenPrint( 15, 9, "��**************************��" );
	screen->ScreenPrint( 15, 10, "��*        GAME OVER       *��" );
	screen->ScreenPrint( 15, 11, "��* Y : replay    N : exit *��" );
	screen->ScreenPrint( 15, 12, "��**************************��" );
	screen->ScreenPrint( 15, 13, "������������������������������" );
}

// ���� Ŭ����� ���
void Tetris::show_cleargame()
{
	screen->SetColor( Screen::GREEN );
	screen->ScreenPrint( 15, 8, "������������������������������" );
	screen->ScreenPrint( 15, 9, "��**************************��" );
	screen->ScreenPrint( 15, 10, "��*       GAME CLEAR       *��" );
	screen->ScreenPrint( 15, 11, "��* Y : replay    N : exit *��" );
	screen->ScreenPrint( 15, 12, "��**************************��" );
	screen->ScreenPrint( 15, 13, "������������������������������" );
}


// ���� ���� ��������, ���� �� ���
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

// ���� �� �� �ΰ� ȭ�� ���
void Tetris::show_logo()
{
	clock_t curTime = clock();

	screen->SetColor( Screen::SKY_BLUE );
	screen->ScreenPrint( 13, 3, "��������������������������������������������������" );
	screen->ScreenPrint( 13, 4, "���ߡߡ�  �ߡߡ�  �ߡߡ�   �ߡ�     ��   ��  �� ��" );
	screen->ScreenPrint( 13, 5, "��  ��    ��        ��     �� ��    ��    �ߡ�  ��" );
	screen->ScreenPrint( 13, 6, "��  ��    �ߡߡ�    ��     �ߡ�     ��     ��   ��" );
	screen->ScreenPrint( 13, 7, "��  ��    ��        ��     �� ��    ��    �ߡ�  ��" );
	screen->ScreenPrint( 13, 8, "��  ��    �ߡߡ�    ��     ��  ��   ��   ��  �� ��" );
	screen->ScreenPrint( 13, 9, "��������������������������������������������������" );

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

// Ű �Է� ������ READY �� �Ѿ
void Tetris::press_any_key( int nKey )
{
	if( nKey != 0 )
		stage = READY;
}

// ���� ����
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

// �� ��ġ�� �Լ� 
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

// ���� ä���� ������ ��ȯ����
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
		if( j == MAX_SIZE_X - 1 )	//������ �� ä������
		{
			return i;
		}
	}
	return 0;
}

// ä���� ���� �ʱ�ȭ ��Ŵ
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

// ä���� �� ������
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

// ���� ���� ���� ȭ��
void Tetris::input_data()
{
	screen->SetColor( Screen::GRAY );
	screen->ScreenPrint( 10, 7, "����������<GAME KEY>������������" );
	screen->ScreenPrint( 10, 8, "�� UP   : Rotate Block        ��" );
	screen->ScreenPrint( 10, 9, "�� DOWN : Move One-Step Down  ��" );
	screen->ScreenPrint( 10, 10, "�� SPACE: Move Bottom Down    ��" );
	screen->ScreenPrint( 10, 11, "�� LEFT : Move Left           ��" );
	screen->ScreenPrint( 10, 12, "�� RIGHT: Move Right          ��" );
	screen->ScreenPrint( 10, 13, "��������������������������������" );

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

// Ŭ��� ���� ������ �ӵ��� ���� ����� ���� Ȯ�� ����
void Tetris::LevelSet()
{
	m_block->SetMoveTime( stage_data[m_level].speed );
	m_block->SetStickRate( stage_data[m_level].stick_rate );
}

// ���� �ʱ� ����
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

	// �������� �ʱ�ȭ ------------------
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


	// �ʱ� ȭ�鿡 ���� �� ������
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