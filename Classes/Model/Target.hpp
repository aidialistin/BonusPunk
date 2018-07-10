//
//  Target.hpp
//  MyCppGame
//
//  Created by Aida Bakhtiari on 10.07.18.
//

#ifndef Target_hpp
#define Target_hpp

#include <stdio.h>
using namespace cocos2d;

class Target : public cocos2d::Sprite
{
public:
    int _lifePoints;
    static Target* create(const std::string& filename);
    bool _alive;
    void move(Size windowsize);
    void kill();
};
#endif /* Target_hpp */
