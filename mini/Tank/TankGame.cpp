#include "TankGame.h"
#include "TankStage.h"
#include "PlayerTank.h"
#include "Enemy.h"
#include <cstdio>

// static ������ �ʱ�ȭ�� ���� ������ ������ �޸� �Ҵ��� �̷����� �ʾ�
// �ʱ�ȭ ���� ȣ�� �� Ȯ���� �� ���ٴ� ��ũ������ ���.
int TankGame::nMap[MAP_ROW][MAP_COL] = { 0, };	

// ����
void TankGame::Update()
{
	clock_t curTime = clock();
	int key = KeyInput();
	switch( m_currentstage )
	{
	case INIT :
		if( key == ' ' )
		{
			m_currentstage = READY;
			m_updateOldTime = clock();
		}
		break;
	case READY :
		if( curTime - m_updateOldTime > 2000 )
		{
			m_currentstage = RUNNING;
			m_gameStartTime = curTime;
		}
		break;
	case RUNNING :
		// ĳ���� ������Ʈ
			m_player->Move( key );

			// �� ����
			for( int i = stage->nEnemyIndex; i < stage->nEnemyCount; ++i )
			{
				m_enemy[i].EnemySpawn( m_gameStartTime );
			}

			// �� ������Ʈ
			for( int i = 0; i < stage->nEnemyIndex; ++i )
			{
				m_enemy[i].Move();
			}

		// �Ѿ� �̵�, �浹 üũ
			for( int i = 0; i < BULLET; ++i )
			{
				m_player->bullet[i].Move();
				m_player->bullet[i].IsCollision();
				for( int j = 0; j < stage->nEnemyIndex; ++j )
				{
					// �i�µ� ��������
					if( m_player->bullet[i].IsCollision( &m_enemy[j] ) )
					{
						// ����ְ� ������
						if( m_enemy[j].IsDead() )
						{
							++(stage->nDeadEnemy);	// ���� ī��Ʈ
							stage->SetGrade( 10 );	// ���� �� ! ��!
						}
					}
					m_enemy[j].bullet[i].Move();
					m_enemy[j].bullet[i].IsCollision();
					m_enemy[j].bullet[i].IsCollision(m_player);
				}
			}

		// �������� ���� üũ
			if( stage->nDeadEnemy == stage->nEnemyCount
				|| m_player->IsDead() || stage->nBossLife == 0)
				m_currentstage = STOP;
		break;
	case STOP :
		GameClearCheck();
		break;
	case SUCCESS :
		stage->StageReset( stage->GetStage() + 1 );
		ResetGame();
		break;
	case FAILED :
		if( key == 'Y' || key == 'y' )
		{
			stage->StageReset( stage->GetStage() );
			stage->SetGrade( 0 );
			ResetGame();
		}
		else if( key == 'N' || key == 'n' )
		{
			m_currentstage = RESULT;
		}
		break;
	case RESULT :
		if( key != 0 )
			stage->StageReset( -1 );
		break;
	}
}

// ����
void TankGame::Render()
{
	switch( m_currentstage )
	{
	case INIT :
		if( stage->GetStage() == 0 )
			InitScreen();
		break;

	case READY : 
		ReadyScreen();
		break;

	case RUNNING :
		DrawMap();
		StateScreen();
		m_player->Draw();
		for( int i = 0; i < stage->nEnemyIndex; ++i )
			m_enemy[i].Draw();
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

// ���� ���� ���� �� true
bool TankGame::Exit()
{
	if( m_currentstage == RESULT && stage->GetStage() == -1 )
	{
		stage->StageReset( 0 );
		stage->SetGrade( 0 );
		ResetGame();
		return true;
	}
	return false;
}

void TankGame::Init()
{
	stage = TankStage::Instance();
	StageLoad( stage->GetStage() );
	m_player = new PlayerTank();

	// �� �ʱ�ȭ�� ����� �ȵǴ°���
	int enemyCount = TankStage::Instance()->nEnemyCount;
	m_enemy = new EnemyTank[enemyCount];
}

void TankGame::Release()
{
	SAFE_DELETE( m_player );
	SAFE_DELETE_ARRAY( m_enemy );
}

// ��𼭵� �������� �޾� ������ ���� �Լ��� ����
int TankGame::GetMap( int x, int y )
{
	return nMap[y][x];
}

// �� ���� �Լ�
void TankGame::SetMap( int x, int y, int map )
{
	nMap[y][x] = map;
}

// �������� ������ ���� �ҷ��´�. _stage �� �� �߰� �Ǹ� ���..
void TankGame::StageLoad(int _stage)
{
	FILE* fp;
	TankStage* stage = TankStage::Instance();
	int i, j;

	fopen_s( &fp, "Tank/map1.txt", "rt" );
	fscanf_s( fp, "�� ĳ���ͼ� : %d\n", &stage->nEnemyCount );
	fscanf_s( fp, "�� ĳ���Ͱ� ������ ��ġ ���� : %d\n", &stage->nEnemyPositionCount );

	if( stage->pEnemyPosition != NULL )
		free( stage->pEnemyPosition );

	// �� �� ��ŭ �Ҵ�
	stage->pEnemyPosition = (POS_XY*)malloc( sizeof( POS_XY )*stage->nEnemyPositionCount );

	for( i = 0; i < stage->nEnemyPositionCount; i++ )
	{
		fscanf_s( fp, "%d %d\n", &stage->pEnemyPosition[i].nX, &stage->pEnemyPosition[i].nY );
	}
	fscanf_s( fp, "���� �ʱ� ��ġ : %d %d\n", &stage->nBossX, &stage->nBossY );
	fscanf_s( fp, "�÷��̾� �ʱ� ��ġ : %d %d\n", &stage->nPlayerX, &stage->nPlayerY );
	fscanf_s( fp, "�� ĳ���� ���� ���� : %d\n", &stage->nEnemyTypeCount );

	for( i = 0; i < stage->nEnemyTypeCount; i++ )
		fscanf_s( fp, "�����: %d �̵��ð� ����: %d �̻���: %d\n", &stage->enemyType[i].nLife, &stage->enemyType[i].nMoveTime, &stage->enemyType[i].nFireTime );

	for( i = 0; i < stage->nEnemyCount; i++ )
		fscanf_s( fp, "Ÿ���ε���: %d ��ĳ���� ���� �ε���: %d ���� �ð�: %d\n", &stage->enemyType[i].nTypeIndex, &stage->enemyType[i].nPosIndex, &stage->enemyType[i].nAppearanceTime );

	for( i = 0; i < MAPSIZE::MAP_ROW; i++ )
	{
		for( j = 0; j < MAPSIZE::MAP_COL; j++ )
		{
			fscanf_s( fp, "%d ", &nMap[i][j] );
		}
	}
	//stage->Init();
	fclose( fp );
}

// ���� Ŭ���� ���� üũ
void TankGame::GameClearCheck()
{
	if( !m_player->IsDead() && stage->nBossLife > 0 )
	{
		m_updateOldTime = clock();
		m_currentstage = SUCCESS;
	}
	else
		m_currentstage = FAILED;
}

// ���� �׸���
void TankGame::DrawMap()
{
	for( int i = 0; i < MAP_ROW; ++i )
	{
		for( int j = 0; j < MAP_COL; ++j )
		{
			if( nMap[i][j] == PLAYER || nMap[i][j] == ENEMY )
				screen->ScreenPrint( j * 2, i, m_tile[BLANK] );
			else
				screen->ScreenPrint( j * 2, i, m_tile[nMap[i][j]] );
		}
	}
}

// ���� �ٽ� ����
void TankGame::ResetGame()
{
	StageLoad( stage->GetStage() );
	m_player->Init();
	for( int i = 0; i < stage->nEnemyCount; ++i )
		m_enemy[i].Init();
	m_currentstage = READY; 
	m_updateOldTime = clock();
}

// box �Լ� ���� �׵θ� �׷���
void TankGame::Box()
{
	int i;

	screen->ScreenPrint( 0, 0, "������������������������������������������������������������" );
	for( i = 1; i <= 19; i++ )
		screen->ScreenPrint( 0, i, "��                                                        ��" );
	screen->ScreenPrint( 0, 20, "������������������������������������������������������������" );
}
void TankGame::InitScreen()
{
	screen->ScreenPrint( 0, 0, "������������������������������������������������������������" );
	screen->ScreenPrint( 0, 1, "��                                                        ��" );
	screen->ScreenPrint( 0, 2, "��         -----                                          ��" );
	screen->ScreenPrint( 0, 3, "��        /    |                                       /  ��" );
	screen->ScreenPrint( 0, 4, "��       /       |    ��ũ ����                       /   ��" );
	screen->ScreenPrint( 0, 5, "��      /          |                            /-----/   ��" );
	screen->ScreenPrint( 0, 6, "��     /            |---------------|         /           ��" );
	screen->ScreenPrint( 0, 7, "��    /                               |      /            ��" );
	screen->ScreenPrint( 0, 8, "��   /              ��������������      |   /             ��" );
	screen->ScreenPrint( 0, 9, "��  /               ��          ��       |/               ��" );
	screen->ScreenPrint( 0, 10, "��/                 ��    ��    ��                        ��" );
	screen->ScreenPrint( 0, 11, "��     ( (    ��������������������������     ) )          ��" );
	screen->ScreenPrint( 0, 12, "��            ��                      ��                  ��" );
	screen->ScreenPrint( 0, 13, "��           �� ��                   �� ��                ��" );
	screen->ScreenPrint( 0, 14, "��           �� �� �������������������� ��                ��" );
	screen->ScreenPrint( 0, 15, "��           �� ��                   �� ��                ��" );
	screen->ScreenPrint( 0, 16, "��  ~ ^ ~ $~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^~ ~ ~ ~ ~ $ ~    ~��" );
	screen->ScreenPrint( 0, 17, "��                                                        ��" );
	screen->ScreenPrint( 0, 18, "��                  Press Space Key !!                    ��" );
	screen->ScreenPrint( 0, 19, "��                                                        ��" );
	screen->ScreenPrint( 0, 20, "������������������������������������������������������������" );
}

void TankGame::ReadyScreen()
{
	char string[100];

	Box();
	sprintf_s( string, "%d ��������", stage->GetStage() + 1 );
	screen->ScreenPrint( 25, 9, string );
}

void TankGame::StateScreen()
{
	char string[100];
	sprintf_s( string, "���ΰ� �����: %d", m_player->GetLife() );
	screen->ScreenPrint( 50, 2, string );
	sprintf_s( string, "���� �����: %d", stage->nBossLife );
	screen->ScreenPrint( 50, 4, string );
	sprintf_s( string, "�� ��ũ ��: %d", stage->nEnemyCount );
	screen->ScreenPrint( 50, 6, string );
	sprintf_s( string, "�ı��� ��ũ ��: %d", stage->nDeadEnemy );
	screen->ScreenPrint( 50, 8, string );
	sprintf_s( string, "����: %d", stage->GetGrade() );
	screen->ScreenPrint( 50, 10, string );
}

void TankGame::SuccessScreen()
{
	screen->ScreenPrint( 0, 0, "������������������������������������������������������������" );
	screen->ScreenPrint( 0, 1, "��                                                        ��" );
	screen->ScreenPrint( 0, 2, "��                                                        ��" );
	screen->ScreenPrint( 0, 3, "��                                                        ��" );
	screen->ScreenPrint( 0, 4, "��                                                        ��" );
	screen->ScreenPrint( 0, 5, "��                                                        ��" );
	screen->ScreenPrint( 0, 6, "��                                                        ��" );
	screen->ScreenPrint( 0, 7, "��                                                        ��" );
	screen->ScreenPrint( 0, 8, "��                     ////����                           ��" );
	screen->ScreenPrint( 0, 9, "��                    q ��. �� p (^)@                     ��" );
	screen->ScreenPrint( 0, 10, "��                    (��������) //                       ��" );
	screen->ScreenPrint( 0, 11, "��                   �� �̼� ���� ��                      ��" );
	screen->ScreenPrint( 0, 12, "��                                                        ��" );
	screen->ScreenPrint( 0, 13, "��                                                        ��" );
	screen->ScreenPrint( 0, 14, "��                                                        ��" );
	screen->ScreenPrint( 0, 15, "��                                                        ��" );
	screen->ScreenPrint( 0, 16, "��                                                        ��" );
	screen->ScreenPrint( 0, 17, "��                                                        ��" );
	screen->ScreenPrint( 0, 18, "��                                                        ��" );
	screen->ScreenPrint( 0, 19, "��                                                        ��" );
	screen->ScreenPrint( 0, 20, "������������������������������������������������������������" );
}

void TankGame::FailureScreen()
{
	screen->ScreenPrint( 0, 0, "������������������������������������������������������������" );
	screen->ScreenPrint( 0, 1, "��                                                        ��" );
	screen->ScreenPrint( 0, 2, "��                                                        ��" );
	screen->ScreenPrint( 0, 3, "��                                                        ��" );
	screen->ScreenPrint( 0, 4, "��                                                        ��" );
	screen->ScreenPrint( 0, 5, "��                                                        ��" );
	screen->ScreenPrint( 0, 6, "��                                                        ��" );
	screen->ScreenPrint( 0, 7, "��                    �̼� ���� !!!!                      ��" );
	screen->ScreenPrint( 0, 8, "��                                                        ��" );
	screen->ScreenPrint( 0, 9, "��                                                        ��" );
	screen->ScreenPrint( 0, 10, "��                               �ܦ�����                 ��" );
	screen->ScreenPrint( 0, 11, "��                                 ��  ��                 ��" );
	screen->ScreenPrint( 0, 12, "��                                �����                ��" );
	screen->ScreenPrint( 0, 13, "��                                                        ��" );
	screen->ScreenPrint( 0, 14, "��                                                        ��" );
	screen->ScreenPrint( 0, 15, "��                                                        ��" );
	screen->ScreenPrint( 0, 16, "��                ��� �Ͻðڽ��ϱ�? (y/n)                ��" );
	screen->ScreenPrint( 0, 17, "��                                                        ��" );
	screen->ScreenPrint( 0, 18, "��                                                        ��" );
	screen->ScreenPrint( 0, 19, "��                                                        ��" );
	screen->ScreenPrint( 0, 20, "������������������������������������������������������������" );
}


void TankGame::ResultScreen()
{
	char string[100];

	Box();

	screen->ScreenPrint( 3, 3, "                     ��ũ ���� ��" );
	screen->ScreenPrint( 3, 6, "                    ��������������" );
	screen->ScreenPrint( 3, 7, "               ~~   ��          ��" );
	screen->ScreenPrint( 3, 8, "        ~~          ��    ��    ��" );
	screen->ScreenPrint( 3, 9, "    ��         ��������������������������" );
	screen->ScreenPrint( 3, 10, "  ������       ��                      ��" );
	screen->ScreenPrint( 3, 11, "   ����      �� ��                   �� ��" );
	screen->ScreenPrint( 3, 12, "             �� �� �������������������� ��" );
	screen->ScreenPrint( 3, 13, "             �� ��                   �� ��" );
	screen->ScreenPrint( 3, 14, "~ ~ ^ ~ $~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^~ ~ ~ ~ /~ $ ~~" );
	sprintf_s( string, "Score : %d", stage->GetGrade() );
	screen->ScreenPrint( 39, 7, string );
}

TankGame::TankGame() : m_currentstage( INIT )
{
	Init();
}

TankGame::~TankGame()
{
	Release();
}