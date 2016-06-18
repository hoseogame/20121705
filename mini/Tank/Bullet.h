#ifndef BULLET_H_
#define BULLET_H_

#include "Object.h"

class Bullet : public Object
{
public :
	int TakeDamage();
	void SetPosition( int x, int y, DIRECT dir );	// �Ѿ� ������ ����
	void Draw() override;					// �Ѿ� �׸�
	void Move( int key = 0 ) override;			// ��������
	bool IsCollision( Object* coll = nullptr ) override;	// �浹 �� true ��ȯ

private :
	int nDamage;

public :
	Bullet();
};

#endif // !BULLET_H_
