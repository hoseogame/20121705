#include "TankStage.h"
#include <cstdlib>

TankStage* TankStage::_instance = nullptr;

TankStage* TankStage::Instance()
{
	if( _instance == nullptr )
		_instance = new TankStage;

	return _instance;
}

// �������� �� ����, ���� Ÿ�Ե鵵 �ʿ��ϸ� �߰�
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

// ���� ����
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