#include "MailboxLayer.h"
#include "constart.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CommonAudio.h"
using namespace std;
using namespace cocos2d::ui;
USING_NS_CC;
bool MailboxLayer::init() {
	if (!Layer::init()) {
		return false;
	}


	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MailboxLayer::onTouchBegan, this);
	//吞没底层事件
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto rootNode = CSLoader::createNode("MailboxLayer.csb");
	addChild(rootNode);

	Button* button1 = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	button1->addTouchEventListener(CC_CALLBACK_2(MailboxLayer::closeButtonClicked, this));
	Button* button2 = dynamic_cast<Button*>(rootNode->getChildByName("Button_2"));
	button2->addTouchEventListener(CC_CALLBACK_2(MailboxLayer::fButtonClicked1, this));
	Button* button3 = dynamic_cast<Button*>(rootNode->getChildByName("Button_3"));
	button3->addTouchEventListener(CC_CALLBACK_2(MailboxLayer::fButtonClicked2, this));
	Button* button4 = dynamic_cast<Button*>(rootNode->getChildByName("Button_4"));
	button4->addTouchEventListener(CC_CALLBACK_2(MailboxLayer::fButtonClicked3, this));

	g1 = dynamic_cast<ImageView*>(rootNode->getChildByName("Image_2")); 
	g2 = dynamic_cast<ImageView*>(rootNode->getChildByName("Image_3"));
	g2->setVisible(false);
	g3 = dynamic_cast<ImageView*>(rootNode->getChildByName("Image_4"));
	g3->setVisible(false);
	xuanzhe1 = dynamic_cast<ImageView*>(rootNode->getChildByName("Image_5"));

	xuanzhe2 = dynamic_cast<ImageView*>(rootNode->getChildByName("Image_8"));
	xuanzhe2->setVisible(false);
	xuanzhe3 = dynamic_cast<ImageView*>(rootNode->getChildByName("Image_7"));
	xuanzhe3->setVisible(false);


	return true;
}

//关闭
void MailboxLayer::closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		removeAllChildrenWithCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	}
}

void MailboxLayer::fButtonClicked1(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{

	if (type == Widget::TouchEventType::ENDED) {

		CommonAudio::playAudio(8);
		g1->setVisible(true);
		g2->setVisible(false);
		g3->setVisible(false);
		xuanzhe1->setVisible(true);
		xuanzhe2->setVisible(false);
		xuanzhe3->setVisible(false);

	}
}

void MailboxLayer::fButtonClicked2(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		g1->setVisible(false);
		g3->setVisible(false);
		g2->setVisible(true);
		xuanzhe2->setVisible(true);
		xuanzhe1->setVisible(false);
		xuanzhe3->setVisible(false);

	}
}

void MailboxLayer::fButtonClicked3(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		g1->setVisible(false);
		g2->setVisible(false);
		g3->setVisible(true);
		xuanzhe3->setVisible(true);
		xuanzhe1->setVisible(false);
		xuanzhe2->setVisible(false);
	}
}

bool MailboxLayer::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

//
