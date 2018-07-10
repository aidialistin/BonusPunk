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
    
    
    if (i == 1) {
        background = Sprite::create("res/images/background_1.png");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/audio/level1.m4a");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("res/audio/level1.m4a",true);//true loops
        this->schedule(schedule_selector(LevelScene::stopMusic), 1);// seconds after to stop

       // _tileMap = new CCTMXTiledMap();
        //_tileMap->initWithTMXFile("res/images/deine_mama.tmx");
        //_background = _tileMap->layerNamed("Kachelebene1");
        //this->addChild(_tileMap);
    } else if (i == 2){
        background = Sprite::create("res/images/background_2.jpg");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/audio/lachen.m4a");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("res/audio/lachen.m4a",true);//true loops
        
    } else if (i == 3) {
        background = Sprite::create("res/images/background_3.jpg");
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
    
    auto toMenu = Label::createWithSystemFont("Zum Menü", "Arial", 24.0);
    auto toMenuItem = MenuItemLabel::create(toMenu, CC_CALLBACK_1(LevelScene::goToMenu, this));
    menuItem ->setPosition(Point(size.width / 4, (size.height -50)));
    
    auto toMenuBtn = Menu::createWithItem(toMenuItem);
    toMenuBtn->setPosition(Point(0, 0));
    this->addChild(toMenuBtn);
    
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
    _player->setAnchorPoint(Vec2::ZERO);
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

    
   // _player->playAnimation(_player->walkRightAnimation);
   // _player->playAnimation(_player->idleAnimation);
    this->addChild(_player, 0);
    
   // _player2 = Player::createWithSpriteFrame(frames.front());
   // _player2->setAnchorPoint(Vec2::ZERO);
   // _player2->setPosition(Vec2(20, origin.y));
   
	auto spriteRectBody = PhysicsBody::createBox(_player->getContentSize(), PhysicsMaterial( 0, 1, 0));
    spriteRectBody-> setRotationEnable(false);
   // auto spriteRectBody2 = PhysicsBody::createBox(_player2->getContentSize(), PhysicsMaterial( 0, 1, 0));
   // spriteRectBody2-> setRotationEnable(false);
	_player->setPhysicsBody( spriteRectBody );
    //_player2->setPhysicsBody( spriteRectBody2 );
   
	// Für Collision
	spriteRectBody->setCollisionBitmask(2);
	spriteRectBody->setContactTestBitmask(true);
   // spriteRectBody->setCategoryBitmask(0);
  //  spriteRectBody2->setCollisionBitmask(3);
    //spriteRectBody2->setContactTestBitmask(true);
    //spriteRectBody2->setCategoryBitmask(1);

	//this->addChild(_player, 0);
  //  this->addChild(_player2, 0);
	this->initKeyboard();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(LevelScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    // score
    score=0;
 
    
   //  int randomX = arc4random() % 600 + 1;
   //  int randomY = arc4random() % 300 + 1;
    
    auto myHussi = Sprite::create("res/images/hussi.png");
    // auto spritebody =   PhysicsBody::createCircle(seq->getContentSize().width/2,PhysicsMaterial(0,1,0));
    myHussi->setPosition(Point(15,400));
    auto moveBy = MoveBy::create(3, Vec2(412,10));//MoveBy::create(5, Vec2(12,40));
    auto delay = DelayTime::create(1);
    auto moveTo = MoveTo::create(3, Vec2(1212,400));
    auto seq = Sequence::create(moveBy, delay, moveTo, nullptr);
 
    auto seqBack =moveBy->reverse();
    auto scaleBy = ScaleBy::create(1.5f, 1.5f, 1.0f);
    
    auto moveBy2 = MoveTo::create(3, Vec2(15,100));//MoveBy::create(5, Vec2(12,40));
    auto delay2 = DelayTime::create(1);
    auto moveTo2 = MoveTo::create(3, Vec2(15,100));
    auto seq2 = Sequence::create(moveBy2, delay2, moveTo2, nullptr);
    auto rotateTo2 = RotateTo::create(5.0f, 1.0f);
    
    
    
    myHussi->runAction(seq);
   
    myHussi->runAction(scaleBy);
    auto rotateTo = RotateTo::create(1.0f, 5.0f);
    myHussi->runAction(rotateTo);
     myHussi->runAction(seq2);
    
    auto myHussi2 = Sprite::create("res/images/hussi.png");
    // auto spritebody =   PhysicsBody::createCircle(seq->getContentSize().width/2,PhysicsMaterial(0,1,0));
    myHussi2->setPosition(Point(1215,100));
    
    myHussi2->runAction(RepeatForever::create(seq2));
    myHussi2->runAction(scaleBy);
    myHussi2->runAction(rotateTo2);
 myHussi2->runAction(seqBack);
    
    this->addChild(myHussi2);
    
       this->addChild(myHussi);
    
    
   
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
   /* ValueMap properties = _tileMap->getProperties();
    Value collision = properties["Collidable"];
    if (!collision.isNull()) {
        CCLOG("COLLISION WITH LAYER");
    } else {
        CCLOG("NO COLLISION");
    }*/
}

bool LevelScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
    PhysicsBody *c = contact.getShapeB()->getBody();

	//check for Collision
	//if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
	if ((a->getCollisionBitmask() != b->getCollisionBitmask()) || (a->getCollisionBitmask() != c->getCollisionBitmask()) || (b->getCollisionBitmask() != c->getCollisionBitmask()))
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


void LevelScene::stopMusic(float dt){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("res/audio/beat.mp3");
}
