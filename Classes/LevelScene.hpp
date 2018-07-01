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
    CREATE_FUNC(LevelScene);
    
    virtual bool init() override;
    
    void startGame();
    
};

#endif /* LevelScene_hpp */
