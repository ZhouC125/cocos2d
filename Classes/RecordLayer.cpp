#include "RecordLayer.h"
#include "constart.h"
#include "audio/include/SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "GameHall.h"
#include "DengluScene.h"
#include "GameScene.h"
#include "CommonAudio.h"
using namespace std;
using namespace cocos2d::ui;
USING_NS_CC;
bool RecordLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(RecordLayer::onTouchBegan, this);
	//吞没底层事件
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto rootNode = CSLoader::createNode("Record.csb");
	//rootNode->setPosition(Vec2(VISIBLE_SIZE.width / 2-333, VISIBLE_SIZE.height / 2-187));
	addChild(rootNode);

	//通过按钮的名字获得按钮
	Button* button = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	//添加监听
	button->addTouchEventListener(CC_CALLBACK_2(RecordLayer::closeButtonClicked, this));
	button->setTag(1);
	auto scrollView = static_cast<ScrollView*>(rootNode->getChildByName("ScrollView_2"));


	sprtie1 = static_cast<Sprite*>(scrollView->getChildByName("Sprite_45"));
	sprtie1->setVisible(false);
	auto Sprite_62 = static_cast<Sprite*>(sprtie1->getChildByName("Sprite_62"));
	auto Sprite_62_0 = static_cast<Sprite*>(sprtie1->getChildByName("Sprite_62_0"));
	auto Sprite_62_1 = static_cast<Sprite*>(sprtie1->getChildByName("Sprite_62_1"));
	auto Sprite_62_1_0 = static_cast<Sprite*>(sprtie1->getChildByName("Sprite_62_1_0"));
	auto Sprite_62_0_0 = static_cast<Sprite*>(sprtie1->getChildByName("Sprite_62_0_0"));

	player_name1 = static_cast<Text*>(Sprite_62->getChildByName("Text_11"));
	player_integral1 = static_cast<Text*>(Sprite_62->getChildByName("Text_2"));
	player_name2 = static_cast<Text*>(Sprite_62_0->getChildByName("Text_12"));
	player_integral2 = static_cast<Text*>(Sprite_62_0->getChildByName("Text_2_2"));
	player_name3 = static_cast<Text*>(Sprite_62_1->getChildByName("Text_13"));
	player_integral3 = static_cast<Text*>(Sprite_62_1->getChildByName("Text_2_3"));
	player_name4 = static_cast<Text*>(Sprite_62_1_0->getChildByName("Text_14"));
	player_integral4 = static_cast<Text*>(Sprite_62_1_0->getChildByName("Text_2_4"));
	player_name5 = static_cast<Text*>(Sprite_62_0_0->getChildByName("Text_15"));
	player_integral5 = static_cast<Text*>(Sprite_62_0_0->getChildByName("Text_2_5"));



	sprtie2 = static_cast<Sprite*>(scrollView->getChildByName("Sprite_45_0"));
	sprtie2->setVisible(false);
	auto Sprite_62_10 = static_cast<Sprite*>(sprtie2->getChildByName("Sprite_62_10"));
	auto Sprite_62_11 = static_cast<Sprite*>(sprtie2->getChildByName("Sprite_62_11"));
	auto Sprite_62_12 = static_cast<Sprite*>(sprtie2->getChildByName("Sprite_62_12"));
	auto Sprite_62_13 = static_cast<Sprite*>(sprtie2->getChildByName("Sprite_62_13"));
	auto Sprite_62_14 = static_cast<Sprite*>(sprtie2->getChildByName("Sprite_62_14"));


	player_name_1 = static_cast<Text*>(Sprite_62_10->getChildByName("Text_20"));
	player_integral_1 = static_cast<Text*>(Sprite_62_10->getChildByName("Text_20"));
	player_name_2 = static_cast<Text*>(Sprite_62_11->getChildByName("Text_21"));
	player_integral_2 = static_cast<Text*>(Sprite_62_11->getChildByName("Text_21"));
	player_name_3 = static_cast<Text*>(Sprite_62_12->getChildByName("Text_22"));
	player_integral_3 = static_cast<Text*>(Sprite_62_12->getChildByName("Text_22"));
	player_name_4 = static_cast<Text*>(Sprite_62_13->getChildByName("Text_23"));
	player_integral_4 = static_cast<Text*>(Sprite_62_13->getChildByName("Text_23"));
	player_name_5 = static_cast<Text*>(Sprite_62_14->getChildByName("Text_24"));
	player_integral_5 = static_cast<Text*>(Sprite_62_14->getChildByName("Text_24"));





	game = CardGame::getInstance();
	playernumbers(game->cishu);



	return true;
}

void RecordLayer::closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);


		Button*n = (Button*)sender;
		if (n->getTag() == 1)
		{
			removeAllChildrenWithCleanup(true);
			Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		}
	}

}

bool RecordLayer::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

void RecordLayer::playernumbers(int t)
{


	if (t == 1)
	{
		sprtie1->setVisible(true);
		player_integral1->setText(game->bottomPlayer[0][1]);

		player_integral2->setText(game->bottomPlayer[1][1]);

		player_integral3->setText(game->bottomPlayer[2][1]);

		player_integral4->setText(game->bottomPlayer[3][1]);

		player_integral5->setText(game->bottomPlayer[4][1]);


		player_name1->setText(game->bottomPlayer[0][0]);

		player_name2->setText(game->bottomPlayer[1][0]);


		player_name3->setText(game->bottomPlayer[2][0]);

		player_name4->setText(game->bottomPlayer[3][0]);

		player_name5->setText(game->bottomPlayer[4][0]);

	}
	else if(t == 2)
	{
		sprtie2->setVisible(true);

		player_integral_1->setText(game->bottomPlayer[0][1]);

		player_integral_2->setText(game->bottomPlayer[1][1]);

		player_integral_3->setText(game->bottomPlayer[2][1]);

		player_integral_4->setText(game->bottomPlayer[3][1]);

		player_integral_5->setText(game->bottomPlayer[4][1]);


		player_name_1->setText(game->bottomPlayer[0][0]);

		player_name_2->setText(game->bottomPlayer[1][0]);


		player_name_3->setText(game->bottomPlayer[2][0]);

		player_name_4->setText(game->bottomPlayer[3][0]);

		player_name_5->setText(game->bottomPlayer[4][0]);
	}
	else  if (t>=3)
	{
		sprtie1->setVisible(true);
		sprtie2->setVisible(true);
	}



}

