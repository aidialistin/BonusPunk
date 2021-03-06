//
//  Target.cpp
//  MyCppGame
//
//  Created by Aida Bakhtiari on 10.07.18.
//

#include "Target.hpp"
#include "audio/include/AudioEngine.h" USING_NS_CC;
using namespace experimental;

using namespace cocos2d;

Target* Target::create(const std::string& filename)
{
    Target *target_hussi = new (std::nothrow) Target();
    
    if (target_hussi && target_hussi->initWithFile(filename))
    {
        target_hussi->autorelease();
        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        auto spritebody = PhysicsBody::createCircle(target_hussi->getContentSize().width/2,PhysicsMaterial(0,1,0));
        spritebody->setGravityEnable(false);
        spritebody->setCollisionBitmask(5);
        spritebody->setContactTestBitmask(true);
        target_hussi->setPhysicsBody(spritebody);
        return target_hussi;
    }
    CC_SAFE_DELETE(target_hussi);
    return nullptr;
}

void Target::move(Size windowsize)
{
    auto x = this->getPosition().x;
    auto y = this->getPosition().y;
    
    //while(this->_alive){
        if(x<windowsize.width){
            x=x+1280;
            auto delay = DelayTime::create(3);
            auto moveTo = MoveTo::create(3, Vec2(x,y));
            auto rotateTo2 = RotateTo::create(5.0f, 1.0f);
            auto scaleBy = ScaleBy::create(1.5f, 1.5f, 1.0f);
            auto seq = Sequence::create(moveTo, delay, nullptr);
            runAction(seq);
        } else {
            x=0;
            auto delay = DelayTime::create(3);
            auto moveTo = MoveTo::create(3, Vec2(x,y));
            auto seq = Sequence::create(moveTo, delay, nullptr);
            runAction(seq);
        }
   // }
}

void Target::kill()
{
    _lifePoints -= 1;
  auto audioFile = "res/audio/explosion.m4a";
     auto audioId = AudioEngine::play2d(audioFile);
    AudioEngine::setLoop(audioId, false);
 /*     //Animation + Sound
    CCLOG("weiss");
     CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("res/audio/level1.m4a");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("res/audio/explosion.m4a");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/audio/explosion.m4a",false);//true loops
 
     CCLOG("du was");*/
    if(_lifePoints==0){
        this->removeFromParent();
    }
}
