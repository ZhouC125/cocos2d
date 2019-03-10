#include "constart.h"
#include "DengluScene.h"
#include "LoginLayer.h"
#include "ZhuceScene.h"
#include "GameScene.h"
#include "GameHall.h"
#include"ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "RulesLayer.h"
#include "ForgetPasswordLayer.h"
#include "CommonAudio.h"
#include "ProgressLayer.h"
#pragma execution_character_set("utf-8")

USING_NS_CC;
DengluScene * DengluScene::scene()
{
	return DengluScene::create();
}

bool DengluScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	CommonAudio::playAudio(9);

	auto rootNode = CSLoader::createNode("DengluScene.csb");
	addChild(rootNode);

	Button* button1 = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	button1->addTouchEventListener(CC_CALLBACK_2(DengluScene::Zhuce, this));

	Button* button2 = dynamic_cast<Button*>(rootNode->getChildByName("Button_2"));
	button2->addTouchEventListener(CC_CALLBACK_2(DengluScene::loginingButtonClicked, this));

	Button* button3 = dynamic_cast<Button*>(rootNode->getChildByName("Button_3"));
	button3->addTouchEventListener(CC_CALLBACK_2(DengluScene::danji, this));

	//button4 = dynamic_cast<Button*>(rootNode->getChildByName("Button_6"));
	//button4->addTouchEventListener(CC_CALLBACK_2(DengluScene::guizhe, this));

	Button* button5 = dynamic_cast<Button*>(rootNode->getChildByName("Button_7"));
	button5->addTouchEventListener(CC_CALLBACK_2(DengluScene::ForgetPasswordButtonClicked, this));
	game = CardGame::getInstance();

	game->is_accomplish = false;             
	game->is_toot = false;
	game->is_access = false;                  


	return true;
}


//×¢²á
void DengluScene::Zhuce(Object *pSender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		//auto transition = TransitionFade::create(1.0f, ZhuceScene::scene());
		//Director::getInstance()->replaceScene(transition);//ÇÐ»»³¡¾°
			//¼ÓÔØLogin²ã
		CommonAudio::playAudio(8);
		ZhuceScene *layer = ZhuceScene::create();
				layer->setPosition(Vec2(VISIBLE_SIZE.width / 4 - 170, VISIBLE_SIZE.height / 4 - 100));
		addChild(layer);
	}
	//Director::getInstance()->replaceScene(ZhuceScene::scene());//¿ìËÙÇÐ»»³¡¾°

		//auto transition = TransitionFade::create(1.0f, GameHall::scene());
		//Director::getInstance()->replaceScene(transition);//ÇÐ»»³¡¾°




}

//µÇÂ¼
void DengluScene::loginingButtonClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		//¼ÓÔØLogin²ã
		LoginLayer *layer = LoginLayer::create();
		layer->setPosition(Vec2(VISIBLE_SIZE.width / 4 - 170, VISIBLE_SIZE.height / 4 - 100));
		addChild(layer);
	}
}

void DengluScene::singleButtonClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			getChildByTag(1)->setVisible(true);//ÏÔÊ¾×Ó±³¾°
			getChildByTag(2)->setVisible(true);//ÏÔÊ¾¹Ø±Õ°´Å¥

		}
}

void DengluScene::closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {

		getChildByTag(1)->setVisible(false);//Òþ²Ø×Ó±³¾°
		getChildByTag(2)->setVisible(false);//Òþ²Ø¹Ø±Õ°´Å¥
	}
}

void DengluScene::danji(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);


		auto transition = TransitionMoveInR::create(0.5f, GameScene::create());
		Director::getInstance()->replaceScene(transition);//ÇÐ»»³¡¾°
		
	}
}

//void DengluScene::guizhe(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
//{
//	if (type != Widget::TouchEventType::ENDED)
//	{
//		return;
//	}
//	button4->setBright(false);
//	button4->setTouchEnabled(false);
//	bangzhu = Sprite::create("guizhe.jpg");
//	bangzhu->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
//	bangzhu->setVisible(true);
//	addChild(bangzhu, 5);
//
//	auto exitbtn = Button::create("close1.png");
//	exitbtn->setScale(1.3);
//	exitbtn->setPosition(Vec2(bangzhu->getPositionX()+140
//		, bangzhu->getPositionY() + bangzhu->boundingBox().size.height / 2-55));
//
//	exitbtn->addTouchEventListener(CC_CALLBACK_2(DengluScene::jump1, this));
//	bangzhu->addChild(exitbtn, 6);
//	Director::getInstance()->stopAnimation();
//}
void DengluScene::jump1(Ref * it, cocos2d::ui::Widget::TouchEventType type)
{

	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}
	bangzhu->setVisible(false);
	button4->setBright(true);
	button4->setTouchEnabled(true);
	Director::getInstance()->startAnimation();
}


void DengluScene::ForgetPasswordButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{


	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		//¼ÓÔØLogin²ã
		ForgetPasswordLayer *layer = ForgetPasswordLayer::create();
		layer->setPosition(Vec2(VISIBLE_SIZE.width / 4 - 170, VISIBLE_SIZE.height / 4 - 100));
		addChild(layer);
	}


}
