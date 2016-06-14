#ifndef ENEMY_H_
#define ENEMY_H_

#include "Tank.h"

class EnemyTank : public Tank
{
public :
	enum STATE { ENEMY_STOP, ENEMY_RUN, ENEMY_ROTATION };
	void EnemySpawn( clock_t gameStartTime );
	virtual void Init() override;
	virtual void Fire() override;
	virtual void Move( int key = 0 ) override;
	virtual void Draw() override;
	virtual bool IsCollision( Object* coll = nullptr ) override;

private :
	DIRECT ChangeIntToDirect( int num );
	STATE nState;			// ���� ����
	int nAppearanceTime;	// ���� �ð�
	int nTypeIndex;
	int nPosIndex;

	int bulletCount;

public :
	EnemyTank();
};

#endif // !ENEMY_H_
