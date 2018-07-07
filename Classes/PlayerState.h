#ifndef __PLAYER_STATE_H__
#define __PLAYER_STATE_H__

#include "cocos2d.h"
#include "Player.h"
#include "enums.h"

class Player;
class Idle;
class WalkLeft;
class WalkRight;
class Jump;
class Fall;
class Shoot;
class Reload;

class PlayerState
{
public:

	static Idle idling;
	static WalkLeft goingLeft;
	static WalkRight goingRight;
	static Jump jumping;
	static Fall falling;
	static Shoot shooting;
	static Reload reloading;

	virtual void handleInput(Player* player, Input input) = 0;
//	virtual void handleUpdate(Player* player, float dt) = 0;
	virtual void handleUpdate(Player* player, float dt, bool collision) = 0;
};

class Idle : public PlayerState
{
public:
	void handleInput(Player* player, Input input);
//	void handleUpdate(Player* player, float dt);
	void handleUpdate(Player* player, float dt, bool collision);
};


class WalkLeft : public PlayerState
{
public:
	void handleInput(Player* player, Input input);
//	void handleUpdate(Player* player, float dt);
	void handleUpdate(Player* player, float dt, bool collision);
};

class WalkRight : public PlayerState
{
public:
	void handleInput(Player* player, Input input);
//	void handleUpdate(Player* player, float dt);
	void handleUpdate(Player* player, float dt, bool collision);
};

class Jump : public PlayerState
{
public:
	void handleInput(Player* player, Input input);
//	void handleUpdate(Player* player, float dt);
	void handleUpdate(Player* player, float dt, bool collision);
};

class Fall : public PlayerState
{
public:
	void handleInput(Player* player, Input input);
//	void handleUpdate(Player* player, float dt);
	void handleUpdate(Player* player, float dt, bool collision);
};

class Shoot : public PlayerState
{
public:
	void handleInput(Player* player, Input input);
//	void handleUpdate(Player* player, float dt);
	void handleUpdate(Player* player, float dt, bool collision);
};

class Reload : public PlayerState
{
public:
	void handleInput(Player* player, Input input);
//	void handleUpdate(Player* player, float dt);
	void handleUpdate(Player* player, float dt, bool collision);
};

#endif // __PLAYER_STATE_H__

