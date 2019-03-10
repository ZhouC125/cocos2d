
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
class ModificationLayer :public Layer
{
public:
	ui::EditBox * userNameText;
	ui::EditBox * passwordText;
	ui::EditBox * passwordText1;
	CREATE_FUNC(ModificationLayer);
	EventListenerTouchOneByOne*  listener;
	CardGame*game;
	bool isSuccess;
	virtual bool init();
private:
	void registerButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	bool onTouchBegan(Touch * touch, Event * event);


	//退出
	void closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);

	void registerClicked();


	void getResponseOfRegister(cocos2d::network::HttpClient* sender,
		cocos2d::network::HttpResponse* response);

	void createHttpOfRegister(std::string url, cocos2d::network::HttpRequest::Type type,
		const cocos2d::network::ccHttpRequestCallback &callback);


	void ValidationAnswer(cocos2d::network::HttpClient* sender,
		cocos2d::network::HttpResponse* response);
};
