#include "RulesLayer.h"
#include "constart.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CommonAudio.h"
using namespace std;
using namespace cocos2d::ui;
USING_NS_CC;
bool RulesLayer::init() {
	if (!Layer::init()) {
		return false;
	}


	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(RulesLayer::onTouchBegan, this);
	//��û�ײ��¼�
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);



	auto rootNode = CSLoader::createNode("RulesLayer.csb");
	addChild(rootNode);

	
	 button1 = dynamic_cast<ImageView*>(rootNode->getChildByName("Image_1"));
	
	 button2 = dynamic_cast<ImageView*>(rootNode->getChildByName("Image_2"));
	button2->setVisible(false);

	Button* button3 = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	button3->addTouchEventListener(CC_CALLBACK_2(RulesLayer::closeButtonClicked, this));




	//ͨ����ť�����ֻ�ð�ť
	 f1 = dynamic_cast<Button*>(rootNode->getChildByName("Button_2"));
	//��Ӽ���
	f1->addTouchEventListener(CC_CALLBACK_2(RulesLayer::fButtonClicked1, this));


	h2 = dynamic_cast<Button*>(rootNode->getChildByName("Button_3"));
	h2->addTouchEventListener(CC_CALLBACK_2(RulesLayer::fButtonClicked2, this));
	h2->setVisible(false);

	
	


	return true;
}

//�ر�
void RulesLayer::closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);

		removeAllChildrenWithCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	}
}

bool RulesLayer::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

//
void RulesLayer::fButtonClicked1(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);

		f1->setVisible(false);//��ʾ����2
		h2->setVisible(true);//��ʾ��ҳ��ť2
		button1->setVisible(false);
		button2->setVisible(true);

	}
}

void RulesLayer::fButtonClicked2(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);

		f1->setVisible(true);//��ʾ����2
		h2->setVisible(false);//��ʾ��ҳ��ť2
		button1->setVisible(true);
		button2->setVisible(false);
	}
}

