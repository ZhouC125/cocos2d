#pragma once
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include "CardGame.h"
using namespace cocos2d::ui;

USING_NS_CC;
class TaskLayer : public Layer {
public:
	CREATE_FUNC(TaskLayer);
	virtual bool init();
	EventListenerTouchOneByOne*  listener;

	bool onTouchBegan(Touch * touch, Event * event);


	ui::EditBox * userNameText;
	CardGame*game;
	Sprite*got1;
	Sprite*got2;
	Sprite*got3;
	Sprite*got4;

	Button*button1;
	Button*button2;
	Button*button3;
	Button*button4;

	//¹Ø±Õ
	void closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);

	void getButtonClicked1(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
};
