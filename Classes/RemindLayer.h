#pragma once
#include <cocos2d.h>
#include <ui/CocosGUI.h>
using namespace cocos2d::ui;

USING_NS_CC;
class RemindLayer : public Layer {
public:
	CREATE_FUNC(RemindLayer);
	virtual bool init();
	EventListenerTouchOneByOne*  listener;


	Button*  f1;
	Button*  h2;
	bool onTouchBegan(Touch * touch, Event * event);
	//关闭
	void closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	//返回界面
	void closeButtonClicked1(Ref * sender, cocos2d::ui::Widget::TouchEventType type);
};
