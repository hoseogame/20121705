#ifndef OBJECT_H_
#define OBJECT_H_

/*
	Object.h
		오브젝트들의 부모 클래스
*/
#include "../Screen.h"
#include "TankStage.h"
#include "TankGame.h"

class Object
{
public :
	enum DIRECT
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77
	};

public :
	virtual void Draw() = 0;
	virtual void Move( int key = 0) = 0;
	virtual bool IsCollision( Object* coll = nullptr ) = 0;
	int GetX()  { return nX; }
	int GetY()  { return nY; }
	int GetLife() { return nLife; }
	bool IsDead();

	void RecvDamage( int damage );

protected :
	int nX, nY;			// 오브젝트 좌표
	int nLife;			// 오브젝트 생명력
	DIRECT eDirect;		// 오브젝트 방향
	int nMoveTime;		// 오브젝트 이동 시간
	int nOldMoveTime;	// 이전 이동 시간

	// BLANK : 빈공간, BLOCK : 깨지는 벽, ROCK : 깨지지 않는 벽, BOSS : 보스
	enum OBJECT { BLANK = 0, BLOCK = 1, ROCK = 2, PLAYER = 3, BOSS = 4, ENEMY = 5 };

	Screen* screen;
	TankStage* stage;

public :
	Object();
	~Object();
	
};

#endif // !OBJECT_H_
