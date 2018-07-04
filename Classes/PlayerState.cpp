#include "PlayerState.h"

USING_NS_CC;

Idle PlayerState::idling;
WalkLeft PlayerState::goingLeft;
WalkRight PlayerState::goingRight;
Jump PlayerState::jumping;
Fall PlayerState::falling;
Shoot PlayerState::shooting;
Reload PlayerState::reloading;

static float jumpStart = 0;

void Idle::handleInput(Player* player, Input input)
{
	switch (input)
	{
	case JUMP_PRESS:
		player->setState(&PlayerState::jumping);
		break;
	case JUMP_RELEASE:
		break;
	case LEFT_PRESS:
		player->setState(&PlayerState::goingLeft);
		break;
	case LEFT_RELEASE:
		break;
	case RIGHT_PRESS:
		player->setState(&PlayerState::goingRight);
		break;
	case RIGHT_RELEASE:
		break;
	case SHOOT_PRESS:
		player->setState(&PlayerState::shooting);
		break;
	default:
		break;
	}
}

void Idle::handleUpdate(Player* player, float dt)
{

}


void WalkLeft::handleInput(Player* player, Input input)
{
	switch (input)
	{
	case JUMP_PRESS:
		player->setState(&PlayerState::jumping);
		break;
	case JUMP_RELEASE:
		break;
	case LEFT_PRESS:
		break;
	case LEFT_RELEASE:
		player->setState(&PlayerState::idling);
		break;
	case RIGHT_PRESS:
		player->setState(&PlayerState::goingRight);
		break;
	case RIGHT_RELEASE:
		break;
	default:
		break;
	}
}

void WalkLeft::handleUpdate(Player* player, float dt)
{
    //player->runAction(Animate::create(player->walkLeftAnimation));
    static const float maxLeft = 0;
    float currentX = player->getPositionX();
    float newX = currentX - 3;
    
    if (newX >= maxLeft){
        player->setPositionX(newX);
    }
    else {
        player->setPositionX(maxLeft);
    }
    
}


void WalkRight::handleInput(Player* player, Input input)
{
	switch (input)
	{
	case JUMP_PRESS:
		player->setState(&PlayerState::jumping);
		break;
	case JUMP_RELEASE:
		break;
	case LEFT_PRESS:
		player->setState(&PlayerState::goingLeft);
		break;
	case LEFT_RELEASE:
		break;
	case RIGHT_PRESS:
		break;
	case RIGHT_RELEASE:
		player->setState(&PlayerState::idling);
		break;
	default:
		break;
	}
}

void WalkRight::handleUpdate(Player* player, float dt)
{
    static const float maxRight = Director::getInstance()->getVisibleSize().width - 64; //- player->getContentSize().width;
    float currentX = player->getPositionX();
    float newX = currentX + 3;
    
    if (newX <= maxRight) player->setPositionX(newX);
    else
        player->setPositionX(maxRight);
}


void Jump::handleInput(Player* player, Input input)
{
	switch (input)
	{
	case JUMP_PRESS:
//		player->setState(&PlayerState::jumping);
		break;
	case JUMP_RELEASE:
		break;
	case LEFT_PRESS:
		break;
	case LEFT_RELEASE:
		break;
	case RIGHT_PRESS:
		/*
		static const float maxRight = Director::getInstance()->getVisibleSize().width - 64; 
		float currentJumpX = player->getPositionX();
		float newJumpX = currentJumpX + 3; 
		if (newJumpX <= maxRight) player->setPositionX(newJumpX);
		else
        	player->setPositionX(maxRight);
			*/
		break;
	case RIGHT_RELEASE:
		break;
	default:
		break;
	}
}

void Jump::handleUpdate(Player* player, float dt)
{
    jumpStart = player->getPositionY();
	static const float jumpHeight = jumpStart + 320; 
	float currentHeight = player->getPositionY(); 
	player->setPositionY(currentHeight + 8);

	if (currentHeight >= jumpHeight) {
        player->setState(&PlayerState::falling);
	}

}

void Fall::handleInput(Player* player, Input input)
{
	switch (input)
	{
	case JUMP_PRESS:
//		player->setState(&PlayerState::jumping);
		break;
	case JUMP_RELEASE:
		break;
	case LEFT_PRESS:
		break;
	case LEFT_RELEASE:
		break;
	case RIGHT_PRESS:
		break;
	case RIGHT_RELEASE:
		break;
	default:
		break;
	}
}

void Fall::handleUpdate(Player* player, float dt)
{
//    static const float jumpStart = jumpMax - 200;
    float currentY = player->getPositionY();
//	Hier Kollisionsabfrage mit Boden als bool-statement
}


void Shoot::handleInput(Player* player, Input input)
{
	switch (input)
	{
	case JUMP_PRESS:
		break;
	case JUMP_RELEASE:
		break;
	case LEFT_PRESS:
		break;
	case LEFT_RELEASE:
		break;
	case RIGHT_PRESS:
		break;
	case RIGHT_RELEASE:
		break;
	case SHOOT_PRESS:
		break;
	case SHOOT_RELEASE:
		player->setState(&PlayerState::reloading);
		break;
	default:
		break;
	}
}

void Shoot::handleUpdate(Player* player, float dt)
{
    player->shoot();
}


void Reload::handleInput(Player* player, Input input)
{
	switch (input)
	{
	case JUMP_PRESS:
		player->setState(&PlayerState::jumping);
		break;
	case JUMP_RELEASE:
		break;
	case LEFT_PRESS:
		player->setState(&PlayerState::goingLeft);
		break;
	case LEFT_RELEASE:
		break;
	case RIGHT_PRESS:
		player->setState(&PlayerState::goingRight);
        player->scheduleUpdate();
		break;
	case RIGHT_RELEASE:
		break;
	default:
		break;
	}
}


void Reload::handleUpdate(Player* player, float dt)
{
    player->setState(&PlayerState::idling);
    float delay = 3.0f;
    auto delayAction = DelayTime::create(delay);
    auto funcCallback = CallFunc::create([player](){
        player->shootAllowed = true;
    });
    player->runAction(Sequence::create(delayAction, funcCallback, NULL));
}


