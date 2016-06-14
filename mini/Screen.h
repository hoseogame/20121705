#ifndef SCREEN_H_
#define SCREEN_H_

#include <Windows.h>


/*
	- Screen.h -
		* Screen Class
		* 화면을 관리하는 클래스
		* 싱글톤을 사용해 하나의 인스턴스만 갖도록 함.
*/

class Screen
{
public:
	// 글씨 색 0 ~ 15 까지 색상 설정 가능
	enum COLOR
	{
		BLACK,			/*  0 : 까망 */
		DARK_BLUE,		/*  1 : 어두운 파랑 */
		DARK_GREEN,		/*  2 : 어두운 초록 */
		DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
		DARK_RED,		/*  4 : 어두운 빨강 */
		DARK_VOILET,	/*  5 : 어두운 보라 */
		DARK_YELLOW,	/*  6 : 어두운 노랑 */
		GRAY,			/*  7 : 회색 */
		DARK_GRAY,		/*  8 : 어두운 회색 */
		BLUE,			/*  9 : 파랑 */
		GREEN,			/* 10 : 초록 */
		SKY_BLUE,		/* 11 : 하늘 */
		RED,			/* 12 : 빨강 */
		VIOLET,			/* 9 : 보라 */
		YELLOW,			/* 10 : 노랑 */
		WHITE,			/* 15 : 하양 */
	};

public :
	static Screen*	Instance();
	static void		ReleaseInstance();

	void ScreenInit();
	void ScreenFlipping();
	void ScreenClear();
	void ScreenRelease();
	void ScreenPrint( int x, int y, char* string );
	void SetColor( COLOR color );

private :
	int		g_nScreenIndex = 0;
	HANDLE	g_hScreen[2] = { 0, };

private :
	Screen() {};
	static Screen* _instance;
};

#endif /* SCREEN_H_ */