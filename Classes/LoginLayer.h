#pragma once
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include "cocos-ext.h"
#include "CardGame.h"
#include "network/HttpClient.h" //����ͷ�ļ�
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
	void update(float delta);//�ص����º������ú���ÿһ֡��������
	bool onTouchBegan(Touch * touch, Event * event);
	//�˳�
	void closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);

	//��¼
	void loginButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type);

	//�û�Э�鹴ѡ��
	void useragreement(Ref * sender, cocos2d::ui::Widget::TouchEventType type);

	//�û���½����
	void createHttpOfLogin(std::string url, cocos2d::network::HttpRequest::Type type,
		const cocos2d::network::ccHttpRequestCallback&callback);
	//��½����
	void getResponseOfLogin(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse*response);

};
