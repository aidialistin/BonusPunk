//
//  CountDown.cpp
//  MyCppGame
//
//  Created by Lale Kaya on 24.06.18.
//

#include "CountDown.hpp"
#include "SimpleAudioEngine.h"
#include "GameOver.hpp"
#include "Youwon.hpp"



using namespace std;

CountDown::CountDown(){
    timeRemaining = 20;
    min = ceil(timeRemaining / 60);
    sec = timeRemaining % 60;
    if (sec < 10){
        timer = (to_string(min) + ":0" + to_string(sec));
    } else {
        timer = (to_string(min) + ":" + to_string(sec));
    }
}

CountDown::~CountDown(){}

void CountDown::update(float dt) {
    if (timeRemaining > 0.f) {
        timeRemaining -= dt;
        min = ceil(timeRemaining / 60);
        sec = timeRemaining % 60;
        if (sec < 10){
            timer = (to_string(min) + ":0" + to_string(sec));
        } else {
            timer = (to_string(min) + ":" + to_string(sec));
        }
        
        if (timeRemaining <= 0.f) {
          //  auto scene = GameOver::createScene();
            auto scene =Youwon::createScene();
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionCrossFade::create(0.5, scene));
        }
    }
}


