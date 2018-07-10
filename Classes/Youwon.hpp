//
//  Youwon.hpp
//  MyCppGame
//
//  Created by Aida Bakhtiari on 10.07.18.
//

#ifndef Youwon_hpp
#define Youwon_hpp

#include <stdio.h>
#endif /* Youwon_hpp */


#include "cocos2d.h"
#include <stdio.h>

using namespace std;

class Youwon : public cocos2d::Scene
{
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Youwon);
    cocos2d::Sprite *mySprite;
    
    void goToMenu(Ref *pSender);
};

