#include "Stage.h"

Stage* Stage::_instance = nullptr;

Stage* Stage::Instance()
{
	if( _instance == nullptr )
		_instance = new Stage();

	return _instance;
}


void Stage::StageSet( int round )
{
	if( round >= ROUND )
	{
		round %= ROUND;
	}
	m_nGoalBall			= stageInfo[round][GOALBALL];
	m_nGoalPostLength	= stageInfo[round][GOALPOSTLEN];
	m_nGoalPostX		= stageInfo[round][GOALPOSX];
	m_nGoalPostY		= stageInfo[round][GOALPOSY];
	m_nDist				= stageInfo[round][DISTANCE];
	m_moveTime			= stageInfo[round][MOVETIME];
	m_limitTime			= stageInfo[round][LIMITTIME] * 1000;
}

void Stage::Init()
{
	m_nGoalBall			= stageInfo[0][GOALBALL];
	m_nGoalPostLength	= stageInfo[0][GOALPOSTLEN];
	m_nGoalPostX		= stageInfo[0][GOALPOSX];
	m_nGoalPostY		= stageInfo[0][GOALPOSY];
	m_nDist				= stageInfo[0][DISTANCE];
	m_moveTime			= stageInfo[0][MOVETIME];
	m_limitTime			= stageInfo[0][LIMITTIME] * 1000;
}

void Stage::Release()
{
	if( _instance != nullptr )
		delete _instance;

	_instance = nullptr;
}

Stage::Stage()
{
	Init();
}

Stage::~Stage()
{
	Release();
}