#pragma once
#include <cocos2d.h>
#include <ui/CocosGUI.h>
using namespace cocos2d::ui;

USING_NS_CC;
class RulesLayer : public Layer {
public:
	CREATE_FUNC(RulesLayer);
	virtual bool init();
	EventListenerTouchOneByOne*  listener;


	ImageView* button1;
	ImageView* button2;
	Button*  f1;
	Button*  h2;
	bool onTouchBegan(Touch * touch, Event * event);
	//�ر�
	void closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	//��ҳ1
	void fButtonClicked1(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	//��ҳ2
	void fButtonClicked2(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
};
