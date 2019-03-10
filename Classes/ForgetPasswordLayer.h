
#pragma once


#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include "cocos-ext.h"
#include "CardGame.h"
#include "network/HttpClient.h" //包含头文件
using namespace cocos2d::extension;
using namespace cocos2d;
using namespace cocos2d::ui;
USING_NS_CC_EXT;
USING_NS_CC;



class ForgetPasswordLayer :public Layer
{
public:
	ui::EditBox * userNameText;
	ui::EditBox * passwordText;
	ui::EditBox * passwordText1;
	ui::EditBox * passwordText2;
	ui::EditBox * passwordText3;
	CREATE_FUNC(ForgetPasswordLayer);
	EventListenerTouchOneByOne*  listener;
	bool isSuccess;
	virtual bool init();

	Button* button1;
	Button* button2;
	Button* button3;
	Node*node;
	Node*node1;
	Text* textView4;
	Text* textView2;

	CardGame*game;



	bool isSuccess1;
	bool isSuccess2;
	bool isUsername = false;
	bool isAnswer = false;
	bool isClicked = false;

private:
	bool onTouchBegan(Touch * touch, Event * event);

	void registerClicked();
	//退出
	void closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	


	void Sure(Ref* psender, Widget::TouchEventType type);
	void sigin(Ref* psender, Widget::TouchEventType type);
	//void registerClicked();
	void createHttpOfRegister(std::string url, cocos2d::network::HttpRequest::Type type,
		const cocos2d::network::ccHttpRequestCallback &callback);
	void ValidationUsername(cocos2d::network::HttpClient* sender,
		cocos2d::network::HttpResponse* response);
	void ValidationAnswer(cocos2d::network::HttpClient* sender,
		cocos2d::network::HttpResponse* response);
	void ValidationPassword(cocos2d::network::HttpClient* sender,
		cocos2d::network::HttpResponse* response);
	//void Onclicked(Ref* sender, Widget::TouchEventType type);
};
