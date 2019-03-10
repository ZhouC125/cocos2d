#pragma once
#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include "CardGame.h"
using namespace cocos2d::ui;
USING_NS_CC;
class ProgressLayer :public Scene
{
public:
	static ProgressLayer* scene();

	CREATE_FUNC(ProgressLayer);
	virtual bool init();
	EventListenerTouchOneByOne*  listener;
	//bool onTouchBegan(Touch *touch, Event *event);
	int time = 0;
	Sprite* bg;
	CardGame*game;
private:


	void  doi();
	void updateReadyTimer(float delta);

	Vector<SpriteFrame *> getSpriteFrame(const char *format, int count);
};
