//	PlayerSprite.cpp
//	
// 	Created by Jan Gabriel on 28.06.10.
//

#include "Player.h"
#include "enums.h"

Player* Player::create(const std::string& filename)
{
	Player *player = new (std::nothrow) Player();
	if (player && player->initWithFile(filename))
	{
		player->autorelease();
		player->setState(&PlayerState::idling);
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

void Player::setState(PlayerState* state)
{
	_state = state;
	CCLOG("New State %s", getStateName());
}

const PlayerState* Player::getState() const
{
	return _state;
}

const char* Player::getStateName() const
{
	return typeid(*_state).name();
}

void Player::input(Input input)
{
	_state->handleInput(this, input);
}

void Player::update(float dt)
{
    _state->handleUpdate(this, dt);
    //auto mouseListener =  cocos2d::EventListenerMouse::create();
    //mouseListener->onMouseMove = CC_CALLBACK_1(Player::onMouseMove, this);
}
/*
void Player::update(float dt, bool colliion)
{
	_state->handleUpdate(this, dt, collision);
}
*/

void Player::shoot(){
    auto mouseListener =  cocos2d::EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(Player::onMouseMove, this);
    auto bullet = create("close24.png");
    bullet->setPosition(100,100);
    this->addChild(bullet);
    cocos2d::Point b = cocos2d::Point(200, 100);
    auto moveTo = cocos2d::MoveTo::create(1.0f, b);
    auto delay = cocos2d::DelayTime::create( 0.1f );
    auto remove = cocos2d::CallFunc::create( [bullet](){bullet->removeFromParent();});
    auto action1 = cocos2d::Sequence::create(moveTo, delay, remove, nullptr );
    bullet->runAction(action1);

}

void Player::onMouseMove(cocos2d::Event *event)
{
    CCLOG("moving");
    /*cocos2d::EventMouse* e = (EventMouse*)event;
    std::string str = "MousePosition X:";
    str = str + tostr(e->getCursorX()) + " Y:" + tostr(e->getCursorY());*/
}
