//
//  LevelScene.cpp
//  MyCppGame
//
//  Created by Lale Kaya on 27.06.18.
//

#include "LevelScene.hpp"
#include "CountDown.hpp"
#include <string>
using namespace std;
USING_NS_CC;

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
    auto background = Sprite::create("");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/images/player.png");
    
    if (i == 1) {
        background = Sprite::create("res/images/testbackground.PNG");
    } else if (i == 2){
        background = Sprite::create("res/images/background_2.jpg");
    } else if (i == 3) {
        background = Sprite::create("res/images/background_3.jpg");
    }
    
    background->setScale(size.width / background->getContentSize().width, size.height / background->getContentSize().height);
    background->setPosition(size.width/2, size.height/2);
    this->addChild(background);    // add a background sprite to watch more obviously
    
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
	_player = Player::create("res/images/ourGuy.png");
	_player->setAnchorPoint(Vec2::ZERO);
	_player->setPosition(Vec2(size.width/2 + origin.x, origin.y)); 

	auto spriteRectBody = PhysicsBody::createBox( _player->getContentSize( ), PhysicsMaterial( 0, 0, 0));
	_player->setPhysicsBody( spriteRectBody );
	spriteRectBody-> setRotationEnable(false);

	// Für Collision
	spriteRectBody->setCollisionBitmask(2);
	spriteRectBody->setContactTestBitmask(true);


	this->addChild(_player, 0);
	this->initKeyboard();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(LevelScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}

void LevelScene::update(float dt){
    countDown.update(dt);
    labelTime->setString(countDown.timer);
}

void LevelScene::playerUpdate(float dt)
{
    _player->update(dt);
}

bool LevelScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	//check for Collision
	if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
	{
		return true;
	}
	else {
		return false;
	}
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
	default:
		break;
	}
}

