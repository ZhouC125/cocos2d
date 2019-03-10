
#pragma once
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include "CardGame.h"

using namespace cocos2d;
using namespace cocos2d::ui;
USING_NS_CC;
class SetLayer : public Layer {
public:
	CREATE_FUNC(SetLayer);
	virtual bool init();
	EventListenerTouchOneByOne*  listener;
	bool onTouchBegan(Touch *touch, Event *event);
	void  closeButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void Zhuxiao(Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	CardGame*game;


	Button* btn_off;
	Button* btn_no;
	void yinxiao(Ref * sender, cocos2d::ui::Widget::TouchEventType type);
};
