#include <conio.h>		// _kbhit 함수 사용
#include "BaseGame.h"

#define EXT_KEY			0xffffffe0	//확장키 인식값 

// 입력 받은 키 반환
int BaseGame::KeyInput()
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

BaseGame::BaseGame()
{
	screen = Screen::Instance();
	srand( (unsigned int)time( NULL ) );
}

BaseGame::~BaseGame()
{
	Screen::ReleaseInstance();
}