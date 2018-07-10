//
//  Bullet.hpp
//  MyCppGame
//
//  Created by Lale Kaya on 08.07.18.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>

class Bullet : public cocos2d::Sprite
{
public:
    static Bullet* create(const std::string& filename);

};
#endif /* Bullet_hpp */
