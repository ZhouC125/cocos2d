
#include "LoginLayer.h"
#include "constart.h"
#include "DengluScene.h"
#include "GameHall.h"
#include "audio/include/SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "CommonAudio.h"
#include "ProgressLayer.h"
#pragma execution_character_set("utf-8")
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
using namespace cocos2d::network;

bool LoginLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LoginLayer::onTouchBegan, this);
	//吞没底层事件
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	auto rootNode = CSLoader::createNode("LoginLayer.csb");
	addChild(rootNode);

	//denglu = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	//denglu->addTouchEventListener(CC_CALLBACK_2(LoginLayer::loginButtonClicked, this));

	//登录按钮
	denglu = Button::create("denglu.png");
	denglu->setPosition(Vec2(VISIBLE_SIZE.width / 2-160, VISIBLE_SIZE.height / 2 -230));
	denglu->addTouchEventListener(CC_CALLBACK_2(LoginLayer::loginButtonClicked, this));

	addChild(denglu);

	Button* button2 = dynamic_cast<Button*>(rootNode->getChildByName("Button_2"));
	button2->addTouchEventListener(CC_CALLBACK_2(LoginLayer::useragreement, this));

	 rememberRadio1 = dynamic_cast<Sprite*>(rootNode->getChildByName("icon_success1_3"));
	rememberRadio1->setVisible(false);


	Button* button4 = dynamic_cast<Button*>(rootNode->getChildByName("Button_4"));
	button4->addTouchEventListener(CC_CALLBACK_2(LoginLayer::closeButtonClicked, this));



	//账户输入框
	userNameText = ui::EditBox::create(cocos2d::Size(590, 73), ui::Scale9Sprite::create("duan.png"));
	userNameText->setPlaceHolder("输入账号");
	userNameText->setPlaceholderFont("宋体", 45);
	userNameText->setColor(Color3B(241, 354, 3));
	userNameText->setPosition(Vec2(VISIBLE_SIZE.width / 2 -150, VISIBLE_SIZE.height/2-5));
	//userNameText->setScale(0.8);
	userNameText->setMaxLength(12);//可以输入字符长度
	addChild(userNameText);

	//密码输入框
	passwordText = ui::EditBox::create(cocos2d::Size(590, 73), ui::Scale9Sprite::create("duan.png"));
	passwordText->setPlaceHolder("输入密码");
	passwordText->setPlaceholderFont("宋体", 45);
	passwordText->setColor(Color3B(241, 354, 3));
	passwordText->setPosition(Vec2(VISIBLE_SIZE.width / 2 -150, VISIBLE_SIZE.height / 2-120));
	//passwordText->setScale(0.8);
	//passwordText->setInputMode(EditBox::InputMode::NUMERIC);//设置输入类型 数字及特殊符号输入
	passwordText->setInputFlag(EditBox::InputFlag::PASSWORD);//设置输入标志 密码输入标志（显示为*）
	passwordText->setMaxLength(14);//可以输入字符长度
	addChild(passwordText);

	game = CardGame::getInstance();
	this->scheduleUpdate();

	return true;
}
void LoginLayer::update(float delta) {

	if (isdenglu)
	{

		denglu->setBright(true);
		denglu->setTouchEnabled(true);

	}
	else	if (!isdenglu)
	{

		denglu->setBright(false);
		denglu->setTouchEnabled(false);

	}


}
//退出
void LoginLayer::closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		this->unscheduleUpdate();
		removeAllChildrenWithCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	}
}

bool LoginLayer::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

void LoginLayer::loginButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type) {

	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
			 userName = userNameText->getText();
			auto password = passwordText->getText();
			//向服务器发送请求
			//拼装地址
			std::string url = "http://dong.deepe.ren/index.php?action=cuser&func=login";

			//      http://dong.deepe.ren/index.php?action=cuser&func=login

			url.append("&userName=");
			url.append(userName);
			game->account = userName;
			url.append("&password=");
			url.append(password);
			//发送请求
			createHttpOfLogin(url, HttpRequest::Type::GET, CC_CALLBACK_2(LoginLayer::getResponseOfLogin, this));

			//auto transition = TransitionFadeDown::create(1.0f, Scene0910::createScene());
			//Director::getInstance()->replaceScene(transition);
		
		
	}
}
void LoginLayer::useragreement(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{


	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}
	CommonAudio::playAudio(8);
 	if (!isdenglu)
		{
			rememberRadio1->setVisible(true);
			isdenglu = true;

	}
	else
	{
		rememberRadio1->setVisible(false);
		isdenglu = false;

	}


}

//用户登陆请求
void LoginLayer::createHttpOfLogin(std::string url, cocos2d::network::HttpRequest::Type type,
	const cocos2d::network::ccHttpRequestCallback&callback) {
	//生成httpRequest对象
	auto request = new HttpRequest();
	//设置请求的地址
	request->setUrl(url.c_str());
	//设置请求方式
	request->setRequestType(type);
	//设置请求的回调函数
	request->setResponseCallback(callback);
	//CC_CALLBACK_2(Scene0910::getHeadImgResponse, this)
	//发送请求
	HttpClient::getInstance()->send(request);
	//释放HttpRequest对象
	request->release();

	//自行封装http
}

//登陆回馈
void LoginLayer::getResponseOfLogin(cocos2d::network::HttpClient* sender,
	cocos2d::network::HttpResponse* response) {
	if (!response) {
		return;
	}
	if (!response->isSucceed()) {
		auto so = Sprite::create("match_bg.png");
		so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
		so->setScale(1.2);
		so->setOpacity(0);//可视度为0,1为完全可见
		addChild(so, 10);
		FadeIn* fadeIn = FadeIn::create(1);
		so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));

		Text* text = Text::create("无法连接到服务器---", "Arail", 40);
		text->setPosition(Vec2(260, 35));
		text->setColor(Color3B(255, 0, 0));
		text->setTag(15);
		so->addChild(text, 11);
		return;

	}
	//获取到响应的信息
	std::vector<char>* buffer = response->getResponseData();
	char data[8888] = "";
	std::copy(buffer->begin(), buffer->end(), data);
	//log("enenenne");
	//log(data);
	//log("enenenne");

	//解析json
	rapidjson::Document doc;
	doc.Parse<0>(data);

	if (!doc.IsObject()) {
	//	log("我不是一个对象");

		auto so = Sprite::create("match_bg.png");
		so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
		so->setScale(1.2);
		so->setOpacity(0);//可视度为0,1为完全可见
		addChild(so, 10);
		FadeIn* fadeIn = FadeIn::create(1);
		so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));

		Text* text = Text::create("json解析错误---", "Arail", 40);
		text->setPosition(Vec2(260, 35));
		text->setColor(Color3B(255, 0, 0));
		text->setTag(15);
		so->addChild(text, 11);

		return;
	}
	if (doc.HasMember("code"))
	{
		const rapidjson::Value& code = doc["code"];
		//log("%d", code);
		if (code.IsInt())
		{
			if (code.GetInt() > 0)
			{
		//	log("登录成功");
			
				game->account = userName;
				Director::getInstance()->replaceScene(ProgressLayer::scene());//切换场景

			}
			else
			{
				auto so = Sprite::create("match_bg.png");
				so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
				so->setScale(1.2);
				so->setOpacity(0);//可视度为0,1为完全可见
				addChild(so, 10);
				FadeIn* fadeIn = FadeIn::create(1);
				so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));
				const rapidjson::Value& msg = doc["message"];
				Text* text = Text::create(msg.GetString(), "Arail", 40);
				text->setPosition(Vec2(260,35));
				text->setColor(Color3B(255, 0, 0));
				text->setTag(15);
				so-> addChild(text,11);
				return;
			}
		}
	}
}

