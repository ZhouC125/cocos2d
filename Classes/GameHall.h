
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

	Sprite *avararSprite;//ͷ����	
	EventListenerTouchOneByOne*  listener;
	Label*_goldsLabel;     //���
	Label*_jewelLabel;     //��ʯ
	int s ;                   //���
	int a ;                  //��ʯ

	CardGame*game;

private:
	bool onTouchBegan(Touch * touch, Event * event);

	void update(float delta);//�ص����º������ú���ÿһ֡��������

	virtual void tableCellTouched(Ref *sender, Widget::TouchEventType type);
	//�̳�
	void shopButtonclicked(Ref *sender, Widget::TouchEventType type);

	//����
	void settingButtonClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	//���ع����
	void guize1ButtonClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
   //����
   void isuepo(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
   //����
   void mailbox(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

   	void createHttpOfHeadImg(string headImgUrl, const cocos2d::network::ccHttpRequestCallback &callBack);
	void getHeadImgResponse(cocos2d::network::HttpClient*sender
		, cocos2d::network::HttpResponse*response);
};
