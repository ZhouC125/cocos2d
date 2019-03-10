#pragma execution_character_set("utf-8")
#include "ZhuceScene.h"
#include "constart.h"
#include "DengluScene.h"
#include "audio/include/SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "CommonAudio.h"
//#pragma execution_character_set("utf-8")

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
using namespace cocos2d::network;
bool ZhuceScene::init()
{
	if (!Layer::init())
		return false;

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ZhuceScene::onTouchBegan, this);
	//吞没底层事件
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto rootNode = CSLoader::createNode("ZhuChe.csb");
	addChild(rootNode);


	Button* button1 = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	button1->addTouchEventListener(CC_CALLBACK_2(ZhuceScene::registerButtonClicked, this));

	Button* button2 = dynamic_cast<Button*>(rootNode->getChildByName("Button_2"));
	button2->addTouchEventListener(CC_CALLBACK_2(ZhuceScene::closeButtonClicked, this));



	//账户输入框
	userNameText = ui::EditBox::create(cocos2d::Size(590, 73), ui::Scale9Sprite::create("duan.png"));
	userNameText->setPlaceHolder("输入账号");
	userNameText->setPlaceholderFont("宋体", 45);
	userNameText->setColor(Color3B(241, 354, 3));
	userNameText->setPosition(Vec2(VISIBLE_SIZE.width / 2 -100, VISIBLE_SIZE.height/2+50));
	userNameText->setMaxLength(12);//可以输入字符长度
	addChild(userNameText);

	//密码输入框
	passwordText = ui::EditBox::create(cocos2d::Size(590, 73), ui::Scale9Sprite::create("duan.png"));
	passwordText->setPlaceHolder("输入密码");
	passwordText->setPlaceholderFont("宋体", 45);
	passwordText->setColor(Color3B(241, 354, 3));
	passwordText->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 100, VISIBLE_SIZE.height / 2-70));
	//passwordText->setInputMode(EditBox::InputMode::NUMERIC);//设置输入类型 数字及特殊符号输入
	passwordText->setInputFlag(EditBox::InputFlag::PASSWORD);//设置输入标志 密码输入标志（显示为*）
	passwordText->setMaxLength(20);//可以输入字符长度
	addChild(passwordText);
	const char* str = passwordText->getText();

	//确认密码输入框
	passwordText1 = ui::EditBox::create(cocos2d::Size(590, 73), ui::Scale9Sprite::create("duan.png"));
	passwordText1->setPlaceHolder("确认密码");
	passwordText1->setPlaceholderFont("宋体", 45);
	passwordText1->setColor(Color3B(241, 354, 3));
	passwordText1->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 100, VISIBLE_SIZE.height / 2 -190));
	//passwordText->setInputMode(EditBox::InputMode::NUMERIC);//设置输入类型 数字及特殊符号输入
	passwordText1->setInputFlag(EditBox::InputFlag::PASSWORD);//设置输入标志 密码输入标志（显示为*）
	passwordText1->setMaxLength(20);//可以输入字符长度
	addChild(passwordText1);


	

	return true;
}

void ZhuceScene::registerButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type){
	
	  if (type != Widget::TouchEventType::ENDED)
	  {
		  return;
	  }
	  CommonAudio::playAudio(8);
	  const char* word = userNameText->getText();
	  const char* word1 = passwordText->getText();
	  const char* word2 = passwordText1->getText();

	  int w;
	  int w1;
	  int w2;
	  w = (int)word;
	  w1 = (int)word1;
	  w2 = (int)word2;
	  int s = strcmp(word1, word2);
	  if (s == 0) {//若两次密码一致
		  registerClicked();

		  if (isSuccess == true)
		  {

		


              //  log("注册成功！");
		  }
	  }
	  if (s != 0) {
	  
	  
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
		  return;

	  
	  }





	
  }


  bool ZhuceScene::onTouchBegan(Touch * touch, Event * event)
  {
	  return true;
  }
  //退出
  void ZhuceScene::closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
  {
	  if (type == Widget::TouchEventType::ENDED) {
		  CommonAudio::playAudio(8);
		  this->unscheduleUpdate();
		  removeAllChildrenWithCleanup(true);
		  Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	  }
  }

  void ZhuceScene::registerClicked() {
	  auto userName = userNameText->getText();
	  auto password = passwordText->getText();
	  std::string url = "http://dong.deepe.ren/index.php?action=cuser&func=register";
	  url.append("&userName=");
	  url.append(userName);
	  url.append("&password=");
	  url.append(password);

	  createHttpOfRegister(url.c_str(), HttpRequest::Type::GET, CC_CALLBACK_2(ZhuceScene::getResponseOfRegister, this));


  }

  void ZhuceScene::createHttpOfRegister(std::string url, cocos2d::network::HttpRequest::Type type,
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

  void ZhuceScene::getResponseOfRegister(cocos2d::network::HttpClient* sender,
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
//  log(data);
//log("enenenne");

	  //解析json
	  rapidjson::Document doc;
	  doc.Parse<0>(data);

	  if (!doc.IsObject()) {
//	  log("我不是一个对象");
	  }
	  if (doc.HasMember("code"))
	  {
		  const rapidjson::Value& code = doc["code"];

		  if (code.IsInt())
		  {
			  if (code.GetInt() > 0)
			  {
				  isSuccess = true;

				  auto so = Sprite::create("match_bg.png");
				  so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
				  so->setScale(1.2);
				  so->setOpacity(0);//可视度为0,1为完全可见
				  addChild(so, 10);

				  FadeIn* fadeIn = FadeIn::create(1);
				  so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));
				  auto used = Text::create("注册成功", "Arail", 40);
				  used->setPosition(Vec2(260, 35));
				  used->setColor(Color3B(0, 255, 0));
				  so->addChild(used, 11);


				  //Director::getInstance()->replaceScene(DengluScene::scene());//切换场景

				  return;
			  }
			  else
			  {
	//  log("注册失败");

				
	
				  auto so = Sprite::create("match_bg.png");
				  so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
				  so->setScale(1.6);
				  so->setOpacity(0);//可视度为0,1为完全可见
				  addChild(so, 10);
				  FadeIn* fadeIn = FadeIn::create(1);
				  so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));

				  const rapidjson::Value& msg = doc["message"];
				  Text* text = Text::create(msg.GetString(), "Arail", 29);
				  text->setPosition(Vec2(255, 35));
				  text->setColor(Color3B(255, 0, 0));
				  text->setTag(15);
				  so->addChild(text, 11);
				  return;
			  }
		  }
	  }
  }