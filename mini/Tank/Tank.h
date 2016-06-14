#ifndef TANK_H_
#define	TANK_H_

#include "Object.h"
#include "Bullet.h"
#define BULLET 5

class Tank : public Object
{
public : 
	virtual void Init() = 0;
	virtual void Fire();
	Bullet bullet[BULLET];
	//const Bullet* const GetBullet( int index );

	virtual void Move( int key = 0 ) override;
	virtual void Draw() override;

	int GetLife() { return nLife; }
protected : 
	int nFireTime;
	int nOldFireTime;
	int nBulletIndex;



private :
	//virtual bool IsCollision( Object* coll = nullptr ) override;

public :
	Tank();
};

#endif // !TANK_H_
