#include "SetLayer.h"
#include "constart.h"
#include "ui/CocosGUI.h"
#include "DengluScene.h"
#include "cocostudio/CocoStudio.h"
#include "CommonAudio.h"
#include "ModificationLayer.h"
using namespace std;
using namespace cocos2d::ui;
USING_NS_CC;
bool SetLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SetLayer::onTouchBegan, this);
	//吞没底层事件
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	auto rootNode = CSLoader::createNode("SetLayer.csb");
	//rootNode->setPosition(Vec2(VISIBLE_SIZE.width / 2-333, VISIBLE_SIZE.height / 2-187));
	addChild(rootNode);



	//通过按钮的名字获得按钮
	Button* button = dynamic_cast<Button*>(rootNode->getChildByName("Button_3"));
	//添加监听
	button->addTouchEventListener(CC_CALLBACK_2(SetLayer::closeButtonClicked, this));


	//通过按钮的名字获得按钮
	Button* button1 = dynamic_cast<Button*>(rootNode->getChildByName("Button_2"));
	//添加监听
	button1->addTouchEventListener(CC_CALLBACK_2(SetLayer::Zhuxiao, this));
	button1->setTag(3);

	Button* button2 = dynamic_cast<Button*>(rootNode->getChildByName("Button_10"));
	button2->addTouchEventListener(CC_CALLBACK_2(SetLayer::Zhuxiao, this));
	button2->setTag(4);


	 btn_off = dynamic_cast<Button*>(rootNode->getChildByName("Button_4"));
	 btn_off->addTouchEventListener(CC_CALLBACK_2(SetLayer::yinxiao, this));
	
	 btn_off->setTag(1);

	 btn_no = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	 btn_no->addTouchEventListener(CC_CALLBACK_2(SetLayer::yinxiao, this));
	 btn_no->setTag(2);
	 game = CardGame::getInstance();
	 if (game->is_yinxiao)
	 {
		 btn_no->setVisible(true);
		 btn_off->setVisible(false);
	 }
	 else
	 {
		 btn_no->setVisible(false);
		 btn_off->setVisible(true);
	 }


	return true;
}
bool SetLayer::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}
void SetLayer::closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		removeAllChildrenWithCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);


	}

}
void SetLayer::Zhuxiao(Ref * sender, cocos2d::ui::Widget::TouchEventType type) {

	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		Button*n = (Button*)sender;
		if (n->getTag() == 3) {

			CommonAudio::playAudio(8);
			game->is_denglu = false;
			Director::getInstance()->replaceScene(DengluScene::scene());//切换场景
		}
		else	if (n->getTag() == 4) {

			ModificationLayer *layer1 = ModificationLayer::create();
			//layer1->setPosition(Vec2(180, 80));
			addChild(layer1, 3);
		}
		
	}
}

void SetLayer::yinxiao(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{

	if (type == Widget::TouchEventType::ENDED) {
				Button*n = (Button*)sender;
				if (n->getTag()==1)
				{
					btn_no->setVisible(true);
					btn_off->setVisible(false);

					game->is_yinxiao = true;


				}
				else 	if (n->getTag() == 2)
				{
					btn_no->setVisible(false);
					btn_off->setVisible(true);

					game->is_yinxiao = false;


				}


	}
}
