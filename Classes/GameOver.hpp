//
//  GameOver.hpp
//  MyCppGame
//
//  Created by Lale Kaya on 27.06.18.
//

#ifndef GameOver_hpp
#define GameOver_hpp
#include "cocos2d.h"
#include <stdio.h>

using namespace std;

class GameOver : public cocos2d::Scene
{
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);
    cocos2d::Sprite *mySprite;

    void goToMenu(Ref *pSender);
};
#endif /* GameOver_hpp */
