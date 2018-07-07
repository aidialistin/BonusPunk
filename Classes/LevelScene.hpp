//
//  LevelScene.hpp
//  MyCppGame
//
//  Created by Lale Kaya on 27.06.18.
//

#ifndef LevelScene_hpp
#define LevelScene_hpp

#include <stdio.h>

#pragma once
#include "cocos2d.h"
#include "CountDown.hpp"
#include "enums.h"
#include "Player.h"

using namespace cocos2d;
USING_NS_CC;

class LevelScene : public Layer
{
public:
    LevelScene(void);
    ~LevelScene(void);
    cocos2d::Label* labelTime;
    CountDown countDown;
    static cocos2d::Scene* createScene(int level);
    virtual void update(float dt) override;
    void playerUpdate(float dt);
    CREATE_FUNC(LevelScene);
    
    virtual bool init() override;
    Vector<SpriteFrame*> getAnimation(const char *format, int count);
    void startGame();
    void stopMusic(float dt);

private:
    CCTMXTiledMap *_tileMap;
    CCTMXLayer *_background;
	Player* _player;
	void initKeyboard();
    void onMouseMove(cocos2d::Event *event);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
    void goToMenu(Ref *pSender);
//	Physics
	cocos2d::PhysicsWorld *sceneWorld;

	void SetPhysicsWorld( cocos2d::PhysicsWorld *world) { sceneWorld = world; };
	bool onContactBegin(cocos2d::PhysicsContact &contact);
    

};

#endif /* LevelScene_hpp */
