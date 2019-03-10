#pragma once
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include "CardGame.h"
using namespace cocos2d::ui;

USING_NS_CC;
class Feedback : public Layer {
public:
	CREATE_FUNC(Feedback);
	virtual bool init();
	EventListenerTouchOneByOne*  listener;

	bool onTouchBegan(Touch * touch, Event * event);
	//¹Ø±Õ
	void closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	void  submitButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	ui::EditBox * userNameText;
	CardGame*game;
};
