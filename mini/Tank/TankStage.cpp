#include "TankStage.h"
#include <cstdlib>

TankStage* TankStage::_instance = nullptr;

TankStage* TankStage::Instance()
{
	if( _instance == nullptr )
		_instance = new TankStage;

	return _instance;
}

// 스테이지 재 설정, 몬스터 타입들도 필요하면 추가
void TankStage::StageReset( int round )
{
	if( round >= ROUND )
	{
		round %= ROUND;
	}

	nBossLife = 2;
	nEnemyIndex = 0;
	nDeadEnemy = 0;
	nStage = round;
}

// 점수 설정
void TankStage::SetGrade( int _score )
{
	if( _score != 0 )
		nGrade += _score;
	else
		nGrade = 0;
}

void TankStage::Init()
{
	if( pEnemyPosition != NULL )
		free( pEnemyPosition );

	TankStage::pEnemyPosition = (POS_XY*)malloc( sizeof( POS_XY )*nEnemyPositionCount );
}

void TankStage::Release()
{
	if( _instance != nullptr )
		delete _instance;

	_instance = nullptr;

	delete[] pEnemyPosition;
	pEnemyPosition = nullptr;
}

TankStage::TankStage() : nStage( 0 ), nGrade( 0 ), nEnemyIndex( 0 ), nDeadEnemy( 0 ), nBossLife( 2 )
{
}

TankStage::~TankStage()
{
	Release();
}