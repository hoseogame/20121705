#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Screen.h"
#include "BaseGame.h"
#include <vector>

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

	void AddGame( BaseGame* _newGame, char* _name );
	void GameCompany();	// 함수이름을 뭐라해야핮맂다ㅡㄹㅈ댛머쟈ㅐ허


	Screen* screen;

	std::vector<BaseGame*> m_gameList;
	std::vector<BaseGame*>::const_iterator m_game;	// 게임을 참조하는 반복자
	std::vector<char*> m_gameName;
	std::vector<char*>::const_iterator m_gameNameIter;
	int m_gameCount;	// 추가된 게임 수
	int m_select;
	bool m_isPlay;
	bool m_exit;

public :
	GameManager();
	~GameManager();
	
};

#endif /*GAMEMANAGER_H_*/