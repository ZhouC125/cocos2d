#pragma once
#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include "CardGame.h"
using namespace cocos2d::ui;
USING_NS_CC;
class DengluScene :public Scene
{
public:
	static DengluScene* scene();

	CREATE_FUNC(DengluScene);
	virtual bool init();
	EventListenerTouchOneByOne*  listener;
	//bool onTouchBegan(Touch *touch, Event *event);
	int time = 0;
	Sprite* bg;
	//帮助
	Sprite*bangzhu;
	Button* button4;
	CardGame*game;
private:
	 void Zhuce(Object *pSender, cocos2d::ui::Widget::TouchEventType type);

	//单机按钮
	void singleButtonClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	//关闭单机按钮
	void  closeButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	//关闭单机按钮
	void  danji(Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	//
	void Denglu(Object *pSender, TouchEventType type);
	
	//login
	void loginingButtonClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	/*void guizhe(Ref *sender, cocos2d::ui::Widget::TouchEventType type);*/

	void jump1(Ref * it, cocos2d::ui::Widget::TouchEventType type);

	//关闭单机按钮
	void ForgetPasswordButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
}; 
