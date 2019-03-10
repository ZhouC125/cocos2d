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
class LoginLayer : public Layer {
public:

	ui::EditBox * userNameText;
	ui::EditBox * passwordText;
	bool isdenglu = false;
	CREATE_FUNC(LoginLayer);
	virtual bool init();
	CardGame*game;
	EventListenerTouchOneByOne*  listener;
	Button* denglu;
	Sprite* rememberRadio1;
	 string userName;
	void update(float delta);//回调更新函数，该函数每一帧都被调用
	bool onTouchBegan(Touch * touch, Event * event);
	//退出
	void closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);

	//登录
	void loginButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);

	//用户协议勾选框
	void useragreement(Ref * sender, cocos2d::ui::Widget::TouchEventType type);

	//用户登陆请求
	void createHttpOfLogin(std::string url, cocos2d::network::HttpRequest::Type type,
		const cocos2d::network::ccHttpRequestCallback&callback);
	//登陆回馈
	void getResponseOfLogin(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse*response);

};
