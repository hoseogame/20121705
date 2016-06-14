#include "Block.h"
#include <stdlib.h>

// 입력 받은 키 상수로 지정
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50
#define KEY_SPACE		0x20

// 블럭 생성 return 값으로 블먹 모양 결정
int Block::MakeBlock()
{
	int shape = 0;
	int i = rand() % 100;	// 0~99 랜덤 출력

	if( i <= m_stick_rate )
		return shape;

	shape = (rand() % BLOCK_VOL - 1) + 1;
	return shape;
}

// 입력 받은 키에 따라 블럭 움직임
void Block::Move( int nKey )
{
	clock_t curTime = clock();
	//erase_cur_block( m_shape, m_angle, m_x, m_y );
	switch( nKey )
	{
	case KEY_UP:	// 회전
		Rotation();
		break;
	case KEY_LEFT :
		if( m_x > 1 )
		{
			--m_x;
			if( strike_check( m_shape, m_angle, m_x, m_y ) )
				++m_x;
		}
		break;
	case KEY_RIGHT :
		if( m_x < MAX_SIZE_X )
		{
			++m_x;
			if( strike_check( m_shape, m_angle, m_x, m_y ) )
				--m_x;
		}
		break;
	case KEY_DOWN :
		m_block_state = BlockDown( &m_shape, &m_angle, &m_x, &m_y, &next_block_shape );
		break;
	case KEY_SPACE :
		while( m_block_state == 0 )
			m_block_state = BlockDown( &m_shape, &m_angle, &m_x, &m_y, &next_block_shape );
		break;
	}
	// 키입력 없어도 조금 씩 아래로 내려감
	if( curTime - m_oldTime > m_moveTime )
	{
		//erase_cur_block( m_shape, m_angle, m_x, m_y );
		m_block_state = BlockDown( &m_shape, &m_angle, &m_x, &m_y, &next_block_shape );
		m_oldTime = curTime;
	}
}

// 블럭을 그려줌
void Block::Draw()
{
	show_total_block();
	show_next_block( next_block_shape );
	show_cur_block( m_shape, m_angle, m_x, m_y );
}

void Block::SetTotalBlock( int y, int x, char data )
{
	m_total_block[y][x] = data;
}

void Block::NextBlockInit()
{
	m_shape = next_block_shape;
	next_block_shape = MakeBlock();

	block_start( &m_angle, &m_x, &m_y );	//angle,x,y는 포인터임
	m_block_state = 0;
}

// 블럭 화면 아래 부딪히는지 검사
bool Block::strike_check( int shape, int angle, int x, int y )
{
	int i, j;
	int block_dat = 0;

	for( i = 0; i < 4; i++ )
	{
		for( j = 0; j < 4; j++ )
		{
			if( ((x + j) == 0) || ((x + j) == 13) )
				block_dat = 1;
			else
			{
				if( y + i >= 0 )
					block_dat = m_total_block[y + i][x + j];
			}


			if( (block_dat == 1) && (m_block[shape][angle][i][j] == 1) )	//좌측벽의 좌표를 빼기위함
			{
				return true;
			}
		}
	}
	return false;
}

// 블럭이 한칸씩 내려감
int Block::BlockDown( int* shape, int* angle, int* x, int* y, int* next_shape )
{
	(*y)++;	//블럭을 한칸 아래로 내림
	if( strike_check( *shape, *angle, *x, *y ) == 1 )
	{
		if( *y<0 )	//게임오버
		{

			return 1;
		}
		(*y)--;
		return 2;
	}
	return 0;
}

// 회전
void Block::Rotation()
{
	int angle = (m_angle + 1) % 4;
	if( !strike_check( m_shape, angle, m_x, m_y ) )
		m_angle = angle;
}

// 시작 좌표 잡아줌
void Block::block_start( int* angle, int* x, int* y )
{
	*x = 5;
	*y = -3;
	*angle = 0;
}

// 진행중인 블럭을 화면에 표시한다.
void Block::show_cur_block( int shape, int angle, int x, int y )
{// 모양 별 색 지정
	switch( shape )
	{
	case STICK :
		screen->SetColor( Screen::RED );
		break;
	case SQUARE :
		screen->SetColor( Screen::BLUE );
		break;
	case T_SHAPE :
		screen->SetColor( Screen::SKY_BLUE );
		break;
	case J_SHAPE :
		screen->SetColor( Screen::WHITE );
		break;
	case L_SHAPE :
		screen->SetColor( Screen::YELLOW );
		break;
	case Z_SHAPE :
		screen->SetColor( Screen::VIOLET );
		break;
	case S_SHAPE :
		screen->SetColor( Screen::GREEN );
		break;
	}
	
	// 출력
	for( int i = 0; i<4; i++ )
	{
		for( int j = 0; j<4; j++ )
		{
			if( (j + y) <0 )
				continue;

			if( m_block[shape][angle][j][i] == 1 )
			{
				screen->ScreenPrint( (i + x) * 2 + ab_x, j + y + ab_y, "■" );
			}
		}
	}
	screen->SetColor( Screen::BLACK );
	screen->ScreenPrint( 77, 23, "" );
}

// 블럭 진행의 잔상을 지우기 위한 함수
void Block::erase_cur_block( int shape, int angle, int x, int y )
{
	for( int i = 0; i<4; i++ )
	{
		for( int j = 0; j<4; j++ )
		{
			if( (j + y) <0 )
				continue;

			if( m_block[shape][angle][j][i] == 1 )
			{
				screen->ScreenPrint( (i + x) * 2 + ab_x, j + y + ab_y, "  " );

			}
		}
	}
}

// 쌓여져있는 블럭을 화면에 표시한다.
void Block::show_total_block()
{
	screen->SetColor( Screen::DARK_GRAY );
	for( int i = 0; i<MAX_SIZE_Y; i++ )
	{
		for( int j = 0; j<MAX_SIZE_X; j++ )
		{
			if( j == 0 || j == 13 || i == 20 )		//레벨에 따라 외벽 색이 변함
			{
				screen->SetColor(Screen::DARK_GREEN);

			}
			else {
				screen->SetColor( Screen::DARK_GRAY );
			}
			if( m_total_block[i][j] == 1 )
			{
				screen->ScreenPrint( (j * 2) + ab_x, i + ab_y, "■" );
			}
			else {
				screen->ScreenPrint( (j * 2) + ab_x, i + ab_y, "  " );
			}

		}
	}
	screen->SetColor( Screen::BLACK );
	screen->ScreenPrint( 77, 23, "" );
}

// 다음 블럭 뭐나올지 미리 출력
void Block::show_next_block( int shape )
{
	screen->SetColor(Screen::YELLOW);
	for( int y = 1; y < BLOCK_VOL; y++ )
	{
		for( int x = 0; x<6; x++ )
		{
			if( y == 1 || y == 6 || x == 0 || x == 5 )
			{
				screen->ScreenPrint( 33 + (2 * x), y, "■" );
			}
			else {
				screen->ScreenPrint( 33 + (2 * x), y, "  " );
			}

		}
	}
	show_cur_block( shape, 0, 15, 1 );
}

// 블럭 초기 설정
void Block::Init()
{
	int i, j;
	// 랜덤 seed 값 넣기
	srand( (unsigned)time( NULL ) );

	// 화면 배열 초기화
	for( i = 0; i < MAX_SIZE_Y - 1; ++i )
	{
		for( j = 0; j < MAX_SIZE_X; ++j )
		{
			if( (j == 0) || (j == MAX_SIZE_X - 1) )
			{
				m_total_block[i][j] = 1;
			}
			else {
				m_total_block[i][j] = 0;
			}
		}
	}

	// 화면 맨 밑줄을 1로 채운다.
	for( j = 0; j < MAX_SIZE_X; ++j )
		m_total_block[MAX_SIZE_Y - 1][j] = 1;

	m_shape = MakeBlock();
	block_start( &m_angle, &m_x, &m_y );
	m_block_state = 0;
	m_oldTime = clock();
	m_moveTime = 1000;
	screen = Screen::Instance();
}