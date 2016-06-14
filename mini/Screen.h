#ifndef SCREEN_H_
#define SCREEN_H_

#include <Windows.h>


/*
	- Screen.h -
		* Screen Class
		* ȭ���� �����ϴ� Ŭ����
		* �̱����� ����� �ϳ��� �ν��Ͻ��� ������ ��.
*/

class Screen
{
public:
	// �۾� �� 0 ~ 15 ���� ���� ���� ����
	enum COLOR
	{
		BLACK,			/*  0 : ��� */
		DARK_BLUE,		/*  1 : ��ο� �Ķ� */
		DARK_GREEN,		/*  2 : ��ο� �ʷ� */
		DARK_SKY_BLUE,  /*  3 : ��ο� �ϴ� */
		DARK_RED,		/*  4 : ��ο� ���� */
		DARK_VOILET,	/*  5 : ��ο� ���� */
		DARK_YELLOW,	/*  6 : ��ο� ��� */
		GRAY,			/*  7 : ȸ�� */
		DARK_GRAY,		/*  8 : ��ο� ȸ�� */
		BLUE,			/*  9 : �Ķ� */
		GREEN,			/* 10 : �ʷ� */
		SKY_BLUE,		/* 11 : �ϴ� */
		RED,			/* 12 : ���� */
		VIOLET,			/* 9 : ���� */
		YELLOW,			/* 10 : ��� */
		WHITE,			/* 15 : �Ͼ� */
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