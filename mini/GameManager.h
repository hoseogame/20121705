#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Screen.h"
#include "BaseGame.h"

/*
	- GameManager.h -
		* GameManager Class
		* 게임 종료, 게임 변경 등 관리
*/

class GameManager
{
public :
	int KeyInput();	// 입력 받은 키 반환

public :
	void Update();
	void Render();
	bool Exit();

private :
	void Init();
	void Release();
	void SelectGame();

	void SelectScreenDraw();
	void SelectBoxDraw();

	void ChangeGame();


	Screen* screen;

	BaseGame* m_game[3];
	int m_select;
	bool m_isPlay;
	bool m_exit;

public :
	GameManager();
	~GameManager();
	
};

#endif /*GAMEMANAGER_H_*/