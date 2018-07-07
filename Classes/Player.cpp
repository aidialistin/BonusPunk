//	PlayerSprite.cpp
//	
// 	Created by Jan Gabriel on 28.06.10.
//

#include "Player.h"
#include "enums.h"

Player* Player::createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame)// (const std::string& filename)
{
    Player *player = new (std::nothrow) Player();
    if (player && player->initWithSpriteFrame(spriteFrame)) //&& player->initWithFile(filenamme))
    {
        player->autorelease();
        player->setState(&PlayerState::idling);
        player->shootAllowed = true;
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

void Player::updatePlayer(float dt)
{
    _state->handleUpdate(this, dt);
    auto mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(Player::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}
/*
 void Player::update(float dt, bool colliion)
 {
 _state->handleUpdate(this, dt, collision);
 }
 */

void Player::shoot(){
    if (shootAllowed){
        auto bullet = create("close24.png");
        bullet->setPosition(100, 100);
        
        auto bulletBody = cocos2d::PhysicsBody::createBox( bullet->getContentSize());
        bullet->setPhysicsBody( bulletBody );
        bulletBody-> setRotationEnable(false);
        
        // Für Collision
        bulletBody->setCollisionBitmask(2);
        bulletBody->setContactTestBitmask(true);
        
        this->addChild(bullet, 0);
        //cocos2d::Point a = cocos2d::Point(300, 100);
        auto moveTo = cocos2d::MoveTo::create(1.0f, _target);
        auto delay = cocos2d::DelayTime::create( 0.1f );
        auto remove = cocos2d::CallFunc::create( [bullet](){bullet->removeFromParent();});
        auto action1 = cocos2d::Sequence::create(moveTo, delay, remove, nullptr );
        bullet->runAction(action1);
        shootAllowed = false;
    }
}

void Player::onMouseMove(cocos2d::Event *event)
{
    cocos2d::EventMouse* e = (cocos2d::EventMouse*)event;
    _target = cocos2d::Point(e->getCursorX(), e->getCursorY()); //(e->getLocation());
}
