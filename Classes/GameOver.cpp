//
//  GameOver.cpp
//  MyCppGame
//
//  Created by Lale Kaya on 27.06.18.
//

#include "GameOver.hpp"
#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    return GameOver::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto bGColor = cocos2d::LayerColor::create(Color4B(53, 103, 183, 255));
    this->addChild(bGColor);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto gameOver = Label::createWithSystemFont("GAME OVER", "Arial", 30.0);
    auto menu = Label::createWithSystemFont("Zum Menü", "Arial", 20.0);
    auto menuItem = MenuItemLabel::create(menu, CC_CALLBACK_1(GameOver::goToMenu, this));
    
    gameOver->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4-10) * 3));
    menuItem->setPosition(Point(visibleSize.width / 2 , (visibleSize.height / 2)));
    
    auto closeItem = MenuItemImage::create("close.png", "close.png",CC_CALLBACK_1(GameOver::menuCloseCallback, this));
    
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
    
    auto gameOverMenu = Menu::createWithItem(menuItem);
    gameOverMenu->setPosition(Point(0, 0));
    
   this->addChild(gameOverMenu);

    
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
    
    auto labelGameOver = Label::createWithTTF("GAME OVER", "fonts/arial.ttf", 25);
    labelGameOver->setColor(Color3B(117, 209, 234));
    if (labelGameOver == nullptr)
    {
        problemLoading("'fonts/arial.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        labelGameOver->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/1.5 - label->getContentSize().height));
        
        // add the label as a child to this layer
        this->addChild(labelGameOver, 1);
    }
    return true;
    
}

void GameOver::goToMenu(cocos2d::Ref *pSender)
{
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}

void GameOver::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
 
}



