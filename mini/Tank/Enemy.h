#ifndef ENEMY_H_
#define ENEMY_H_

#include "Tank.h"

class EnemyTank : public Tank
{
public :
	enum STATE { ENEMY_STOP, ENEMY_RUN, ENEMY_ROTATION };
	void EnemySpawn( clock_t gameStartTime );
	void Init() override;
	void Fire() override;
	void Move( int key = 0 ) override;
	void Draw() override;
	bool IsCollision( Object* coll = nullptr ) override;

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
