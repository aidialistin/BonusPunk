/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CountDown.hpp"
#include "LevelScene.hpp"
#include <vector>

#include <string>
using namespace std;
using namespace cocos2d;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto bGColor = cocos2d::LayerColor::create(Color4B(53, 103, 183, 255));
    this->addChild(bGColor);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/images/player_plist.plist");
   
    auto background = Sprite::createWithSpriteFrameName("res/images/testbackground.png");
    background->setPosition(origin.x + 200,origin.y + 200/2);
    this->addChild(background);
    //Vector<SpriteFrame*>  frames = getAnimation("res/images/Layer 1_sprite_%01d.png", 8);
    auto frames = getAnimation("Layer 1_sprite_0%01d.png", 8);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    this->addChild(sprite);
    sprite->setPosition(100,620);
    
    auto animation = Animation::createWithSpriteFrames(frames, 1.0f/8);
    sprite->runAction(RepeatForever::create(Animate::create(animation)));


    mySprite = Sprite::create("res/images/player_plist.png");
    
    mySprite->setPosition(Point((visibleSize.width/2) + origin.x, (visibleSize.height/2) + origin.y));
    auto action=MoveBy::create(3,Point(100,10));
    mySprite->runAction(EaseBounceIn::create(action));
    this->addChild(mySprite); */
    

    auto start = Label::createWithSystemFont("Start", "Arial", 30.0);
    auto level1 = Label::createWithSystemFont("Level1", "Arial", 20.0);
    auto level2 = Label::createWithSystemFont("Level2", "Arial", 20.0);
    auto level3 = Label::createWithSystemFont("Level3", "Arial", 20.0);
    auto startMenuItem = MenuItemLabel::create(start, CC_CALLBACK_1(HelloWorld::Play, this));
    auto level2MenuItem = MenuItemLabel::create(level2, CC_CALLBACK_1(HelloWorld::levelAdd, this));
    auto level3MenuItem = MenuItemLabel::create(level3, CC_CALLBACK_1(HelloWorld::levelDrei, this));
    auto level4MenuItem = MenuItemLabel::create(level1, CC_CALLBACK_1(HelloWorld::levelEins, this));

	// Menü-Label Positionen    
    startMenuItem ->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4-10) * 3));
    level2MenuItem->setPosition(Point(visibleSize.width / 2 , (visibleSize.height / 2)));
    level3MenuItem->setPosition(Point(visibleSize.width / 2 + 100, (visibleSize.height / 2)));
    level4MenuItem ->setPosition(Point(visibleSize.width / 2-100 , (visibleSize.height / 2)));

    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("close.png", "close.png",CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'close24.png' and 'close36.png'");
    }
    else
    {
        float xPosCloseItem = origin.x + visibleSize.width/2 - closeItem->getContentSize().width/2 +10;
        float yPosCloseItem = origin.y + closeItem->getContentSize().height;
        closeItem->setPosition(Vec2(xPosCloseItem,yPosCloseItem));
    }

    auto *menu = Menu::create(startMenuItem,level4MenuItem , level2MenuItem, level3MenuItem,closeItem, NULL);
    menu->setPosition(Point(0, 0));
    
    this->addChild(menu);

    /////////////////////////////
    // 3. add your codes below...



    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("B O N U S", "fonts/arial.ttf", 34);
    label->setColor(Color3B(117, 209, 234));
    if (label == nullptr)
    {
        problemLoading("'fonts/arial.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    return true;
    
}// ende intit


void HelloWorld::Play(cocos2d::Ref *pSender)
{
    CCLOG("Play");
}

void HelloWorld::levelDrei(cocos2d::Ref *pSender)
{
    auto scene = LevelScene::createScene(3);
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}

void HelloWorld::levelAdd(cocos2d::Ref *pSender)
{
    auto scene = LevelScene::createScene(2);
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}

void HelloWorld::levelEins(cocos2d::Ref *pSender)
{
    //auto scene = Scene::create();
    auto scene = LevelScene::createScene(1);
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}



    // add "HelloWorld" splash screen"
/*    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }*/

    //this->schedule(SEL_SCHEDULE(&CountDown::update), 1.0f);
 //   this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::update), 1.0f);
   // return true;

//}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
Vector<SpriteFrame*> HelloWorld::getAnimation(const char * format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    for(int i = 1; i <= count; i++)
    {
        string str = StringUtils::format("Layer 1_sprite_0%01d.png", i);
        //animFrames.pushBack(spritecache->getSpriteFrameByName(str));
        SpriteFrame* frame = spritecache->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
       
    }
    return animFrames;
}

