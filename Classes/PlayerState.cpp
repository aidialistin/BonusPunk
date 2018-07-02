#include "PlayerState.h"

USING_NS_CC;

Idle PlayerState::idling;
WalkLeft PlayerState::goingLeft;
WalkRight PlayerState::goingRight;
Jump PlayerState::jumping;
Fall PlayerState::falling;
Shoot PlayerState::shooting;
Reload PlayerState::reloading;

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
    static const float maxLeft = 0;
    float currentX = player->getPositionX();
    float newX = currentX - 3;
    
    if (newX >= maxLeft)
        player->setPositionX(newX);
    else
        player->setPositionX(maxLeft);
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
		break;
	case RIGHT_RELEASE:
		break;
	default:
		break;
	}
}

void Jump::handleUpdate(Player* player, float dt)
{
    static const float jumpStart = player->getPositionY();
	float jumpHeight = player->getPositionY();
	float lastHeight = jumpStart;


	if (jumpHeight > lastHeight) lastHeight = jumpHeight;
	else 
        player->setState(&PlayerState::falling);


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
    static const float jumpMax = player->getPositionY();
    static const float jumpStart = jumpMax - 200;
    float currentY = player->getPositionY();
    float newY = currentY - 4;
    
    if (newY >= jumpStart)
        player->setPositionY(newY);
    else
        player->setState(&PlayerState::idling);
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
		break;
	case RIGHT_RELEASE:
		break;
	default:
		break;
	}
}

void Reload::handleUpdate(Player* player, float dt)
{

}

