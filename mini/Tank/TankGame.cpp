#include "TankGame.h"
#include "TankStage.h"
#include "PlayerTank.h"
#include "Enemy.h"
#include <cstdio>

// static 변수로 초기화를 따로 해주지 않으면 메모리 할당이 이뤄지지 않아
// 초기화 없이 호출 시 확인할 수 없다는 링크에러가 뜬다.
int TankGame::nMap[MAP_ROW][MAP_COL] = { 0, };	

// 업뎃
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
		// 캐릭터 업데이트
			m_player->Move( key );

			// 적 스폰
			for( int i = stage->nEnemyIndex; i < stage->nEnemyCount; ++i )
			{
				m_enemy[i].EnemySpawn( m_gameStartTime );
			}

			// 적 업데이트
			for( int i = 0; i < stage->nEnemyIndex; ++i )
			{
				m_enemy[i].Move();
			}

		// 총알 이동, 충돌 체크
			for( int i = 0; i < BULLET; ++i )
			{
				m_player->bullet[i].Move();
				m_player->bullet[i].IsCollision();
				for( int j = 0; j < stage->nEnemyIndex; ++j )
				{
					// 쐇는데 맞췄으면
					if( m_player->bullet[i].IsCollision( &m_enemy[j] ) )
					{
						// 맞춘애가 죽으면
						if( m_enemy[j].IsDead() )
						{
							++(stage->nDeadEnemy);	// 죽음 카운트
							stage->SetGrade( 10 );	// 점수 증 ! 가!
						}
					}
					m_enemy[j].bullet[i].Move();
					m_enemy[j].bullet[i].IsCollision();
					m_enemy[j].bullet[i].IsCollision(m_player);
				}
			}

		// 스테이지 상태 체크
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

// 렌더
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

// 종료 조건 만족 시 true
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

	// 왜 초기화가 제대로 안되는거지
	int enemyCount = TankStage::Instance()->nEnemyCount;
	m_enemy = new EnemyTank[enemyCount];
}

void TankGame::Release()
{
	SAFE_DELETE( m_player );
	SAFE_DELETE_ARRAY( m_enemy );
}

// 어디서든 맵정보를 받아 오도록 정적 함수로 만듬
int TankGame::GetMap( int x, int y )
{
	return nMap[y][x];
}

// 맵 수정 함수
void TankGame::SetMap( int x, int y, int map )
{
	nMap[y][x] = map;
}

// 스테이지 정보와 맵을 불러온다. _stage 는 맵 추가 되면 사용..
void TankGame::StageLoad(int _stage)
{
	FILE* fp;
	TankStage* stage = TankStage::Instance();
	int i, j;

	fopen_s( &fp, "Tank/map1.txt", "rt" );
	fscanf_s( fp, "적 캐릭터수 : %d\n", &stage->nEnemyCount );
	fscanf_s( fp, "적 캐릭터가 출현할 위치 개수 : %d\n", &stage->nEnemyPositionCount );

	if( stage->pEnemyPosition != NULL )
		free( stage->pEnemyPosition );

	// 적 수 만큼 할당
	stage->pEnemyPosition = (POS_XY*)malloc( sizeof( POS_XY )*stage->nEnemyPositionCount );

	for( i = 0; i < stage->nEnemyPositionCount; i++ )
	{
		fscanf_s( fp, "%d %d\n", &stage->pEnemyPosition[i].nX, &stage->pEnemyPosition[i].nY );
	}
	fscanf_s( fp, "보스 초기 위치 : %d %d\n", &stage->nBossX, &stage->nBossY );
	fscanf_s( fp, "플레이어 초기 위치 : %d %d\n", &stage->nPlayerX, &stage->nPlayerY );
	fscanf_s( fp, "적 캐릭터 종류 개수 : %d\n", &stage->nEnemyTypeCount );

	for( i = 0; i < stage->nEnemyTypeCount; i++ )
		fscanf_s( fp, "생명력: %d 이동시간 간격: %d 미사일: %d\n", &stage->enemyType[i].nLife, &stage->enemyType[i].nMoveTime, &stage->enemyType[i].nFireTime );

	for( i = 0; i < stage->nEnemyCount; i++ )
		fscanf_s( fp, "타입인덱스: %d 적캐릭터 생성 인덱스: %d 출현 시간: %d\n", &stage->enemyType[i].nTypeIndex, &stage->enemyType[i].nPosIndex, &stage->enemyType[i].nAppearanceTime );

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

// 게임 클리어 여부 체크
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

// 맵을 그린다
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

// 게임 다시 시작
void TankGame::ResetGame()
{
	StageLoad( stage->GetStage() );
	m_player->Init();
	for( int i = 0; i < stage->nEnemyCount; ++i )
		m_enemy[i].Init();
	m_currentstage = READY; 
	m_updateOldTime = clock();
}

// box 함수 게임 테두리 그려줌
void TankGame::Box()
{
	int i;

	screen->ScreenPrint( 0, 0, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" );
	for( i = 1; i <= 19; i++ )
		screen->ScreenPrint( 0, i, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 20, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" );
}
void TankGame::InitScreen()
{
	screen->ScreenPrint( 0, 0, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 0, 1, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 2, "┃         -----                                          ┃" );
	screen->ScreenPrint( 0, 3, "┃        /    |                                       /  ┃" );
	screen->ScreenPrint( 0, 4, "┃       /       |    탱크 게임                       /   ┃" );
	screen->ScreenPrint( 0, 5, "┃      /          |                            /-----/   ┃" );
	screen->ScreenPrint( 0, 6, "┃     /            |---------------|         /           ┃" );
	screen->ScreenPrint( 0, 7, "┃    /                               |      /            ┃" );
	screen->ScreenPrint( 0, 8, "┃   /              ┏━━━━━┓      |   /             ┃" );
	screen->ScreenPrint( 0, 9, "┃  /               ┃          ┃       |/               ┃" );
	screen->ScreenPrint( 0, 10, "┃/                 ┃    ◎    ┃                        ┃" );
	screen->ScreenPrint( 0, 11, "┃     ( (    ┏━━━━━━━━━━━┓     ) )          ┃" );
	screen->ScreenPrint( 0, 12, "┃            ┃                      ┃                  ┃" );
	screen->ScreenPrint( 0, 13, "┃           ▤ ▤                   ▤ ▤                ┃" );
	screen->ScreenPrint( 0, 14, "┃           ▤ ▤ ━━━━━━━━━▤ ▤                ┃" );
	screen->ScreenPrint( 0, 15, "┃           ▤ ▤                   ▤ ▤                ┃" );
	screen->ScreenPrint( 0, 16, "┃  ~ ^ ~ $~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^~ ~ ~ ~ ~ $ ~    ~┃" );
	screen->ScreenPrint( 0, 17, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 18, "┃                  Press Space Key !!                    ┃" );
	screen->ScreenPrint( 0, 19, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 20, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" );
}

void TankGame::ReadyScreen()
{
	char string[100];

	Box();
	sprintf_s( string, "%d 스테이지", stage->GetStage() + 1 );
	screen->ScreenPrint( 25, 9, string );
}

void TankGame::StateScreen()
{
	char string[100];
	sprintf_s( string, "주인공 생명력: %d", m_player->GetLife() );
	screen->ScreenPrint( 50, 2, string );
	sprintf_s( string, "보스 생명력: %d", stage->nBossLife );
	screen->ScreenPrint( 50, 4, string );
	sprintf_s( string, "적 탱크 수: %d", stage->nEnemyCount );
	screen->ScreenPrint( 50, 6, string );
	sprintf_s( string, "파괴된 탱크 수: %d", stage->nDeadEnemy );
	screen->ScreenPrint( 50, 8, string );
	sprintf_s( string, "점수: %d", stage->GetGrade() );
	screen->ScreenPrint( 50, 10, string );
}

void TankGame::SuccessScreen()
{
	screen->ScreenPrint( 0, 0, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 0, 1, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 2, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 3, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 4, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 5, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 6, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 7, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 8, "┃                     ////＼＼                           ┃" );
	screen->ScreenPrint( 0, 9, "┃                    q ∧. ∧ p (^)@                     ┃" );
	screen->ScreenPrint( 0, 10, "┃                    (└──┘) //                       ┃" );
	screen->ScreenPrint( 0, 11, "┃                   ♬ 미션 성공 ♪                      ┃" );
	screen->ScreenPrint( 0, 12, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 13, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 14, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 15, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 16, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 17, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 18, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 19, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 20, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" );
}

void TankGame::FailureScreen()
{
	screen->ScreenPrint( 0, 0, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" );
	screen->ScreenPrint( 0, 1, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 2, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 3, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 4, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 5, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 6, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 7, "┃                    미션 실패 !!!!                      ┃" );
	screen->ScreenPrint( 0, 8, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 9, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 10, "┃                               ●┳━┓                 ┃" );
	screen->ScreenPrint( 0, 11, "┃                                 ┛  ┗                 ┃" );
	screen->ScreenPrint( 0, 12, "┃                                ■■■■                ┃" );
	screen->ScreenPrint( 0, 13, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 14, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 15, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 16, "┃                계속 하시겠습니까? (y/n)                ┃" );
	screen->ScreenPrint( 0, 17, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 18, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 19, "┃                                                        ┃" );
	screen->ScreenPrint( 0, 20, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" );
}


void TankGame::ResultScreen()
{
	char string[100];

	Box();

	screen->ScreenPrint( 3, 3, "                     탱크 게임 끝" );
	screen->ScreenPrint( 3, 6, "                    ┏━━━━━┓" );
	screen->ScreenPrint( 3, 7, "               ~~   ┃          ┃" );
	screen->ScreenPrint( 3, 8, "        ~~          ┃    ◎    ┃" );
	screen->ScreenPrint( 3, 9, "    ●         ┏━━━━━━━━━━━┓" );
	screen->ScreenPrint( 3, 10, "  ┗┃┛       ┃                      ┃" );
	screen->ScreenPrint( 3, 11, "   ┏┓      ▤ ▤                   ▤ ▤" );
	screen->ScreenPrint( 3, 12, "             ▤ ▤ ━━━━━━━━━▤ ▤" );
	screen->ScreenPrint( 3, 13, "             ▤ ▤                   ▤ ▤" );
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