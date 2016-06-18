#ifndef BULLET_H_
#define BULLET_H_

#include "Object.h"

class Bullet : public Object
{
public :
	int TakeDamage();
	void SetPosition( int x, int y, DIRECT dir );	// 총알 포지션 수정
	void Draw() override;					// 총알 그림
	void Move( int key = 0 ) override;			// 움직움직
	bool IsCollision( Object* coll = nullptr ) override;	// 충돌 시 true 반환

private :
	int nDamage;

public :
	Bullet();
};

#endif // !BULLET_H_
