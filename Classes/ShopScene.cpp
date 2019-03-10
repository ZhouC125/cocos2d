#include "constart.h"
#include "ShopScene.h"
#include "GameHall.h"
#include"ui/CocosGUI.h"
#include "CardGame.h"
#include "cocostudio/CocoStudio.h"
#include "CommonAudio.h"
using namespace std;
using namespace cocos2d::ui;
USING_NS_CC;
#pragma execution_character_set("utf-8")
ShopScene * ShopScene::scene()
{
	return ShopScene::create();
}

bool ShopScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	auto rootNode = CSLoader::createNode("ShopScene.csb");
	addChild(rootNode);
	Button* button1 = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	button1->addTouchEventListener(CC_CALLBACK_2(ShopScene::backButtonclicked, this));

	for (int i = 2; i < 10; i++)
	{

		string file_name = "";
		file_name = StringUtils::format("Button_%d", i);
		Button* button1 = dynamic_cast<Button*>(rootNode->getChildByName(file_name));
		button1->setTag(i);
		button1->addTouchEventListener(CC_CALLBACK_2(ShopScene::fButtonClicked1, this));
	}
	game = CardGame::getInstance();
	return true;
}

void ShopScene::backButtonclicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{

	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}
	CommonAudio::playAudio(8);
	GameHall *layer = GameHall::create();
	addChild(layer, 3);

}
void ShopScene::fButtonClicked1(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}
	CommonAudio::playAudio(8);
	Button*n = (Button*)sender;
	switch (n->getTag())
	{

	case 2:
		remind(1);
		break;
	case 3:
		remind(1);

		break;
	case 4:
		remind(1);

		break;

	case 5:
		remind(1);

		break;
	case 6:
		if (game->jewel >= 30)
		{
			game->golds += 3600;
			game->jewel -= 30;
			game->is_ok = true;
			remind(2);
		}
		else if (game->jewel < 30)
		{
			game->is_ok = false;

			remind(2);
		}

		break;
	case 7:
		if (game->jewel >= 60)
		{
			game->golds += 7560;
			game->jewel -= 60;
			game->is_ok = true;
			remind(2);
		}
		else if (game->jewel < 60)
		{
			game->is_ok = false;
			remind(2);
		}

		break;
	case 8:
		if (game->jewel >= 180)
		{
			game->golds += 13200;
			game->jewel -= 180;
			game->is_ok = true;
			remind(2);
		}
		else if (game->jewel < 180)
		{
			game->is_ok = false;
			remind(2);
		}

		break;
	case 9:
		if (game->jewel >= 400)
		{
			game->golds += 78000;
			game->jewel -= 400;
			game->is_ok = true;
			remind(2);
		}
		else if (game->jewel < 400)
		{
			game->is_ok = false;
			remind(2);
		}
		break;
	default:
		break;
	} 
}

void ShopScene::remind(int t)
{
	if (t==1)
	{

		auto chongzhi = Sprite::create("item_bg.png");
		chongzhi->setScaleX(1.5);
		chongzhi->setScaleY(2);
		chongzhi->setPosition(Vec2(VISIBLE_SIZE.width / 2 , VISIBLE_SIZE.height/2));
		addChild(chongzhi);

		
		auto weixin = Sprite::create("weixin.png");
		weixin->setScale(0.4);
		weixin->setPosition(Vec2(260,130));
		chongzhi->addChild(weixin);


	}
	else  if(t==2)
	{
		game->pmgressbar[0] = 100;
		game->text[0] = "1";


		if (game->is_ok)
		{
			/*		CommonAnimation::ShopAnimation(1);*/
			auto so = Sprite::create("success.png");
			so->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
			so->setScale(1.2);
			so->setOpacity(0);//可视度为0,1为完全可见
			addChild(so, 10);
			FadeIn* fadeIn = FadeIn::create(1);
			so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));
		}
		else if (!game->is_ok)
		{
			/*CommonAnimation::ShopAnimation(2);*/
			auto so = Sprite::create("12355.png");
			so->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
			so->setScale(1.2);
			so->setOpacity(0);//可视度为0,1为完全可见
			addChild(so, 10);
			FadeIn* fadeIn = FadeIn::create(1);
			so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));
		}
		game->is_ok = false;
	}
	
}
