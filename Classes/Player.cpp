//	PlayerSprite.cpp
//	
// 	Created by Jan Gabriel on 28.06.10.
//
#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif
#include "Player.h"
#include "enums.h"
#include "LevelScene.hpp"
#include "cocos2d.h"

Player* Player::createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame)// (const std::string& filename)
{
    Player *player = new (std::nothrow) Player();
    if (player && player->initWithSpriteFrame(spriteFrame)) //&& player->initWithFile(filenamme))
    {
        player->autorelease();
        player->setState(&PlayerState::idling);
        player->shootAllowed = true;
        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
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
    //this->playAnimation();
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
        auto bullet = Bullet::create("close24.png");
        bullet->setAnchorPoint(Vec2::ZERO);
        bullet->setPosition(0,0);//this->origin.x, this->origin.y);
        
        auto bulletBody = cocos2d::PhysicsBody::createBox(bullet->getContentSize());
        bulletBody->setGravityEnable(false);
        
        bullet->setPhysicsBody(bulletBody );
        bulletBody-> setRotationEnable(false);
        
        // Für Collision
        bulletBody->setCollisionBitmask(2); //4
        bulletBody->setContactTestBitmask(true);
        
        this->addChild(bullet, 0);
        auto moveBy = cocos2d::MoveBy::create(1.0f, _target);
        auto delay = cocos2d::DelayTime::create( 0.1f );
        auto b = bullet;
        auto remove = cocos2d::CallFunc::create( [b](){b->removeFromParent();});
        auto action1 = cocos2d::Sequence::create(moveBy, delay, remove, nullptr );
        bullet->runAction(action1);
        shootAllowed = false;
    }
}

void Player::onMouseMove(cocos2d::Event *event)
{
    cocos2d::EventMouse* e = (cocos2d::EventMouse*)event;
    auto mouseX = e->getLocation().x;
    auto mouseY = 640 - e->getLocation().y;
    auto vec = Vec2(mouseX, mouseY)-this->getPosition();//e->getLocation() - this->getPosition();
   // CCLOG("x: %f y: %f", mouseX, mouseY);
    auto distance = 500;
    auto shootAngle = vec.getAngle();
   // auto degrees = CC_RADIANS_TO_DEGREES(shootAngle);
    //CCLOG("%f", degrees);
    float x1 = distance * (cos(shootAngle));
    float y1 = distance * (sin(shootAngle));

    _target = Vec2(x1, y1);
}

void Player::playAnimation(){
    
    //this->getActionManager()->removeActionByTag(1, this);
    if (this->getState() == &PlayerState::idling){
        getActionManager()->removeAllActions();// pauseAllRunningActions();
        //this->getActionManager()->resumeTarget(this);
        //runAction(this->idleAnim);
        runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(this->idleAnimation)));
    } else if (this->getState() == &PlayerState::goingLeft){
        //runAction(this->leftAnim);
        getActionManager()->pauseAllRunningActions();
        runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(this->walkLeftAnimation)));
    } else if (this->getState() == &PlayerState::goingRight) {
        runAction(this->rightAnim);
        //runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(this->walkRightAnimation)));
    } else {
        runAction(this->idleAnim);
        //runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(this->idleAnimation)));
    }
    
}
