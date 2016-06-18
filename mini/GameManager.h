#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Screen.h"
#include "BaseGame.h"
#include <vector>

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

	void AddGame( BaseGame* _newGame, char* _name );
	void GameCompany();	// �Լ��̸��� �����ؾ��F���٤Ѥ������������


	Screen* screen;

	std::vector<BaseGame*> m_gameList;
	std::vector<BaseGame*>::const_iterator m_game;	// ������ �����ϴ� �ݺ���
	std::vector<char*> m_gameName;
	std::vector<char*>::const_iterator m_gameNameIter;
	int m_gameCount;	// �߰��� ���� ��
	int m_select;
	bool m_isPlay;
	bool m_exit;

public :
	GameManager();
	~GameManager();
	
};

#endif /*GAMEMANAGER_H_*/