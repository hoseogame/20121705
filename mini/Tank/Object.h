#ifndef OBJECT_H_
#define OBJECT_H_

/*
	Object.h
		������Ʈ���� �θ� Ŭ����
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
	int nX, nY;			// ������Ʈ ��ǥ
	int nLife;			// ������Ʈ �����
	DIRECT eDirect;		// ������Ʈ ����
	int nMoveTime;		// ������Ʈ �̵� �ð�
	int nOldMoveTime;	// ���� �̵� �ð�

	// BLANK : �����, BLOCK : ������ ��, ROCK : ������ �ʴ� ��, BOSS : ����
	enum OBJECT { BLANK = 0, BLOCK = 1, ROCK = 2, PLAYER = 3, BOSS = 4, ENEMY = 5 };

	Screen* screen;
	TankStage* stage;

public :
	Object();
	~Object();
	
};

#endif // !OBJECT_H_
