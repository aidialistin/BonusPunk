//
//  CountDown.hpp
//  MyCppGame
//
//  Created by Lale Kaya on 24.06.18.
//

#ifndef CountDown_hpp
#define CountDown_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;

class CountDown
{
public:
    CountDown();
    ~CountDown();
    int timeRemaining;
    int min;
    int sec;
    string timer;
    cocos2d::Label* labelTime;

    virtual void update(float dt);
};
#endif /* CountDown_hpp */
