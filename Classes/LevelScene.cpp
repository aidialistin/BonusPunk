//
//  LevelScene.cpp
//  MyCppGame
//
//  Created by Lale Kaya on 27.06.18.
//

#include "LevelScene.hpp"
#include "CountDown.hpp"
#include "SimpleAudioEngine.h"



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

Scene* LevelScene::createScene() {
    auto scene = Scene::create();
    
    auto layer = LevelScene::create();
    
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
    auto background = Sprite::create("res/images/testbackground.PNG");
    
    
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
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/audio/beat.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("res/audio/beat.mp3",true);//true loops
    this->schedule(schedule_selector(LevelScene::stopMusic), 1);// seconds after to stop 
    return true;
}

void LevelScene::update(float dt){
    countDown.update(dt);
    labelTime->setString(countDown.timer);
}


void LevelScene::stopMusic(float dt){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("res/audio/beat.mp3");
}
