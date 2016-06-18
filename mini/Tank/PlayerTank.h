#ifndef PLAYER_TANK_H_
#define PLAYER_TANK_H_

#include "Tank.h"

class PlayerTank : public Tank
{
public :
	void Init() override;
	void Draw() override;
	bool IsCollision( Object* coll = nullptr ) override;

	PlayerTank();
};

#endif // !PLAYER_TANK_H_
