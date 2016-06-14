#include "Screen.h"

void Screen::ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	// 가상의 콘솔창 2개룰 만든다.
	g_hScreen[0] = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );
	g_hScreen[1] = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );

	// 커서 숨기기
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo( g_hScreen[0], &cci );
	SetConsoleCursorInfo( g_hScreen[1], &cci );
}

void Screen::ScreenFlipping()
{
	Sleep( 10 );
	SetConsoleActiveScreenBuffer( g_hScreen[g_nScreenIndex] );
	g_nScreenIndex = !g_nScreenIndex;
}

void Screen::ScreenClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter( g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw );
}

void Screen::ScreenRelease()
{
	CloseHandle( g_hScreen[0] );
	CloseHandle( g_hScreen[1] );
}


void Screen::ScreenPrint( int x, int y, char *string )
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition( g_hScreen[g_nScreenIndex], CursorPosition );
	WriteFile( g_hScreen[g_nScreenIndex], string, strlen( string ), &dw, NULL );
}

// 0 ~ 15 까지 색상 설정 가능
void Screen::SetColor( COLOR color )
{
	SetConsoleTextAttribute( g_hScreen[g_nScreenIndex], color );
}

Screen* Screen::_instance = nullptr;

Screen* Screen::Instance()
{
	if (_instance == nullptr)
		_instance = new Screen;

	return _instance;
}

void Screen::ReleaseInstance()
{
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
	}
}