//
//  LevelScene.cpp
//  MyCppGame
//
//  Created by Lale Kaya on 27.06.18.
//

#include "LevelScene.hpp"
#include "CountDown.hpp"

#include "SimpleAudioEngine.h"

#include "HelloWorldScene.h"
#include <string>
#include "Target.hpp"
using namespace std;
USING_NS_CC;
#include "audio/include/AudioEngine.h" USING_NS_CC;
using namespace experimental;


int i;

LevelScene::LevelScene(void)
{
}


LevelScene::~LevelScene(void)
{
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* LevelScene::createScene(int level) {
    
    i = level;
    
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, -900));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = LevelScene::create();
	layer->SetPhysicsWorld( scene->getPhysicsWorld() );
    scene->addChild(layer);
    return scene;
}

bool LevelScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    CountDown countDown = *new CountDown();
    auto size = Director::getInstance()->getWinSize();
   // auto background = Sprite::create("");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (i == 1) {
        LevelScene::level_1();
    } else if (i == 2){
        LevelScene::level_2();
    } else if (i == 3) {
        LevelScene::level_3();
    }
    
    background->setScale(size.width / background->getContentSize().width, size.height / background->getContentSize().height);
    background->setPosition(size.width/2, size.height/2);
    this->addChild(background); // add a background sprite to watch more obviously
    
    auto menu = Label::createWithSystemFont("Zum Menü", "Arial", 24.0);
    auto menuItem = MenuItemLabel::create(menu, CC_CALLBACK_1(LevelScene::goToMenu, this));
    menuItem ->setPosition(Point(size.width / 4, (size.height -50)));
    
    auto menuBtn = Menu::createWithItem(menuItem);
    menuBtn->setPosition(Point(0, 0));
    this->addChild(menuBtn);
    
    labelTime = Label::createWithTTF(countDown.timer, "fonts/arial.ttf", 24);
    if (labelTime == nullptr)
    {
        problemLoading("'fonts/arial.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        labelTime->setPosition(Vec2(size.width/2, size.height-50));
        
        // add the label as a child to this layer
        this->addChild(labelTime, 1);
    }
    
    this->schedule(CC_SCHEDULE_SELECTOR(LevelScene::update), 1.0f);
    this->schedule(CC_SCHEDULE_SELECTOR(LevelScene::playerUpdate));

    // Physics-Teil
    //	Ränder
	auto edgeBody = PhysicsBody::createEdgeBox( size, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	//	Für Collision
	edgeBody->setCollisionBitmask(1);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition( Point( size.width/2 - origin.x , size.height /2 + origin.y) );
	edgeNode->setPhysicsBody( edgeBody );
	this->addChild( edgeNode );

    //	Player
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/images/player_plist.plist");
    auto frames = getAnimation("Player_0%01d.png", 12, 1);
    auto frame = getAnimation("Player_0%01d.png", 1, 1);
    auto framesRight = getAnimation("Player_0%01d.png", 5, 1);
    auto framesLeft = getAnimation("Player_0%01d.png", 10, 6);
    
    _player = Player::createWithSpriteFrame(frames.front());
    _player->setAnchorPoint(Vec2(0,0));//::ZERO);
    _player->setPosition(Vec2(size.width/2 + origin.x, origin.y+200));
    
    _player->idleAnimation = Animation::createWithSpriteFrames(frame, 1.0f/8);
    _player->walkLeftAnimation = Animation::createWithSpriteFrames(framesLeft, 1.0f/8);
    _player->walkRightAnimation = Animation::createWithSpriteFrames(framesRight, 1.0f/8);
   /* _player->runAction(RepeatForever::create(Animate::create(_player->walkRightAnimation)));
    _player->runAction(RepeatForever::create(Animate::create(_player->walkLeftAnimation)));
    _player->runAction(RepeatForever::create(Animate::create(_player->idleAnimation)));*/
    
    _player->idleAnim = RepeatForever::create(Animate::create(_player->idleAnimation));
    _player->leftAnim = RepeatForever::create(Animate::create(_player->walkLeftAnimation));
    _player->rightAnim = RepeatForever::create(Animate::create(_player->walkRightAnimation));
    _player->idleAnim->setTag(1);
    _player->leftAnim->setTag(1);
    _player->rightAnim->setTag(1);
    _player->runAction(_player->leftAnim);
    _player->runAction(_player->rightAnim);
    _player->runAction(_player->idleAnim);

    this->addChild(_player, 0);
   // _player->playAnimation(_player->walkRightAnimation);
   // _player->playAnimation(_player->idleAnimation);
    
    _player2 = Player::createWithSpriteFrame(frames.front());
    _player2->setAnchorPoint(Vec2::ZERO);
    _player2->setPosition(Vec2(20, origin.y));
   
	auto spriteRectBody = PhysicsBody::createBox(_player->getContentSize(), PhysicsMaterial( 0, 1, 0));
    spriteRectBody-> setRotationEnable(false);
    auto spriteRectBody2 = PhysicsBody::createBox(_player2->getContentSize(), PhysicsMaterial( 0, 1, 0));
    spriteRectBody2-> setRotationEnable(false);
	_player->setPhysicsBody( spriteRectBody );
    _player2->setPhysicsBody( spriteRectBody2 );
   
	// Für Collision
	spriteRectBody->setCollisionBitmask(2);
	spriteRectBody->setContactTestBitmask(true);
    //spriteRectBody->setCategoryBitmask(0);
    spriteRectBody2->setCollisionBitmask(3);
    spriteRectBody2->setContactTestBitmask(true);
    spriteRectBody2->setCategoryBitmask(1);

    
    this->addChild(_player2, 0);
	this->initKeyboard();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(LevelScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    _hussi1 = Target::create("res/images/hussi.png");
    _hussi1->_alive = true;
    _hussi1->_lifePoints = 2;
    this->addChild(_hussi1);
    _hussi1->setPosition(200,350);
    //_hussi1->move(size);
   
    return true;
}

void LevelScene::update(float dt){
    countDown.update(dt);
    labelTime->setString(countDown.timer);
}

void LevelScene::playerUpdate(float dt)
{
    _player->updatePlayer(dt);
   // _player2->updatePlayer(dt);
}

bool LevelScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
    PhysicsBody *c = contact.getShapeB()->getBody();

	//check for Collision
	if ((a->getCollisionBitmask() != b->getCollisionBitmask()) || (a->getCollisionBitmask() != c->getCollisionBitmask()) || (b->getCollisionBitmask() != c->getCollisionBitmask()))
    {
        if (a->getCollisionBitmask()==5 && b->getCollisionBitmask()==2) {
            CCLOG("collision");
            _hussi1->kill();
        }
        return true;
	}
	else {
		return false;
	}
    
}

void LevelScene::level_1()
{
    LevelScene::background = Sprite::create("res/images/background_1.png");
    auto audioFile = "res/audio/level1.m4a";
    auto audioId = AudioEngine::play2d(audioFile);
    AudioEngine::setLoop(audioId, true);
    AudioEngine::setVolume(audioId, 0.1);
}

void LevelScene::level_2()
{
    background = Sprite::create("res/images/background_2.jpg");
    auto audioFile = "res/audio/BoulderDash.mp3";
    auto audioId = AudioEngine::play2d(audioFile);
    AudioEngine::setLoop(audioId, true);
    AudioEngine::setVolume(audioId, 0.1);
}

void LevelScene::level_3()
{
    background = Sprite::create("res/images/background_3.jpg");
}

void LevelScene::initKeyboard()
{
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(LevelScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(LevelScene::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void LevelScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
    switch(key)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            //_player->runAction(Animate::create(_player->walkLeftAnimation));
            _player->input(Input::LEFT_PRESS);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            _player->input(Input::RIGHT_PRESS);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            _player->input(Input::JUMP_PRESS);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
            _player->input(Input::SHOOT_PRESS);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            _player2->input(Input::LEFT_PRESS);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            _player2->input(Input::RIGHT_PRESS);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            _player2->input(Input::JUMP_PRESS);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
            _player2->input(Input::SHOOT_PRESS);
            break;
        default:
            break;
    }
}

void LevelScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
	switch (key)
	{
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            _player->input(Input::LEFT_RELEASE);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            _player->input(Input::RIGHT_RELEASE);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            _player->input(Input::JUMP_RELEASE);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
            _player->input(Input::SHOOT_RELEASE);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            _player2->input(Input::LEFT_RELEASE);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            _player2->input(Input::RIGHT_RELEASE);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            _player2->input(Input::JUMP_RELEASE);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
            _player2->input(Input::SHOOT_RELEASE);
            break;
        default:
            break;
	}
}

void LevelScene::goToMenu(cocos2d::Ref *pSender)
{
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
    AudioEngine::pauseAll();
}

Vector<SpriteFrame*> LevelScene::getAnimation(const char * format, int count, int i)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    for(i; i <= count; i++)
    {
        string str = StringUtils::format("Player_0%01d.png", i);
        //animFrames.pushBack(spritecache->getSpriteFrameByName(str));
        SpriteFrame* frame = spritecache->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    return animFrames;
}


