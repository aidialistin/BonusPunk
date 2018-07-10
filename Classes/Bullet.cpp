//
//  Bullet.cpp
//  MyCppGame
//
//  Created by Lale Kaya on 08.07.18.
//

#include "Bullet.hpp"
#include "cocos2d.h"

Bullet* Bullet::create(const std::string& filename)
{
    Bullet *bullet = new (std::nothrow) Bullet();
    if (bullet && bullet->initWithFile(filename))
    {
        bullet->autorelease();
        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return nullptr;
}
