#include <conio.h>		// _kbhit �Լ� ���
#include "BaseGame.h"

#define EXT_KEY			0xffffffe0	//Ȯ��Ű �νİ� 

// �Է� ���� Ű ��ȯ
int BaseGame::KeyInput()
{
	int nKey = 0;

	if( _kbhit() )
	{
		nKey = _getch();
		if( nKey == EXT_KEY )	// Ȯ��Ű üũ
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