
#include "ForgetPasswordLayer.h"
#include "constart.h"
#include "DengluScene.h"
#include "audio/include/SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include <json/document.h>
#include "CommonAudio.h"
#pragma execution_character_set("utf-8")

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
using namespace cocos2d::network;
bool ForgetPasswordLayer::init()
{
	if (!Layer::init())
		return false;

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ForgetPasswordLayer::onTouchBegan, this);
	//吞没底层事件
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto rootNode = CSLoader::createNode("ForgetPasswordLayer.csb");
	addChild(rootNode);

	game = CardGame::getInstance();

	node = dynamic_cast<Node*>(rootNode->getChildByName("Node_1"));
	node->setVisible(false);
	button2 = dynamic_cast<Button*>(node->getChildByName("Button_2"));
	button2->addTouchEventListener(CC_CALLBACK_2(ForgetPasswordLayer::closeButtonClicked, this));
	button1 = dynamic_cast<Button*>(node->getChildByName("Button_1"));
	button1->addTouchEventListener(CC_CALLBACK_2(ForgetPasswordLayer::Sure, this));
	//答案
	 textView4 = static_cast<Text*>(node->getChildByName("Text_1_0_0"));
	//密保问题
	 textView2 = static_cast<Text*>(node->getChildByName("Text_1_0"));
	 

   button3 = dynamic_cast<Button*>(rootNode->getChildByName("Button_3"));
	button3->addTouchEventListener(CC_CALLBACK_2(ForgetPasswordLayer::Sure, this));

	Button* button4 = dynamic_cast<Button*>(rootNode->getChildByName("Button_4"));
	button4->addTouchEventListener(CC_CALLBACK_2(ForgetPasswordLayer::closeButtonClicked, this));


	node1 = dynamic_cast<Node*>(rootNode->getChildByName("Node_2"));
	node1->setVisible(false);
	//新密码
	auto textView = static_cast<Text*>(node1->getChildByName("Text_1_1"));

	//确认密码
	auto textView1 = static_cast<Text*>(node1->getChildByName("Text_1_1_0"));




	//账号
	auto textView5 = static_cast<Text*>(rootNode->getChildByName("Text_1"));

	//账户输入框
	userNameText = ui::EditBox::create(cocos2d::Size(590, 73), ui::Scale9Sprite::create("duan.png"));
	userNameText->setPlaceHolder("输入账号");
	userNameText->setPlaceholderFont("宋体", 45);
	userNameText->setColor(Color3B(241, 354, 3));
	userNameText->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 100, VISIBLE_SIZE.height / 2 + 50));
	userNameText->setMaxLength(20);//可以输入字符长度
	addChild(userNameText);

	//密保问题
	passwordText = ui::EditBox::create(cocos2d::Size(590, 73), ui::Scale9Sprite::create("duan.png"));
	//passwordText->setPlaceHolder("1");
	passwordText->setPlaceholderFont("宋体", 45);
	passwordText->setColor(Color3B(241, 354, 3));
	passwordText->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 100, VISIBLE_SIZE.height / 2 - 60));
	passwordText->setVisible(false);
	passwordText->setText(game->question.c_str());
	passwordText->setMaxLength(20);//可以输入字符长度
	addChild(passwordText);
	passwordText->setEnabled(false);
	const char* str = passwordText->getText();

  ///密保答案
	passwordText1 = ui::EditBox::create(cocos2d::Size(590, 73), ui::Scale9Sprite::create("duan.png"));
	passwordText1->setPlaceHolder("输入密码");
	passwordText1->setPlaceholderFont("宋体", 45);
	passwordText1->setColor(Color3B(241, 354, 3));
	passwordText1->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 100, VISIBLE_SIZE.height / 2 - 175));
	passwordText1->setVisible(false);
	passwordText1->setMaxLength(20);//可以输入字符长度
	addChild(passwordText1);

	//新密码
	passwordText2 = ui::EditBox::create(cocos2d::Size(590, 73), ui::Scale9Sprite::create("duan.png"));
	passwordText2->setPlaceHolder("输入密码");
	passwordText2->setPlaceholderFont("宋体", 45);
	passwordText2->setColor(Color3B(241, 354, 3));
	passwordText2->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 100, VISIBLE_SIZE.height / 2 - 60));
	passwordText2->setInputFlag(EditBox::InputFlag::PASSWORD);//设置输入标志 密码输入标志（显示为*）
	passwordText2->setVisible(false);
	passwordText2->setMaxLength(20);//可以输入字符长度
	addChild(passwordText2);
	//const char* str = passwordText2->getText();


	//确定新密码
	passwordText3 = ui::EditBox::create(cocos2d::Size(590, 73), ui::Scale9Sprite::create("duan.png"));
	passwordText3->setPlaceHolder("确认密码");
	passwordText3->setPlaceholderFont("宋体", 45);
	passwordText3->setColor(Color3B(241, 354, 3));
	passwordText3->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 100, VISIBLE_SIZE.height / 2 - 175));
	passwordText3->setInputFlag(EditBox::InputFlag::PASSWORD);//设置输入标志 密码输入标志（显示为*
	passwordText3->setVisible(false);
	passwordText3->setMaxLength(20);//可以输入字符长度
	addChild(passwordText3);







	return true;
}


bool ForgetPasswordLayer::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}
//退出
void ForgetPasswordLayer::closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		this->unscheduleUpdate();
		removeAllChildrenWithCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	}
}



void ForgetPasswordLayer::Sure(Ref* sender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		registerClicked();
		if (isAnswer)
		{
			sigin(sender, type);
		}
	/*	sureBtn->setEnabled(false);*/
	}
}

void ForgetPasswordLayer::sigin(Ref* psender, Widget::TouchEventType type) {
	const char* word1 = passwordText3->getText();
	const char* word2 = passwordText2->getText();
	//passwordText3->setEnabled(false);
	//passwordText2->setEnabled(false);
	int a = strcmp(word1, word2);
	if (type == Widget::TouchEventType::ENDED) {

		userNameText->setEnabled(false);
		if (a == 0) {//若两次密码一致
			//registerClicked();
			std::string url = "http://dong.deepe.ren/index.php?action=cuser&func=findPass";//重置密码
			auto password = passwordText3->getText();
			auto userName= userNameText->getText();
			if (isAnswer) {

				url.append("&userName=");
				url.append(userName);

				url.append("&password=");
				url.append(password);
				createHttpOfRegister(url.c_str(), HttpRequest::Type::GET, CC_CALLBACK_2(ForgetPasswordLayer::ValidationPassword, this));
			}

			if (isSuccess2 == true)
			{
			

				auto so = Sprite::create("match_bg.png");
				so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
				so->setScale(1.2);
				so->setOpacity(0);//可视度为0,1为完全可见
				addChild(so, 10);
				FadeIn* fadeIn = FadeIn::create(1);
				so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));

				Text* text = Text::create("重置成功", "Arail", 40);
				text->setPosition(Vec2(260, 35));
				text->setColor(Color3B(255, 0, 0));
				text->setTag(15);
				so->addChild(text, 11);

				removeAllChildrenWithCleanup(true);
				Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

			}
		}
		if (a != 0) {

			auto so = Sprite::create("match_bg.png");
			so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
			so->setScale(1.2);
			so->setOpacity(0);//可视度为0,1为完全可见
			addChild(so, 10);
			FadeIn* fadeIn = FadeIn::create(1);
			so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));

			Text* text = Text::create("2次密码不一致", "Arail", 40);
			text->setPosition(Vec2(260, 35));
			text->setColor(Color3B(255, 0, 0));
			text->setTag(15);
			so->addChild(text, 11);


		}
	}
}



void ForgetPasswordLayer::registerClicked() {
	std::string url = "http://dong.deepe.ren/index.php?action=cuser&func=enterAnswer";//验证密保
	
	auto userName = userNameText->getText();
	auto answertext = passwordText1->getText();


	url.append("&userName=");
	url.append(userName);
	if (!isClicked)
	{
		createHttpOfRegister(url.c_str(), HttpRequest::Type::GET, CC_CALLBACK_2(ForgetPasswordLayer::ValidationUsername, this));
	}

	if (isUsername)
	{
		url.append("&answer=");
		url.append(answertext);
		createHttpOfRegister(url.c_str(), HttpRequest::Type::GET, CC_CALLBACK_2(ForgetPasswordLayer::ValidationAnswer, this));
	}
	
}
void ForgetPasswordLayer::createHttpOfRegister(std::string url, cocos2d::network::HttpRequest::Type type,
	const cocos2d::network::ccHttpRequestCallback &callback) {
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

}
void ForgetPasswordLayer::ValidationUsername(cocos2d::network::HttpClient* sender,
	cocos2d::network::HttpResponse* response) {
	if (!response) {
		return;
	}
	if (!response->isSucceed()) {
		Sprite* errorBG = Sprite::create("warning.png");
		errorBG->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2 + 50));
		errorBG->setTag(11);
		addChild(errorBG);
		auto errorText = Text::create("无法连接到服务器---", "Arail", 18);
		errorText->setColor(Color3B(255, 0, 0));
		errorText->setPosition(Vec2(errorBG->getPositionX(), errorBG->getPositionY() - 10));
		errorText->setTag(12);
		addChild(errorText);

		//log(response->getErrorBuffer());
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
		//log("我不是一个对象");

	}
	if (doc.HasMember("code"))
	{
		const rapidjson::Value& code = doc["code"];

		if (code.IsInt())
		{
			if (code.GetInt() > 0)
			{
				isClicked = true;
				isUsername = true;
				userNameText->setEnabled(false);
				const rapidjson::Value& data1 = doc["data"];
	
				isSuccess1 = true;
				//账号正确
				if (isAnswer == false)
				{
					auto so = Sprite::create("match_bg.png");
					so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
					so->setScale(1.2);
					so->setOpacity(0);//可视度为0,1为完全可见
					addChild(so, 10);

					FadeIn* fadeIn = FadeIn::create(1);
					so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));
					auto used = Text::create("账号正确", "Arail", 40);
					used->setPosition(Vec2(260, 35));
					used->setColor(Color3B(0, 255, 0));
					so->addChild(used, 11);
					passwordText->setVisible(true);
					passwordText1->setVisible(true);
					button3->setVisible(false);
					node->setVisible(true);
			
				}

			}
			else
			{
		
				isUsername = false;
			

				auto so = Sprite::create("match_bg.png");
				so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
				so->setScale(1.2);
				so->setOpacity(0);//可视度为0,1为完全可见
				addChild(so, 10);
				FadeIn* fadeIn = FadeIn::create(1);
				so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));
				const rapidjson::Value& msg = doc["message"];
				Text* text = Text::create(msg.GetString(), "Arail", 40);
				text->setPosition(Vec2(260, 35));
				text->setColor(Color3B(255, 0, 0));
				text->setTag(15);
				so->addChild(text, 11);

			

				/*auto sureBtn2 = Button::create("sure.png");
				sureBtn2->setPosition(Vec2(errorBG->getPositionX(), errorBG->getPositionY() - 80));
				sureBtn2->addTouchEventListener(CC_CALLBACK_2(RetrievePassword::Onclicked, this));
				sureBtn2->setTag(16);
				hasText2 = true;
				addChild(sureBtn2);*/
			}
		}
	}
}

void ForgetPasswordLayer::ValidationAnswer(cocos2d::network::HttpClient* sender,
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
		//log("我不是一个对象");
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
				/*wenTiLabel->setVisible(false);
				wenTiText->setVisible(false);
				answerLabel->setVisible(false);
				answerText->setVisible(false);
				passwordLabel->setVisible(true);
				passwordText->setVisible(true);
				ConfirmLabel->setVisible(true);
				ConfirmPassword->setVisible(true);
				sureBtn->setEnabled(true);*/
				isUsername = false;
				isAnswer = true;



				auto so = Sprite::create("match_bg.png");
				so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
				so->setScale(1.2);
				so->setOpacity(0);//可视度为0,1为完全可见
				addChild(so, 10);
				FadeIn* fadeIn = FadeIn::create(1);
				so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));

				Text* text = Text::create("回答正确", "Arail", 40);
				text->setPosition(Vec2(260, 35));
				text->setColor(Color3B(0, 255, 0));
				text->setTag(15);
				so->addChild(text, 11);

				   passwordText->setVisible(false);
					passwordText1->setVisible(false);
					passwordText2->setVisible(true);
					passwordText3->setVisible(true);
					textView2->setVisible(false);
					textView4->setVisible(false);
					node1->setVisible(true);

			}
			else if (code.GetInt() < 0)
			{
	
				isAnswer = false;
				auto so = Sprite::create("match_bg.png");
				so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
				so->setScale(1.3);
				so->setOpacity(0);//可视度为0,1为完全可见
				addChild(so, 10);
				FadeIn* fadeIn = FadeIn::create(1);
				so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));
				const rapidjson::Value& msg = doc["message"];
				Text* text = Text::create(msg.GetString(), "Arail", 35);
				text->setPosition(Vec2(260, 35));
				text->setColor(Color3B(255, 0, 0));
				text->setTag(15);
				so->addChild(text, 11);

			}
		}
	}
}
void ForgetPasswordLayer::ValidationPassword(cocos2d::network::HttpClient* sender,
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
	//	log(response->getErrorBuffer());
		return;
	}

	
	//获取到响应的信息
	std::vector<char>* buffer = response->getResponseData();
	char data[8888] = "";
	std::copy(buffer->begin(), buffer->end(), data);
	//解析json
	rapidjson::Document doc;
	doc.Parse<0>(data);
	if (!doc.IsObject()) {


		//重置成功
		auto so = Sprite::create("match_bg.png");
		so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
		so->setScale(1.2);
		so->setOpacity(0);//可视度为0,1为完全可见
		addChild(so, 10);
		FadeIn* fadeIn = FadeIn::create(1);
		so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));

		Text* text = Text::create("重置成功", "Arail", 40);
		text->setPosition(Vec2(260, 35));
		text->setColor(Color3B(0, 255, 0));
		text->setTag(15);
		so->addChild(text, 11);



		return;
	}		
if (doc.HasMember("code"))
{
	const rapidjson::Value& code = doc["code"];
					//log("%d", code);
	if (code.IsInt()){
	if (code.GetInt() > 0)
	{
				isAnswer = true;
				isSuccess2 = true;
				//重置成功
				auto so = Sprite::create("match_bg.png");
				so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
				so->setScale(1.2);
				so->setOpacity(0);//可视度为0,1为完全可见
				addChild(so, 10);
				FadeIn* fadeIn = FadeIn::create(1);
				so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));

				Text* text = Text::create("重置成功", "Arail", 40);
				text->setPosition(Vec2(260, 35));
				text->setColor(Color3B(0, 255, 0));
				text->setTag(15);
				so->addChild(text, 11);
			}
			else
			{
				isAnswer = false;
				auto so = Sprite::create("match_bg.png");
				so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
				so->setScale(1.3);
				so->setOpacity(0);//可视度为0,1为完全可见
				addChild(so, 10);
				FadeIn* fadeIn = FadeIn::create(1);
				so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));
				const rapidjson::Value& msg = doc["message"];
				Text* text = Text::create(msg.GetString(), "Arail", 35);
				text->setPosition(Vec2(260, 35));
				text->setColor(Color3B(255, 0, 0));
				text->setTag(15);
				so->addChild(text, 11);
			}
		}
	}
}