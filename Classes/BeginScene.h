#pragma once
#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include "CardGame.h"
using namespace cocos2d::ui;
USING_NS_CC;
class BeginScene :public Scene
{
public:
	static BeginScene* scene();

	CREATE_FUNC(BeginScene);
	virtual bool init();
	EventListenerTouchOneByOne*  listener;
	//bool onTouchBegan(Touch *touch, Event *event);
	int time = 0;
	Sprite* bg;

private:


	void  doi();
	void updateReadyTimer(float delta);

	Vector<SpriteFrame *> getSpriteFrame(const char *format, int count);
};
