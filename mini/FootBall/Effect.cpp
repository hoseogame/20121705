#include "Effect.h"
#include "../Screen.h"

bool Effect::EffectUpdate( clock_t curTime )
{
	if( curTime - m_startTime > m_stayTime )
		return false;
	return true;
}

void Effect::EffectDraw( int x, int y )
{
	Screen* screen = Screen::Instance();
	screen->ScreenPrint( x, y, "�� )) ���� (( ��" );
	screen->ScreenPrint( x, y + 1, "��(^^')/ ��(\"*')/" );
	screen->ScreenPrint( x, y + 2, "   ��       ��" );
	screen->ScreenPrint( x, y + 3, "  ����    ����" );
}