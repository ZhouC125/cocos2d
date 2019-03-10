
#pragma once
#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "CardGame.h"
using namespace cocos2d::ui;
using namespace cocos2d::network;
using namespace std;
USING_NS_CC;
class GameHall :public Scene
{
public:
	static GameHall* scene();

	//static cocos2d::Scene* createSceneWithLevel(int selectLevel, int selectLevel1);
	CREATE_FUNC(GameHall);

	virtual bool init();

	Sprite *avararSprite;//头像精灵	
	EventListenerTouchOneByOne*  listener;
	Label*_goldsLabel;     //金币
	Label*_jewelLabel;     //钻石
	int s ;                   //金币
	int a ;                  //钻石

	CardGame*game;

private:
	bool onTouchBegan(Touch * touch, Event * event);

	void update(float delta);//回调更新函数，该函数每一帧都被调用

	virtual void tableCellTouched(Ref *sender, Widget::TouchEventType type);
	//商城
	void shopButtonclicked(Ref *sender, Widget::TouchEventType type);

	//设置
	void settingButtonClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	//加载规则层
	void guize1ButtonClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
   //反馈
   void isuepo(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
   //邮箱
   void mailbox(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

   	void createHttpOfHeadImg(string headImgUrl, const cocos2d::network::ccHttpRequestCallback &callBack);
	void getHeadImgResponse(cocos2d::network::HttpClient*sender
		, cocos2d::network::HttpResponse*response);
};
