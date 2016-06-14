#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Screen.h"
#include "BaseGame.h"

/*
	- GameManager.h -
		* GameManager Class
		* ���� ����, ���� ���� �� ����
*/

class GameManager
{
public :
	int KeyInput();	// �Է� ���� Ű ��ȯ

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