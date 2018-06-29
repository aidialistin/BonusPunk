#include "PlayerState.h"

USING_NS_CC;

Idle PlayerState::idling;
WalkLeft PlayerState::goingLeft;
WalkRight PlayerState::goingRight;
Jump PlayerState::jumping;
Fall PlayerState::falling;

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
//		player->setState(&PlayerState::jumping);
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

}


void WalkRight::handleInput(Player* player, Input input)
{
	switch (input)
	{
	case JUMP_PRESS:
//		player->setState(&PlayerState::jumping);
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

}


void Jump::handleInput(Player* player, Input input)
{
	switch (input)
	{
	case JUMP_PRESS:
//		player->setState(&PlayerState::jumping);
		break;
	case JUMP_RELEASE:
		player->setState(&PlayerState::idling);
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

}




void Fall::handleInput(Player* player, Input input)
{
	switch (input)
	{
	case JUMP_PRESS:
//		player->setState(&PlayerState::jumping);
		break;
	case JUMP_RELEASE:
		player->setState(&PlayerState::idling);
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

}
