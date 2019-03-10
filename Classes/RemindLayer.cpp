#include "RemindLayer.h"
#include "constart.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "DengluScene.h"
#include "CommonAudio.h"
using namespace std;
using namespace cocos2d::ui;
USING_NS_CC;
bool RemindLayer::init() {
	if (!Layer::init()) {
		return false;
	}


	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(RemindLayer::onTouchBegan, this);
	//吞没底层事件
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);



	auto rootNode = CSLoader::createNode("Layer.csb");
	addChild(rootNode);

	


	Button* button1 = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	button1->addTouchEventListener(CC_CALLBACK_2(RemindLayer::closeButtonClicked, this));


	Button* button2 = dynamic_cast<Button*>(rootNode->getChildByName("Button_1_0"));
	button2->addTouchEventListener(CC_CALLBACK_2(RemindLayer::closeButtonClicked1, this));



	return true;
}

//关闭
void RemindLayer::closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		removeAllChildrenWithCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	}
}
void RemindLayer::closeButtonClicked1(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		auto transition = TransitionFade::create(1.0f, DengluScene::scene());
		Director::getInstance()->replaceScene(transition);//切换场景
	}
}

bool RemindLayer::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}


