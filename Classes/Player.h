#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "PlayerState.h"
#include "enums.h"

class PlayerState;

class Player : public cocos2d::Sprite
{

friend class PlayerState;
friend class Idle;
friend class WalkLeft;
friend class WalkRight;
friend class Jump;
friend class Fall;
friend class Shoot;
friend class Reload;

public:

	static Player* create(const std::string& filename);
	const PlayerState* getState() const;
	const char* getStateName()const;

	void input(Input input);
	void update(float dt) override;
//	void collision(bool b) override;

protected:

	void setState(PlayerState* state);

private:
   
	PlayerState* _state;

};
#endif // __PLAYER_H_
