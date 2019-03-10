#include "Feedback.h"
#include "constart.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CommonAudio.h"
using namespace std;
using namespace cocos2d::ui;
#pragma execution_character_set("utf-8")
USING_NS_CC;
bool Feedback::init() {
	if (!Layer::init()) {
		return false;
	}


	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Feedback::onTouchBegan, this);
	//吞没底层事件
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	auto rootNode = CSLoader::createNode("Feedback.csb");
	addChild(rootNode);

	Button* button1 = dynamic_cast<Button*>(rootNode->getChildByName("Button_2"));
	button1->addTouchEventListener(CC_CALLBACK_2(Feedback::closeButtonClicked, this));

	Button* button2 = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	button2->addTouchEventListener(CC_CALLBACK_2(Feedback::submitButtonClicked, this));


	userNameText = ui::EditBox::create(cocos2d::Size(650, 140), ui::Scale9Sprite::create("fankui.png"));
	userNameText->setPlaceHolder("请输入反馈或问题，我们会为你不断改进");
	userNameText->setPlaceholderFont("宋体", 30);
	userNameText->setColor(Color3B(241, 354, 3));
	userNameText->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 310, VISIBLE_SIZE.height / 2 -220));
	//userNameText->setScale(0.8);
	//userNameText->setMaxLength(12);//可以输入字符长度
	addChild(userNameText);
	game = CardGame::getInstance();


	auto textView = static_cast<Text*>(rootNode->getChildByName("Text_1_0_0_0"));
	textView->setText(game->account);



	return true;
}

//关闭
void Feedback::closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);

		removeAllChildrenWithCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	}
}

void Feedback::submitButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{

	auto userName = userNameText->getText();

	 
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);

		if (userNameText->getMaxLength() >= 4)
		{
			auto so = Sprite::create("match_bg.png");
			so->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height / 2));
			so->setScale(1.2);
			so->setOpacity(0);//可视度为0,1为完全可见
			addChild(so, 10);
			FadeIn* fadeIn = FadeIn::create(1);
			so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));

			//const rapidjson::Value& msg = doc["message"];
			Text* text = Text::create("内容请不要少于2个字符", "Arail", 40);
			text->setPosition(Vec2(260, 35));
			text->setColor(Color3B(255, 0, 0));
			text->setTag(15);
			so->addChild(text, 11);
			return;
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

		
			Text* text = Text::create("提交成功", "Arail", 40);
			text->setPosition(Vec2(260, 35));
			text->setColor(Color3B(255, 0, 0));
			text->setTag(15);
			so->addChild(text, 11);
			return;
		}
		


	}


}

bool Feedback::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

