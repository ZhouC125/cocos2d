#pragma once
#include <cocos2d.h>
#include <ui/CocosGUI.h>
using namespace cocos2d::ui;

USING_NS_CC;
class MailboxLayer : public Layer {
public:
	CREATE_FUNC(MailboxLayer);
	virtual bool init();
	EventListenerTouchOneByOne*  listener;

	bool onTouchBegan(Touch * touch, Event * event);
	//¹Ø±Õ
	void closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);

	ImageView* g1;
	ImageView* g2;
	ImageView* g3;
	ImageView*xuanzhe1;
	ImageView*xuanzhe2;
	ImageView*xuanzhe3;
	void fButtonClicked1(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void fButtonClicked2(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void fButtonClicked3(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
};
