#include "GameScene.h"
#include "constart.h"
#include"ui/CocosGUI.h"
#include "CommonAnimation.h"
#include "CommonAudio.h"
#include "GameHall.h"
#include "SetLayer.h"
#include "cocostudio/CocoStudio.h"
#include "RemindLayer.h"
#include "TaskLayer.h"
#include "DengluScene.h"

#include "SettingLayer.h"


#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string

#pragma execution_character_set("utf-8")


using namespace std;
USING_NS_CC;
GameScene * GameScene::scene()
{
	return GameScene::create();
}
bool GameScene::init()
{
	if (!Scene::init())
		return false;
	


	auto Background = Sprite::create("1224720BG.jpg");
	float scaleW = VISIBLE_SIZE.width / Background->getBoundingBox().size.width;
	float scaleH = VISIBLE_SIZE.height / Background->getBoundingBox().size.width;
	Background->setScale(scaleW > scaleH ? scaleW : scaleH);
	Background->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	addChild(Background);

	// 加载素材
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameSence.plist", "GameSence.png");

	//添加玩家
	Button *addplayer= Button::create("tian.png");
	addplayer->setTag(1);
	addplayer->setScale(0.6);
	addplayer->setPosition(Vec2(VISIBLE_SIZE.width / 2-65, VISIBLE_SIZE.height / 2+50 ));
	addplayer->addTouchEventListener(CC_CALLBACK_2(GameScene::aaa, this));
	addChild(addplayer);
	//删除玩家
	Button *removeplayer = Button::create("shan.png");
	removeplayer->setTag(2);
	removeplayer->setScale(0.6);
	removeplayer->setPosition(Vec2(VISIBLE_SIZE.width / 2+60, VISIBLE_SIZE.height / 2+50 ));
	removeplayer->addTouchEventListener(CC_CALLBACK_2(GameScene::aaa, this));
	addChild(removeplayer);
	
	//开始按钮
	auto beginItem = Button::create("kai.png");
	beginItem->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2 ));
	beginItem->setScale(0.6);
	beginItem->addTouchEventListener(CC_CALLBACK_2(GameScene::beginGame, this));
	addChild(beginItem);

	//添加总分数
	_goldLabel = Label::create(String::createWithFormat("总分数:%d", Endpoints)->getCString(), "Arial", 46);
	_goldLabel->setAnchorPoint(Vec2(0, 0));
	_goldLabel->setPosition(Vec2(VISIBLE_SIZE.width *0.1-70, VISIBLE_SIZE.height-50 ));
	_goldLabel->setColor(Color3B::RED);
	//_goldLabel->setTag(500);
	_goldLabel->setVisible(false);
	addChild(_goldLabel);
	////////跟注/////////
	Button *Call = Button::create("action_follow.png");
	Call->setPosition(Vec2(VISIBLE_SIZE.width *0.25, VISIBLE_SIZE.height*0.1-VISIBLE_SIZE.height*0.9));
	Call->addTouchEventListener(CC_CALLBACK_2(GameScene::multiplyingpower, this));
	//Call->setScale(1.2);
	Call->setTag(20);
	_goldLabel->addChild(Call);
	////////加注/////////
	fill = Button::create("action_add.png");
	fill->setPosition(Vec2(VISIBLE_SIZE.width *0.34, VISIBLE_SIZE.height*0.1 - VISIBLE_SIZE.height*0.9));
	fill->addTouchEventListener(CC_CALLBACK_2(GameScene::multiplyingpower, this));
	//fill->setScale(1.2);
	fill->setTag(30);
	_goldLabel->addChild(fill);
	////////看牌/////////
	Button *look = Button::create("action_look.png");
	look->setPosition(Vec2(VISIBLE_SIZE.width *0.43, VISIBLE_SIZE.height*0.1 - VISIBLE_SIZE.height*0.9));
	look->addTouchEventListener(CC_CALLBACK_2(GameScene::multiplyingpower, this));
	look->setTag(50);
	_goldLabel->addChild(look);
	///////比牌///////
	compares = Button::create("action_cmp.png");
	compares->setPosition(Vec2(VISIBLE_SIZE.width *0.52, VISIBLE_SIZE.height*0.1 - VISIBLE_SIZE.height*0.9));
	compares->addTouchEventListener(CC_CALLBACK_2(GameScene::compare, this));
	compares->setTag(3);
	_goldLabel->addChild(compares);
	///////弃牌////////
	Button *abandon = Button::create("action_giveup.png");
	abandon->setPosition(Vec2(VISIBLE_SIZE.width *0.61, VISIBLE_SIZE.height*0.1 - VISIBLE_SIZE.height*0.9));
	abandon->addTouchEventListener(CC_CALLBACK_2(GameScene::multiplyingpower, this));
	abandon->setTag(60);
	_goldLabel->addChild(abandon);

	ta = Button::create("mahjongheadframe.png");
	ta->setPosition(Vec2(VISIBLE_SIZE.width-130, VISIBLE_SIZE.height / 2 + 60));
	ta->addTouchEventListener(CC_CALLBACK_2(GameScene::compare, this));
	ta->setScale(0.8);
	ta->setTag(4);
	ta->setVisible(false);
	addChild(ta, 2);


	ta1 = Button::create("mahjongheadframe.png");
	ta1->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 98, VISIBLE_SIZE.height*0.9 +15));
	ta1->addTouchEventListener(CC_CALLBACK_2(GameScene::compare, this));
	ta1->setTag(5);
	ta1->setScale(0.8);
	ta1->setVisible(false);
	addChild(ta1, 2);

	ta2 = Button::create("mahjongheadframe.png");
	ta2->setPosition(Vec2(VISIBLE_SIZE.width*0.3+66 , ta1->getPositionY()));
	ta2->addTouchEventListener(CC_CALLBACK_2(GameScene::compare, this));
	ta2->setTag(6);
	ta2->setScale(0.8);
	ta2->setVisible(false);
	addChild(ta2, 2);


	ta3 = Button::create("mahjongheadframe.png");
	ta3->setPosition(Vec2(VISIBLE_SIZE.width*0.1-82, VISIBLE_SIZE.height / 2 + 60));
	ta3->addTouchEventListener(CC_CALLBACK_2(GameScene::compare, this));
	ta3->setTag(7);
	ta3->setScale(0.8);
	ta3->setVisible(false);
	addChild(ta3, 2);

	

	game = CardGame::getInstance();
	player_self = new Player();
	player_right = new Player();
	player_rightupper = new Player();
	player_front = new Player();
	player_left = new Player();
	//没有登录，单机场
	if (!game->is_denglu)
	{
		RemindLayer *layer = RemindLayer::create();
		layer->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 260, VISIBLE_SIZE.height / 2 - 100));
		this->addChild(layer, 3);
		player_self->money = 5000;
		 player_right->money = 5000;
		 player_rightupper->money = 5000;
		player_front->money = 5000;
		player_left->money = 5000;

	}
	else if (game->is_denglu)
	{

		addplayer->setVisible(false);
		removeplayer->setVisible(false);
	



	}


	if (game->is_again)
	{

			player_self->money = game->golds;
			player_right->money = game->right_money;
			player_rightupper->money = game->rightupper_money;
			player_front->money = game->front_money;
			player_left->money = game->left_money;

		//	addplayer->setVisible(false);
		//	removeplayer->setVisible(false);

		///*	layer->removeFromParent();*/
		//	addplayers(game->ren);
		//	isdate_self = true;
		//		isdate_right = true;
	}


	players = __Array::create();
	players->retain();
	//自己
	if (game->is_denglu)
	{
		player_self->headImgUrl = ("http://www.telnote.cn/qqtouxiang/images/20120408/20120408093053751.jpg");

	}

	player_self->account = game->account;
	player_self->position = 1;
	self_money = player_self->money;
	loadPlayerUI(player_self);
	players->addObject(player_self);

	//添加自己分数
	_selfLabel = Label::create(String::createWithFormat("%d", player_self->money)->getCString(), "Arial", 20);
	_selfLabel->setPosition(Vec2(VISIBLE_SIZE.width*0.2 - 100, VISIBLE_SIZE.height*0.2 - 40));
	_selfLabel->setTextColor(Color4B(238, 199, 16, 200));
	this->addChild(_selfLabel, 3);



	Sprite *bvatarSprite3 = Sprite::create("bg_xiazhu (2).png");
	bvatarSprite3->setPosition(_selfLabel->getPositionX() - 11, _selfLabel->getPositionY());
	bvatarSprite3->setScaleY(0.9);
	bvatarSprite3->setScaleX(0.8);
	addChild(bvatarSprite3);

	auto _self_account = Label::createWithSystemFont(game->account.c_str(), "Arial", 20);
	_self_account->setPosition( 45, - 20);
	bvatarSprite3->addChild(_self_account);

	setting2 = Button::create("arrow_down.png");
	setting2->setPosition(Vec2(VISIBLE_SIZE.width - 80, VISIBLE_SIZE.height - 50));
	setting2->setScale(1.5);
	setting2->addTouchEventListener(CC_CALLBACK_2(GameScene::setting, this));
	addChild(setting2, 1);

	setting1 = Button::create("arrow_up.png");
	setting1->setPosition(Vec2(VISIBLE_SIZE.width - 80, VISIBLE_SIZE.height - 50));
	setting1->setScale(1.5);
	setting1->addTouchEventListener(CC_CALLBACK_2(GameScene::setting, this));
	setting1->setVisible(false);
	addChild(setting1, 1);
	b = Sprite::create("rank_bottom.png");
	b->setScaleX(0.9);
	b->setScaleY(0.9);
	b->setPosition(Vec2(VISIBLE_SIZE.width - 80, VISIBLE_SIZE.height - 150));
	b->setVisible(false);
	addChild(b, 3);





	CCSprite *s = CCSprite::create("xuanzhongkuang.png");
	//利用精灵创建进度条，并设置一些属性
	progresstime1 = CCProgressTimer::create(s);
	progresstime1->setPercentage(0.0f);    //设置初始百分比的值
	//转圈的CD实现
	progresstime1->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeRadial));
	progresstime1->setPosition(ccp(127, 89));
	progresstime1->setScaleY(0.38);
	progresstime1->setScaleX(0.458);

	//从中间到外的出现
	addChild(progresstime1, 1);






	auto taskbtn = Button::create("renwu_icon_glow1.png");
	taskbtn->setPosition(Vec2(VISIBLE_SIZE.width - 170, VISIBLE_SIZE.height - 45));
	taskbtn->setScale(0.7);
	taskbtn->addTouchEventListener(CC_CALLBACK_2(GameScene::taskButtonClicked, this));
	addChild(taskbtn, 1);
	CommonAudio::playAudio(10);	
	this->scheduleUpdate();


	return true;
}
//计时器
void  GameScene::updateReadyTimer(float delta)
{


	//ct1 = ct1 +1.3f;    //每帧+0.5%
	// 如果进度条小于100 % ，设置进度条的百分比

	tt1 += 1;


	if (tt1 <= 50)
	{

		progresstime1->setPercentage(tt1 * 2);
		if (tt1 == 20 && isie)
		{
			g1 += 1;
			tt1 = 0;
			isie = false;
		}
	
		if (ie == 1 && isdate_right&&g1 == 2)
		{
		/*	log("机器人1未淘汰");*/
			AIjudge(player_right, player_right->money, _rightLabel, player_right->pq, 340, 20);
			ie = 2;
			isie = true;


		}
		else  if (ie == 1 && !isdate_right&&g1 == 2)
		{
		/*	log("机器人1淘汰");*/
			ie = 2;
			g1 = 3;
		}
		if (ie == 2 && isdate_rightupper&& g1 == 3)
		{
/*			log("机器人2未淘汰");*/
			AIjudge(player_rightupper, player_rightupper->money, _rightupperLabel, player_rightupper->pq, 180, 200);
			ie = 3;
			isie = true;
		}
		else  if (ie == 2 && !isdate_rightupper&&g1 == 3)
		{
			//log("机器人2淘汰");
			ie = 3;
			g1 = 4;
		}
		if (ie == 3 && isdate_front&& g1 == 4)
		{
			//log("机器人3未淘汰");
			AIjudge(player_front, player_front->money, _frontLabel, player_front->pq, -130, 200);
			ie = 4;
			isie = true;
		}
		else  if (ie == 3 && !isdate_front&&g1 == 4)
		{
			//log("机器人3淘汰");
			ie = 4;
			g1 = 5;
		}
		if (ie == 4 && isdate_left&&g1 == 5)
		{
			//log("机器人4未淘汰");
			AIjudge(player_left, player_left->money, _leftLabel, player_left->pq, -345, 20);
			ie = 0;
			isie = true;
			/*	tt2 = 5;*/
		}
		else  if (ie == 4 && !isdate_left&&g1 == 5)
		{
			//log("机器人4淘汰");
			ie = 0;
			g1 = 0;

		}

		if (ie==0&&isdate_self)
		{

			isie = false;

		}
		else if (ie == 0 && !isdate_self)
		{
			//log("玩家淘汰");
			ie = 1;
			isie = true;
			g1 = 1;
			tt1 = 0;
		}

		if (ie == 1 && isdate_right)
		{
			tt2 = 1;
		}
		else  if (ie == 1 && !isdate_right)
		{
			tt2 = 1;
		}
		if (ie == 2 && isdate_rightupper)
		{
			tt2 = 2;
		}
		else  if (ie == 2 && !isdate_rightupper)
		{
			tt2 = 2;
		}
		if (ie == 3 && isdate_front)
		{
			tt2 = 3;
		}
		else  if (ie == 3 && !isdate_front)
		{
			tt2 = 3;
		}

		if (ie == 4 && isdate_left)
		{
			tt2 = 4;
		}
		else  if (ie == 4 && !isdate_left)
		{
			tt2 = 4;

		}

		if (tt2 == 1 && isdate_right&&tt1 == 1)
		{
			progresstime1->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 583, VISIBLE_SIZE.height / 2 + 58));

		}
		else  if (tt2 == 1 && !isdate_right&&tt1 == 1)
		{

			progresstime1->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 146, VISIBLE_SIZE.height / 2 + 260));
			tt2 = 2;

		}


		if (tt2 == 2 && isdate_rightupper&&tt1 == 1)
		{
			progresstime1->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 146, VISIBLE_SIZE.height / 2 + 315));

		}
		else  if (tt2 == 2 && !isdate_rightupper&&tt1 == 1)
		{
			progresstime1->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 156, VISIBLE_SIZE.height / 2 + 315));

			tt2 = 3;
		}


		if (tt2 == 3 && isdate_front&&tt1 == 1)
		{
			progresstime1->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 156, VISIBLE_SIZE.height / 2 + 315));


		}
		else  if (tt2 == 3 && !isdate_front&&tt1 == 1)
		{
			progresstime1->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 574, VISIBLE_SIZE.height / 2 + 56));
			tt2 = 4;
		}

		if (tt2 == 4 && isdate_left&&tt1 == 1)
		{
			progresstime1->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 574, VISIBLE_SIZE.height / 2 + 56));
		}

		else if (tt2 == 4 && !isdate_left&&tt1 == 1)
		{

			progresstime1->setPosition(ccp(127, 89));

			progresstime1->setVisible(false);
			tt2 = 0;

		}

		if (ie == 0 && isdate_self&&tt1 == 1)
		{
			progresstime1->setPosition(ccp(127, 89));
			progresstime1->setVisible(true);
		}

		else if (ie == 0 && !isdate_self&&tt1 == 1)
		{
			progresstime1->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 583, VISIBLE_SIZE.height / 2 + 58));
			progresstime1->setVisible(true);
			tt2 = 1;
		}
	}
else
{

operation(4, player_self, _selfLabel);
ie = 1;
g1 = 1;
tt1 = 0;
tt2 = 1;
isie = true;
compareframe(true);
return;



 }
}

void GameScene::update(float delta) {
	if (ie == 0)
	{
		bout = true;
	}
	else if (ie!=0)
	{
		bout = false;
	}
	if (currentzu==800)
	{
		//不可用状态
		fill->setBright(false);
		fill->setTouchEnabled(false);

	}



	if (!game->is_accomplish&&game->is_access)
	{
		/*game->is_toot = true;*/
		/*game->is_toot = true;*/
		game->is_access = false;
		game->is_toot = false;
		//game->is_accomplish = true;

	/*	Director::getInstance()->startAnimation();*/


	}
	int size = players->count();
	
	if (size == 1 && isbegin)
	{ 
		qs += 1;
		if (qs==100)
		{
			residue();
			//加载设置层
			SettingLayer *layer = SettingLayer::create();
			layer->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 190, VISIBLE_SIZE.height / 4 - 55));
			addChild(layer, 6);
			this->unschedule(schedule_selector(GameScene::updateReadyTimer));
			log("jieshu");
			isbegin = false;
			qs = 0;
		}

		
	}
 
	if (game->is_again)
	{

		

	}



	
}
void GameScene::aaa(Ref * sss, Widget::TouchEventType type)
{

	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}
	CommonAudio::playAudio(8);
	Menu*item = (Menu*)sss;
	if (item->getTag() == 1 && s < 4)
	{
		s = s + 1;
		menuItemClicked(s);
	}
	else  if (item->getTag() == 2 && s > 0)
	{

		s = s - 1;
		reducePlayer(s);
	}
}
void GameScene::reducePlayer(int r)
{
	//this->players = __Array::create();
	switch (r)
	{
	case 3:
	{
		player_left->node->removeAllChildrenWithCleanup(true);
	/*	player_left->isdate(false);*/
		isdate_left = false;
		CC_SAFE_DELETE(player_left);
		left = false;
		ren--;
		players->removeObject(player_left);
			bvatarSprite4->setVisible(false);
		_leftLabel->setVisible(false);
		break;
	}
	case 2:
	{
		player_front->node->removeAllChildrenWithCleanup(true);
		CC_SAFE_DELETE(player_front);
		front = false;
		isdate_front = false;
		ren--;
		players->removeObject(player_front);

		_frontLabel->setVisible(false);
		bvatarSprite2->setVisible(false);
		break;
	}
	case 1:
	{
		player_rightupper->node->removeAllChildrenWithCleanup(true);
		CC_SAFE_DELETE(player_rightupper);
		rightupper = false;
		isdate_rightupper = false;
		ren--;
		players->removeObject(player_rightupper);

		_rightupperLabel->setVisible(false);
		bvatarSprite1->setVisible(false);
		break;
	}case 0:
	{
		player_right->node->removeAllChildrenWithCleanup(true);
		CC_SAFE_DELETE(player_right);
		right = false;
		isdate_right = false;
		ren--;
		players->removeObject(player_right);

		_rightLabel->setVisible(false);
		bvatarSprite->setVisible(false);
		break;
	}
	}
}
void GameScene::loadPlayerUI(Player * player)
{
	//把椅子号转换成具体位置
	player->pos_char = getPlayerCharPosition(player->position);

	player->createPlayerNode();
	addChild(player->node);

}
char GameScene::getPlayerCharPosition(int pos)
{
	if (player_self->position == 1)
	{
		if (pos == 1) return 's';
		if (pos == 2) return 'r';
		if (pos == 3) return 'e';
		if (pos == 4) return 'f';
		if (pos == 5) return 'l';
	}
	/*else if (player_self->position == 2)
	{
		if (pos == 4) return 'e';
		if (pos == 1) return 'l';
		if (pos == 3) return 'r';
		if (pos == 5) return 'f';
	}
	else if (player_self->position == 3)
	{
		if (pos == 1) return 'f';
		if (pos == 2) return 'l';
		if (pos == 4) return 'r';
		if (pos == 5) return 'e';
	}
	else if (player_self->position == 4)
	{
		if (pos == 5) return 'r';
		if (pos == 2) return 'f';
		if (pos == 3) return 'l';
		if (pos == 1) return 'e';
	}
	else if (player_self->position == 5)
	{
		if (pos == 1) return 'r';
		if (pos == 3) return 'f';
		if (pos == 4) return 'l';
		if (pos == 2) return 'e';
	}*/

}

void GameScene::addplayers() {

	
	player_left->headImgUrl = ("http://imgsrc.baidu.com/imgad/pic/item/0e2442a7d933c89561219d5edb1373f0820200b3.jpg");
	player_front->headImgUrl = ("https://img4.duitang.com/uploads/item/201601/16/20160116161347_svH5y.thumb.224_0.jpeg");
	player_rightupper->headImgUrl = ("https://img4.duitang.com/uploads/item/201601/16/20160116161347_svH5y.thumb.224_0.jpeg");
	player_right->headImgUrl = ("https://img5.duitang.com/uploads/item/201409/20/20140920163111_fsSQj.thumb.700_0.png");

	player_right->account = "wanjiak_1";
	player_right->position = 2;
	loadPlayerUI(player_right);
	right = true;
	isdate_right = true;
	ren++;
	//player->addObject(player_right);
		//添加右侧分数
	_rightLabel = Label::create(String::createWithFormat("%d", player_right->money)->getCString(), "Arial", 20);
	//_rightLabel->setAnchorPoint(Vec2(0, 0));
	_rightLabel->setTextColor(Color4B(238, 199, 16, 200));
	_rightLabel->setPosition(Vec2(VISIBLE_SIZE.width - 41, VISIBLE_SIZE.height / 2 + 75));
	//_rightLabel->setVisible(false);
	//_rightLabel->setVisible(true);
	this->addChild(_rightLabel, 3);




	bvatarSprite = Sprite::create("bg_xiazhu (2).png");
	bvatarSprite->setPosition(_rightLabel->getPositionX() - 11, _rightLabel->getPositionY());
	bvatarSprite->setScaleY(0.9);
	bvatarSprite->setScaleX(0.8);
	addChild(bvatarSprite);
	auto _right_account = Label::createWithSystemFont(player_right->account.c_str(), "Arial", 20);
	_right_account->setPosition(45, -20);
	bvatarSprite->addChild(_right_account);


	player_rightupper->account = "wanjiak_2";
	player_rightupper->position = 3;
	isdate_rightupper = true;

	loadPlayerUI(player_rightupper);
	rightupper = true;
	ren++;
	//添加右上侧分数
	_rightupperLabel = Label::create(String::createWithFormat("%d", player_rightupper->money)->getCString(), "Arial", 20);
	_rightupperLabel->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 185, VISIBLE_SIZE.height - 43));
	_rightupperLabel->setTextColor(Color4B(238, 199, 16, 200));
	/*		_rightupperLabel->setVisible(false);*/
	this->addChild(_rightupperLabel, 3);
	//_rightupperLabel->setVisible(true);




	bvatarSprite1 = Sprite::create("bg_xiazhu (2).png");
	bvatarSprite1->setPosition(_rightupperLabel->getPositionX() - 11, _rightupperLabel->getPositionY());
	bvatarSprite1->setScaleY(0.9);
	bvatarSprite1->setScaleX(0.8);
	addChild(bvatarSprite1);
	auto _rightupper_account = Label::createWithSystemFont(player_rightupper->account.c_str(), "Arial", 20);
	_rightupper_account->setPosition(45, -20);
	bvatarSprite1->addChild(_rightupper_account);


	player_front->account = "wanjiak_3";
	player_front->position = 4;
	loadPlayerUI(player_front);
	isdate_front = true;
	front = true;
	ren++;
	//添加对面分数
	_frontLabel = Label::create(String::createWithFormat("%d", player_front->money)->getCString(), "Arial", 20);
	_frontLabel->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 120, VISIBLE_SIZE.height - 43));
	_frontLabel->setTextColor(Color4B(238, 199, 16, 200));
	this->addChild(_frontLabel, 3);




	bvatarSprite2 = Sprite::create("bg_xiazhu (2).png");
	bvatarSprite2->setPosition(_frontLabel->getPositionX() - 11, _frontLabel->getPositionY());
	bvatarSprite2->setScaleY(0.9);
	bvatarSprite2->setScaleX(0.8);
	addChild(bvatarSprite2);

	auto _front_account = Label::createWithSystemFont(player_front->account.c_str(), "Arial", 20);
	_front_account->setPosition(45, -20);
	bvatarSprite2->addChild(_front_account);


	//从左侧添加玩家
	player_left->account = "wanjiak_4";
	player_left->position = 5;
	loadPlayerUI(player_left);
	isdate_left = true;
	left = true;
	ren++;

	//添加左侧分数
	_leftLabel = Label::create(String::createWithFormat("%d", player_left->money)->getCString(), "Arial", 20);
	_leftLabel->setPosition(Vec2(135, VISIBLE_SIZE.height / 2 + 80));
	_leftLabel->setTextColor(Color4B(238, 199, 16, 200));
	this->addChild(_leftLabel, 3);




	bvatarSprite4 = Sprite::create("bg_xiazhu (2).png");
	bvatarSprite4->setPosition(_leftLabel->getPositionX() - 11, _leftLabel->getPositionY());
	bvatarSprite4->setScaleY(0.9);
	bvatarSprite4->setScaleX(0.8);
	addChild(bvatarSprite4);

	auto _left_account = Label::createWithSystemFont(player_left->account.c_str(), "Arial", 20);
	_left_account->setPosition(45, -20);
	bvatarSprite4->addChild(_left_account);


	players->addObject(player_right);
	right_money = player_right->money;

	players->addObject(player_rightupper);
	rightupper_money = player_rightupper->money;

	players->addObject(player_front);
	front_money = player_front->money;
	players->addObject(player_left);
	left_money = player_left->money;

}


void GameScene::menuItemClicked(int  sender)
{
	switch (sender)
	{

	case 1:
	{
	

		player_right->account = "wanjiak_1";
		player_right->position = 2;
		loadPlayerUI(player_right);
		right = true;
		isdate_right = true;
		ren++;
		players->addObject(player_right);

		
		right_money = player_right->money;
			//添加右侧分数
		_rightLabel = Label::create(String::createWithFormat("%d", player_right->money)->getCString(), "Arial", 20);
		//_rightLabel->setAnchorPoint(Vec2(0, 0));
		_rightLabel->setTextColor(Color4B(238, 199, 16, 200));
		_rightLabel->setPosition(Vec2(VISIBLE_SIZE.width - 41, VISIBLE_SIZE.height / 2 + 75));
		//_rightLabel->setVisible(false);
		//_rightLabel->setVisible(true);
		this->addChild(_rightLabel, 3);

		bvatarSprite = Sprite::create("bg_xiazhu (2).png");
		bvatarSprite->setPosition(_rightLabel->getPositionX() - 11, _rightLabel->getPositionY());
		bvatarSprite->setScaleY(0.9);
		bvatarSprite->setScaleX(0.8);
		addChild(bvatarSprite);

		auto _right_account = Label::createWithSystemFont(player_right->account.c_str(), "Arial", 20);
		_right_account->setPosition(45, -20);
		bvatarSprite->addChild(_right_account);

		break;
	}
	case 2:
	{
		
		player_rightupper->account = "wanjiak_2";
		player_rightupper->position = 3;
		isdate_rightupper = true;

		loadPlayerUI(player_rightupper);
		rightupper = true;
		ren++;


		players->addObject(player_rightupper);
		rightupper_money = player_rightupper->money;

		//添加右上侧分数
		_rightupperLabel = Label::create(String::createWithFormat("%d", player_rightupper->money)->getCString(), "Arial", 20);
		_rightupperLabel->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 185, VISIBLE_SIZE.height - 43));
		_rightupperLabel->setTextColor(Color4B(238, 199, 16, 200));
		/*		_rightupperLabel->setVisible(false);*/
		this->addChild(_rightupperLabel, 3);
		//_rightupperLabel->setVisible(true);

	bvatarSprite1 = Sprite::create("bg_xiazhu (2).png");
		bvatarSprite1->setPosition(_rightupperLabel->getPositionX() - 11, _rightupperLabel->getPositionY());
		bvatarSprite1->setScaleY(0.9);
		bvatarSprite1->setScaleX(0.8);
		addChild(bvatarSprite1);
		auto _rightupper_account = Label::createWithSystemFont(player_rightupper->account.c_str(), "Arial", 20);
		_rightupper_account->setPosition(45, -20);
		bvatarSprite1->addChild(_rightupper_account);
		break;

	}
	case 3:
	{
		
		player_front->account = "wanjiak_3";
		player_front->position = 4;
		loadPlayerUI(player_front);
		isdate_front = true;
		front = true;
		ren++;


		players->addObject(player_front);
		front_money = player_front->money;

		//添加对面分数
		_frontLabel = Label::create(String::createWithFormat("%d", player_front->money)->getCString(), "Arial", 20);
		_frontLabel->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 120, VISIBLE_SIZE.height - 43));
		_frontLabel->setTextColor(Color4B(238, 199, 16, 200));
		this->addChild(_frontLabel, 3);

		bvatarSprite2 = Sprite::create("bg_xiazhu (2).png");
		bvatarSprite2->setPosition(_frontLabel->getPositionX() - 11, _frontLabel->getPositionY());
		bvatarSprite2->setScaleY(0.9);
		bvatarSprite2->setScaleX(0.8);
		addChild(bvatarSprite2);

		auto _front_account = Label::createWithSystemFont(player_front->account.c_str(), "Arial", 20);
		_front_account->setPosition(45, -20);
		bvatarSprite2->addChild(_front_account);

		break;
	}
	case 4:
	{
		//从左侧添加玩家
		
		player_left->account = "wanjiak_4";
		player_left->position = 5;
		loadPlayerUI(player_left);
		isdate_left = true;
		left = true;
		ren++;

		players->addObject(player_left);
		left_money = player_left->money;

		//添加左侧分数
		_leftLabel = Label::create(String::createWithFormat("%d", player_left->money)->getCString(), "Arial", 20);
		_leftLabel->setPosition(Vec2(135, VISIBLE_SIZE.height / 2 + 80));
		_leftLabel->setTextColor(Color4B(238, 199, 16, 200));
		this->addChild(_leftLabel, 3);

		bvatarSprite4 = Sprite::create("bg_xiazhu (2).png");
		bvatarSprite4->setPosition(_leftLabel->getPositionX() - 11, _leftLabel->getPositionY());
		bvatarSprite4->setScaleY(0.9);
		bvatarSprite4->setScaleX(0.8);
		addChild(bvatarSprite4);

		auto _left_account = Label::createWithSystemFont(player_left->account.c_str(), "Arial", 20);
		_left_account->setPosition(45, -20);
		bvatarSprite4->addChild(_left_account);
		break;
	}

	}


}
void GameScene::beginGame(Ref *sender, Widget::TouchEventType type) {
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}
	if(game->is_denglu){
		addplayers();
}
	provide();
	CommonAudio::playAudio(8);
	if (isdate_self && isdate_right) {
	isbegin = true;
	//隐藏开始按钮
	Button*btn = (Button*)sender;
	btn->setVisible(false);
	getChildByTag(1)->setVisible(false);
	getChildByTag(2)->setVisible(false);
	_goldLabel->setVisible(true);
	meng();
	schedule(schedule_selector(GameScene::updateReadyTimer), 0.2, kRepeatForever, 0);
	game->ren = ren;


	//node = game->selfCards_node;
	if (game->is_denglu)
	{
		for (int i = 0; i < 5; i++) {

			CommonAnimation::jetton(100);

		}

		player_self->money - 100;
		player_right->money - 100;
		player_rightupper->money - 100;
		player_front->money - 100;
		player_left->money - 100;
	}
	


	}
	else {
		return;
	}


	



	//洗牌
	int cards[52];

	game->shuffle(cards, 52);

	//player_self->initCards();
	//player_right->initCards();
	//player_left->initCards();
	//player_front->initCards();

	Player *currentPlayer;
	for (int i = 0; i < 52; i++) {
		// 计算当前牌是发给哪个位置的
		char pos_char = getPlayerCharPosition(i % ren + 1);
		// 把当前遍历的牌给到对应的玩家
		if (pos_char == 's') {
			currentPlayer = player_self;
		}
		else if (pos_char == 'r') {
			currentPlayer = player_right;
		}
		else if (pos_char == 'e') {
			currentPlayer = player_rightupper;
		}
		else if (pos_char == 'f') {
			currentPlayer = player_front;
		}
		else if (pos_char == 'l') {
			currentPlayer = player_left;
		}
		// 发牌
		currentPlayer->cards[i / ren] = cards[i];
	}

	/*int test[3] = { 7,5,17 };
	for (int i = 0; i < 3; i++) {
		player_self->cards[i] = test[i];
	}
	int test1[3] = { 49,34,28 };
	for (int i = 0; i < 3; i++) {
		player_right->cards[i] = test1[i];
	}
	int test2[3] = { 32,5,15 };
	for (int i = 0; i < 3; i++) {
		player_rightupper->cards[i] = test2[i];
	}*/
	//int test3[3] = { 36,16,40 };
	//for (int i = 0; i < 3; i++) {
	//	player_front->cards[i] = test3[i];
	//}

	//3.展现自己的牌
	//排序
	player_self->sortCards();
	pai(player_self, -120, -160);
	if (right)
	{
		player_right->sortCards();
		pai(player_right, 300, 20);
	}
	if (rightupper)
	{
		player_rightupper->sortCards();
		pai(player_rightupper, 120, 200);
	}
	if (front)
	{
		player_front->sortCards();
		pai(player_front, -180, 200);
	}
	if (left)
	{
		player_left->sortCards();
		pai(player_left, -400, 20);
	}
}

void GameScene::pai(Player * ss, int a, int b)
{

	
	// 显示自己的牌
	for (int i = 0; i < 3; i++) {
		string file_name = "";
		// 如何得到花色？
		int flower = ss->cards[i] / 13 + 1;
		// 牌的值？
		int value = ss->cards[i] % 13 + 1;

		switch (flower) {
		case 1: // ??
			file_name = StringUtils::format("hei-%d.png", value);
			break;
		case 2: // ??
			file_name = StringUtils::format("fk-%d.png", value);
			break;
		case 3: // ??
			file_name = StringUtils::format("mh-%d.png", value);
			break;
		case 4: // ??
			file_name = StringUtils::format("hong-%d.png", value);
			break;
		default:
			break;
		}
		Sprite *cardSprite = Sprite::createWithSpriteFrameName(file_name);
		cardSprite->setScale(0.5);
		cardSprite->setPosition(Vec2(VISIBLE_SIZE.width / 2 + a + i * 60, VISIBLE_SIZE.height / 2 + b));
	addChild(cardSprite);
	}
}
void GameScene::compare(Ref * sss, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}
	CommonAudio::playAudio(8);
	Button*n = (Button*)sss;
	compareframe(false);
	if (n->getTag() == 4&& bout)
	{
		ie = 1;
		g1 = 1;
		tt1 = 0;
		tt2 = 1;
		isie = true;
		qipao(player_self, 5);
		if (player_right->islook)
		{
			for (int i = 0; i < 3; i++)
			{
				hide1[i]->setVisible(false);
			}
		}
	int q1=	cardtype(player_self, player_self->pq);
	int q2=	cardtype(player_right, player_right->pq);
	
		compareframe(true);
		operation(5, player_self, _selfLabel);
		if (q1 > q2)
		{
			CommonAnimation::runAnimation(-80, -160, 340, 20,player_self->account,player_right->account);
			abandon1(player_right);
			CommonAudio::playAudio(7);
		}
		else   if (q1 < q2)
		{
			CommonAnimation::runAnimation(340, 20, -80, -160, player_self->account, player_right->account);
			abandon1(player_self);
			CommonAudio::playAudio(6);
			/*selfs = false;*/
		}
		else  if (q1== q2)
		{
			cardtype1(player_self, player_right, 340, 20);
		}	
	}
	if (n->getTag() == 5)
	{
		ie = 1;
		g1 = 1;
		tt1 = 0;
		tt2 = 1;
		isie = true;
		qipao(player_self, 5);
		operation(5, player_self, _selfLabel);
		if (player_rightupper->islook)
		{
			for (int i = 0; i < 3; i++)
			{
				hide2[i]->setVisible(false);
			}
		}
	int q1=	 cardtype(player_self, player_self->pq);
	int q2=	cardtype(player_rightupper, player_rightupper->pq);
		compareframe(true);
		if (q1 == q2)
		{
			cardtype1(player_self, player_rightupper, 180, 200);
		}
		else  if (q1 > q2)
		{
	
			CommonAnimation::runAnimation(-80, -160, 180, 200, player_self->account, player_rightupper->account);
			abandon1(player_rightupper);
			CommonAudio::playAudio(7);
		}
		else  if (q1< q2)
		{

			CommonAnimation::runAnimation(180, 200, -80, -160, player_self->account, player_rightupper->account);
			abandon1(player_self);
			CommonAudio::playAudio(6);
		}


	}

	if (n->getTag() == 6)
	{
		ie = 1;
		g1 = 1;
		tt1 = 0;
		tt2 = 1;
		isie = true;
		qipao(player_self, 5);
		operation(5, player_self, _selfLabel);
		if (player_front->islook)
		{
			for (int i = 0; i < 3; i++)
			{
				hide3[i]->setVisible(false);
			}
		}
		int q1=cardtype(player_self, player_self->pq);
		int q2=cardtype(player_front, player_front->pq);
		compareframe(true);
		if (q1== q2)
		{
			cardtype1(player_self, player_front, -130, 200);
		}
		else  if (q1 > q2)
		{

			CommonAnimation::runAnimation(-80, -160, -130, 200, player_self->account, player_front->account);
			abandon1(player_front);
			CommonAudio::playAudio(7);
		}
		else  if (q1 < q2)
		{
			CommonAnimation::runAnimation(-130, 200, -80, -160, player_self->account, player_front->account);
			abandon1(player_self);
			CommonAudio::playAudio(6);

		}

	}


	if (n->getTag() == 7)
	{
		ie = 1;
		g1 = 1;
		tt1 = 0;
		tt2 = 1;
		isie = true;
		qipao(player_self, 5);
		operation(5, player_self, _selfLabel);
		if (player_left->islook)
		{
			for (int i = 0; i < 3; i++)
			{
				hide4[i]->setVisible(false);
			}
		}
		int q1=cardtype(player_self, player_self->pq);
		int q2=cardtype(player_left, player_left->pq);
		compareframe(true);
		if (q1== q2)
		{
			cardtype1(player_self, player_left, -345, 20);
		}
		else  if (q1 > q2)
		{
			CommonAnimation::runAnimation(-80, -160, -345, 20, player_self->account, player_left->account);
			abandon1(player_left);
			CommonAudio::playAudio(7);

		}
		else  if (q1 < q2)
		{
			CommonAnimation::runAnimation(-345, 20, -80, -160, player_self->account, player_left->account);
			abandon1(player_self);
			CommonAudio::playAudio(6);

		}
	}


}

int   GameScene::cardtype(Player * palayer, int qs)
{
	vector<int> arr;

	for (int i = 0; i < palayer->countCards(); i++)
	{
		arr.push_back(palayer->cards[i]);
		hua[i] = palayer->cards[i] / 13 + 1;
	}
	PokerType type = game->getPokerTypeWithCards(arr, hua);
	switch (type)
	{
	case POKER_TYPE_SINGLE:
		//log("单牌123");
		qs = 1;
		break;
	case POKER_TYPE_DOUBLE:
		//log("对子");
		qs = 2;
		break;
	case POKER_TYPE_STRAIGHT:
		//log("顺子");
		qs = 3;
		break;
	case POKER_TYPE_GOLDEN_FLOWER:
	//	log("金花");
		qs = 4;
		break;
	case POKER_TYPE_STRAIGHT_FLUSH:
		//log("顺金");
		qs = 5;
		break;
	case POKER_TYPE_LEOPARD:
	//	log("豹子");
		qs = 6;
		break;


	}
	//if (palayer == player_self)
	//{
	//	player_self->pq = qs;
	//	log("%d", player_self->pq);

	//}
	//else  if (palayer == player_right)
	//{
	//	player_right->pq = qs;
	//	log("%d", player_right->pq);

	//}
	//else  if (palayer == player_rightupper)
	//{
	//	player_rightupper->pq = qs;
	//}
	//else  if (palayer == player_front)
	//{
	//	player_front->pq = qs;
	//}
	//else  if (palayer == player_left)
	//{
	//	player_left->pq = qs;
	//}

	return qs;
}
void GameScene::cardtype1(Player * palayer1, Player * palayer2, int x, int y)
{

	vector<int> arr1;
	vector<int> arr2;
	for (int i = 0; i < palayer1->countCards(); i++)
	{
		arr1.push_back(palayer1->cards[i]);

		flower1[i] = palayer1->cards[i] / 13 + 1;
	}
	for (int j = 0; j < palayer2->countCards(); j++)
	{
		arr2.push_back(palayer2->cards[j]);

		flower2[j] = palayer2->cards[j] / 13 + 1;
	}
	bool can = game->biggerThanLast(arr1, arr2, flower1, flower2);
	if (can) {

		if (palayer1 == player_self)
		{
		//	log("player_self赢");
			CommonAnimation::runAnimation(-80, -160, x, y, palayer1->account, palayer2->account);
			abandon1(palayer2);
		}
		else 	if (palayer1 == player_right)
		{
		//	log("player_right赢");

			CommonAnimation::runAnimation(340, 20, x, y, palayer1->account, palayer2->account);
			abandon1(palayer2);
		}
		else 	if (palayer1 == player_rightupper)
		{
			//log("player_rightupper赢");

			CommonAnimation::runAnimation(180, 200, x, y, palayer1->account, palayer2->account);
			abandon1(palayer2);
		}
		else 	if (palayer1 == player_front)
		{
			//log("player_front赢");

			CommonAnimation::runAnimation(-130, 200, x, y, palayer1->account, palayer2->account);
			abandon1(palayer2);
		}
		else 	if (palayer1 == player_left)
		{
			//log("player_left赢");
			CommonAnimation::runAnimation(-345, 20, x, y, palayer1->account, palayer2->account);
			abandon1(palayer2);
		}
	}

	else {
		if (palayer1 == player_self)
		{
			CommonAnimation::runAnimation(x, y, -80, -160, palayer1->account, palayer2->account);
			abandon1(palayer1);

			/*selfs = false;*/
		}
		else 	if (palayer1 == player_right)
		{
		//	log("player_right输");
			CommonAnimation::runAnimation(x, y, 340, 20, palayer1->account, palayer2->account);
			abandon1(palayer1);
		}
		else 	if (palayer1 == player_rightupper)
		{
		//	log("player_rightupper输");
			CommonAnimation::runAnimation(x, y, 180, 200, palayer1->account, palayer2->account);
			abandon1(palayer1);
		}
		else 	if (palayer1 == player_front)
		{
		//	log("player_front输");
			CommonAnimation::runAnimation(x, y, -130, 200, palayer1->account, palayer2->account);
			abandon1(palayer1);
		}
		else 	if (palayer1 == player_left)
		{
		//	log("player_left输");
			CommonAnimation::runAnimation(x, y, -345, 20, palayer1->account, palayer2->account);
			abandon1(palayer1);
		}
	}
}

void GameScene::multiplyingpower(Ref * it, Widget::TouchEventType type)
{

	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}
	CommonAudio::playAudio(8);
	Button*n = (Button*)it;
	if (n->getTag() == 20 && bout)
	{
		//跟注
		operation(1, player_self, _selfLabel);
		qipao(player_self, 1);
		compareframe(true);
		ie = 1;
		g1 = 1;
		tt1 = 0;
		tt2 = 1;
		isie = true;

		game->genzhu += 34;
	}
	else  if (n->getTag() == 30 && bout)
	{
		//加注
		operation(2, player_self, _selfLabel);
		qipao(player_self, 2);
		compareframe(true);
		ie = 1;
		g1 = 1;
		tt1 = 0;
		isie = true;
	}
	else  if (n->getTag() == 50 && bout)
	{

		//看牌
		CommonAudio::playAudio(2);
		operation(3, player_self, _selfLabel);
		compareframe(true);
		for (int i = 0; i < 3; i++)
		{
			hide[i]->setVisible(false);
		}
		kanpai(player_self);
		qipao(player_self, 3);
	}
	else  if (n->getTag() == 60 && bout)
	{

		ie = 1;
		g1 = 1;
		tt1 = 0;
		isie = true;

		CommonAudio::playAudio(3);
		abandon(player_self);
		abandon1(player_self);
		compareframe(true);
		////加载设置层
		//SettingLayer *layer = SettingLayer::create();
		///*layer->setScale(0.1f);*/
		//addChild(layer, 4);

		/*qipao(player_self,4);*/

		 /*	qipao(player_right);
			qipao(player_rightupper);
			qipao(player_left);
			qipao(player_front);*/

			//CommonAnimation::runAnimation();



	}
}
//跟注,加注,看牌,弃牌,开牌
void GameScene::operation(int t, Player * player, Label*integrallabel)
{
	int shen;
	if (t == 1)
	{
	
		//log("跟注");
		if (!player->islook)
		{
	
			//跟注
			currentzu = currentzu ;
			player->money =player->money - currentzu;
			Endpoints = Endpoints + currentzu;
			log("%d", currentzu);
			_goldLabel->setString(StringUtils::format("%d", Endpoints));
			integrallabel->setString(StringUtils::format("%d", player->money));
			CommonAnimation::jetton(currentzu);
		
		}
		else  if (player->islook)
		{
			currentzu = currentzu ;
			player->money = player->money - currentzu * 2;
			log("%d", currentzu);
			Endpoints = Endpoints + currentzu * 2;
			_goldLabel->setString(StringUtils::format("%d", Endpoints));
			integrallabel->setString(StringUtils::format("%d", player->money));
			CommonAnimation::jetton(currentzu * 2);
		}
		CommonAudio::playAudio(5);
		CommonAudio::playAudio(0);
		qipao(player, 1);//气泡
	}
	else	if (t == 2)
	{
		//log("加注");
		if (!player->islook)
		{
			currentzu = currentzu +100;
			player->money = player->money - currentzu ;
			log("%d", currentzu);
			Endpoints = Endpoints + currentzu * 2;
			_goldLabel->setString(StringUtils::format("%d", Endpoints));
			integrallabel->setString(StringUtils::format("%d", player->money));

			CommonAnimation::jetton(currentzu);
		}
		else	if (player->islook)
		{
			currentzu = currentzu +100;
			player->money = player->money - currentzu*2;
			log("%d", currentzu);
			Endpoints = Endpoints + currentzu * 2;
			_goldLabel->setString(StringUtils::format("%d", Endpoints));
			integrallabel->setString(StringUtils::format("%d", player->money));

			CommonAnimation::jetton(currentzu * 2);
		}
		CommonAudio::playAudio(5);
		CommonAudio::playAudio(1);
		qipao(player, 2);//气泡
	}
	else	if (t == 3)
	{
		//log("看牌");
		player->islook = true;
		kanpai(player);
	
		qipao(player, 3);//气泡
	}
	else	if (t == 4)
	{
		//log("弃牌");
		abandon(player);
		abandon1(player);
		CommonAudio::playAudio(3);
		qipao(player, 4);
	}
	else	if (t == 5)
	{
		//log("开牌");
		if (!player->islook)
		{
			currentzu = currentzu;
			player->money = player->money - currentzu;
			log("%d", currentzu);
			Endpoints = Endpoints + currentzu;
			_goldLabel->setString(StringUtils::format("%d", Endpoints));
			integrallabel->setString(StringUtils::format("%d", player->money));
			CommonAnimation::jetton(currentzu);
		}
		else  if (player->islook)
		{
			currentzu = currentzu ;
			player->money = player->money - currentzu * 2;
			log("%d", currentzu);
			Endpoints = Endpoints + currentzu * 2;
			_goldLabel->setString(StringUtils::format("%d", Endpoints));
			integrallabel->setString(StringUtils::format("%d", player->money));
			CommonAnimation::jetton(currentzu * 2);
		}
		CommonAudio::playAudio(5);
		CommonAudio::playAudio(4);
		qipao(player, 5);//气泡


	}

	if (player->money<=0)
	{
      	auto giveup = Sprite::create("game_result_pochang_icon.png");
		giveup->setScale(1.5);
		if (player == player_self)
		{
			giveup->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 80, VISIBLE_SIZE.height / 2 - 160));
			isdate_self = false;
		}
		else  if (player == player_right)
		{
			giveup->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 360, VISIBLE_SIZE.height / 2 + 20));
			isdate_right = false;
		}
		else  if (player == player_rightupper)
		{
			giveup->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 180, VISIBLE_SIZE.height / 2 + 200));
			isdate_rightupper = false;
		}
		else  if (player == player_front)
		{
			giveup->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 130, VISIBLE_SIZE.height / 2 + 200));
			isdate_front = false;
		}
		else  if (player == player_left)
		{
			giveup->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 340, VISIBLE_SIZE.height / 2 + 20));
			isdate_left = false;
		}
		addChild(giveup, 3);

		abandon1(player);
	}

}
void GameScene::compareframe(bool is_boads)
{
	if (!is_boads&& bout)
	{
		if (ren == 2)
		{
			ta->setVisible(true);
		}
		if (ren == 3)
		{
			ta->setVisible(true);
			ta1->setVisible(true);
		}
		if (ren == 4)
		{
			ta->setVisible(true);
			ta1->setVisible(true);
			ta2->setVisible(true);
		}
		if (ren == 5)
		{
			ta->setVisible(true);
			ta1->setVisible(true);
			ta2->setVisible(true);
			ta3->setVisible(true);
		}
		//不可用状态
		compares->setBright(false);
		compares->setTouchEnabled(false);

	}
	else if (is_boads&& bout)
	{
		if (ren == 2)
		{
			ta->setVisible(false);
		}
		if (ren == 3)
		{
			ta->setVisible(false);
			ta1->setVisible(false);
		}
		if (ren == 4)
		{
			ta->setVisible(false);
			ta1->setVisible(false);
			ta2->setVisible(false);
		}
		if (ren == 5)
		{
			ta->setVisible(false);
			ta1->setVisible(false);
			ta2->setVisible(false);
			ta3->setVisible(false);
		}
		//不可用状态
		compares->setBright(true);
		compares->setTouchEnabled(true);
	}
	
}
//人机AI
void GameScene::AIjudge(Player*player, int integral, Label*integrallabel, int q, int x, int y)
{

	vector<int> zhi;
	int cocor[3];
	for (int i = 0; i < player->countCards(); i++)
	{
		zhi.push_back(player->cards[i]);
		cocor[i] = player->cards[i] / 13 + 1;
	}
	PokerType type = game->getPokerTypeWithCards(zhi, cocor);
	switch (type)
	{
	case POKER_TYPE_SINGLE: {

		int xx;
		if (!player->islook)
		{
			xx = rand() % 8;
		}
		else
		{
			xx = 6;
		}
		if (xx == 0 || xx == 1 || xx == 2)//跟注
		{
			operation(1, player, integrallabel);//跟注
			break;
		}
		else  if (xx == 3 || xx == 4 || xx == 7)//加注
		{
			if (currentzu <800)
			{
				operation(2, player, integrallabel);
				break;
			}
			else
			{
				operation(1, player, integrallabel);
				break;
			}
		}
		else  if (xx ==5)//看牌
		{
			if (player->cards[0] % 13 + 1 > 6)
			{
				int aa = rand() % 6;
				operation(3, player, integrallabel);
				if (aa == 0 || aa == 1)//跟注
				{
					operation(1, player, integrallabel);//跟注
					break;
				}
				else  if (aa == 2 || aa == 3)//加注
				{
					if (currentzu <800)
					{
						operation(2, player, integrallabel);
						break;
					}
					else
					{
						operation(1, player, integrallabel);
						break;
					}
				}
				else if (aa == 4 || aa == 5)//开牌
				{
					operation(5, player, integrallabel);
					
				 Open(q, player, x, y);
				
				}
				else if (aa == 6)//弃牌
				{
					operation(4, player, integrallabel);
					break;
				}
			}
			else
			{
				operation(4, player, integrallabel);
				break;
			}
		}
		else if (xx == 6 )//开牌
		{
			operation(5, player, integrallabel);
			
			 Open(q, player, x, y);
		
		}
		else if (xx == 8)//弃牌
		{
			operation(4, player, integrallabel);
			break;
		}
		break;
	}
	case POKER_TYPE_DOUBLE:
	{
		int xx1;
		if (!player->islook)
		{
			xx1 = rand() % 8;
		}
		else
		{
			xx1 = 5;
		}
		if (xx1 == 0 || xx1 == 1 || xx1 == 7)//跟注
		{
			operation(1, player, integrallabel);//跟注
			break;
		}
		else  if (xx1 == 3 || xx1 == 4 || xx1 == 2)//加注
		{
			if (currentzu <800)
			{
				operation(2, player, integrallabel);
				break;
			}
			else
			{
				operation(1, player, integrallabel);
				break;
			}
		}
		else  if (xx1 == 5 )//看牌
		{
			int aa1 = rand() % 6;
			operation(3, player, integrallabel);
			if (aa1 == 0 || aa1 == 1)//跟注
			{
				operation(1, player, integrallabel);//跟注
				break;
			}
			else  if (aa1 == 2 || aa1 == 3)//加注
			{
				if (currentzu <800)
				{
					operation(2, player, integrallabel);
					break;
				}
				else
				{
					operation(1, player, integrallabel);
					break;
				}
			}
			else if (aa1 == 4 || aa1 == 5)//开牌
			{
				operation(5, player, integrallabel);
			 Open(q, player, x, y);
			
			}
			else if (aa1 == 6)//弃牌
			{
				operation(4, player, integrallabel);
				break;
			}

		}
		else if (xx1 == 6 )//开牌
		{
			operation(5, player, integrallabel);
			 Open(q, player, x, y);
		

			break;

		}
		else if (xx1 == 8)//弃牌
		{
			operation(4, player, integrallabel);
		}
		break;
	}

	case POKER_TYPE_STRAIGHT:
		gen(integral, integrallabel, player, q, x, y);

		break;
	case POKER_TYPE_GOLDEN_FLOWER:
		gen(integral, integrallabel, player, q, x, y);
		break;
	case POKER_TYPE_STRAIGHT_FLUSH:
		gen(integral, integrallabel, player, q, x, y);
		break;
	case POKER_TYPE_LEOPARD:
		gen(integral, integrallabel, player, q, x, y);
		break;


	}


}
//随机操作
void GameScene::gen(int integral, Label*integrallabel, Player*player, int q, int x, int y)
{
	int  xx;
	if (!player->islook)
	{
		xx = rand() % 8;
	}
	else
	{
		xx = 5;
	}
	if (xx == 0 || xx == 1)//跟注
	{
		operation(1, player, integrallabel);
	}
	else  if (xx == 2 || xx == 3 || xx == 4)//加注
	{
		if (currentzu <800)
		{
			operation(2, player, integrallabel);
		}
		else
		{
			operation(1, player, integrallabel);
		}

	}
	else  if (xx == 5 )//看牌
	{
		int aa1 = rand() % 6;
		operation(3, player, integrallabel);
		if (aa1 == 0 || aa1 == 1)//跟注
		{
			operation(1, player, integrallabel);//跟注
		}
		else  if (aa1 == 2 || aa1 == 3)//加注
		{
			if (currentzu <800)
			{
				operation(2, player, integrallabel);
			}
			else
			{
				operation(1, player, integrallabel);
			}
		}
		else if (aa1 == 4 || aa1 == 5)//开牌
		{
			operation(5, player, integrallabel);
			 Open(q, player, x, y);
			
		}
		else if (aa1 == 6)//弃牌
		{
			operation(4, player, integrallabel);
		}

	}
	else if ( xx == 6||xx == 7)//开牌
	{
		operation(5, player, integrallabel);
		 Open(q, player, x, y);
		

	}
	else if (xx == 8)//弃牌
	{
		operation(4, player, integrallabel);
	}
}

void GameScene::abandon(Player * player)
{
	auto giveup = Sprite::create("qipai.png");
	giveup->setScale(1.5);
	if (player == player_self)
	{
		giveup->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 80, VISIBLE_SIZE.height / 2 - 160));
	}
	else  if (player == player_right)
	{
		giveup->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 360, VISIBLE_SIZE.height / 2 + 20));
	}
	else  if (player == player_rightupper)
	{
		giveup->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 180, VISIBLE_SIZE.height / 2 + 200));
	}
	else  if (player == player_front)
	{
		giveup->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 130, VISIBLE_SIZE.height / 2 + 200));
	}
	else  if (player == player_left)
	{
		giveup->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 340, VISIBLE_SIZE.height / 2 + 20));
	}
	addChild(giveup, 3);
}

void  GameScene::Open(int q, Player*player2, int x, int y)
{

	int  AIgos= rand() % 4;
	int  qs = cardtype(player2, q);


	if (AIgos == 0)
	{
		if (player2 == player_self || isdate_self == false)
		{
			Open1(q, player2, x, y);
		}
		else
		{
		     int  qs1=	cardtype(player_self, player_self->pq);
			if (qs1 > qs)
			{
				//log("输给player_self");
				CommonAnimation::runAnimation(-80, -160, x, y, player_self->account, player2->account);
				abandon1(player2);
			}
			else  if (qs1 < qs)
			{
			//	log("赢player_self");
				CommonAnimation::runAnimation(x, y, -80, -160, player_self->account, player2->account);
				abandon1(player_self);
			}
			else  if (qs1 == qs)
			{
				cardtype1(player_self, player2, x, y);
			}
		}
	}
	else  if (AIgos == 1)
	{
		if (player2 == player_right || isdate_right == false)
		{
			Open1(q, player2, x, y);
		}
else {
		    int qs2=	cardtype(player_right, player_right->pq);
			if (qs == qs2)
			{
				cardtype1(player2, player_right, x, y);

			}
			else  if (qs > qs2)
			{
				//log("赢player_right");

				CommonAnimation::runAnimation(x, y, 340, 20, player_right->account, player2->account);
				abandon1(player_right);

			}
			else  if (qs < qs2)
			{
			//	log("输player_right");

				CommonAnimation::runAnimation(340, 20, x, y, player_right->account, player2->account);
				abandon1(player2);

			}
		}
	}
	else  if (AIgos == 2)
	{
		if (player2 == player_rightupper || isdate_rightupper == false)
		{
			Open1(q, player2, x, y);
		}
		else
		{
		   int qs3=cardtype(player_rightupper, player_rightupper->pq);
			if (qs == qs3)
			{
				cardtype1(player_rightupper, player2, x, y);
			}
			else  if (qs > qs3)
			{
				//log("赢player_rightupper");;
				CommonAnimation::runAnimation(x, y, 180, 200, player_rightupper->account, player2->account);
				abandon1(player_rightupper);
			}
			else  if (qs < qs3)
			{
				//log("输player_rightupper");
				CommonAnimation::runAnimation(180, 200, x, y, player_rightupper->account, player2->account);
				abandon1(player2);
			}
		}
	}
	else  if (AIgos == 3)
	{
		if (player2 == player_front || isdate_front == false)
		{
			Open1(q, player2, x, y);
		}
		else {

			int  qs4=cardtype(player_front, player_front->pq);
			if (qs == qs4)
			{
				cardtype1(player_front, player2, x, y);
			}
			else  if (qs > qs4)
			{
				//log("赢player_front");

				CommonAnimation::runAnimation(x, y, -130, 200, player_front->account, player2->account);
				abandon1(player_front);
			}
			else  if (qs < qs4)
			{
				//log("输player_front");
				CommonAnimation::runAnimation(-130, 200, x, y, player_front->account, player2->account);
				abandon1(player2);
			}
		}
	}
	else  if (AIgos == 4)
	{
		if (player2 == player_left || isdate_left == false)
		{
			Open1(q, player2, x, y);
		}
	else {
			cardtype(player_left, player_left->pq);
			if (qs == player_left->pq)
			{
				cardtype1(player_left, player2, x, y);
			}
			else  if (qs > player_left->pq)
			{
			//	log("yingplayer_left");

				CommonAnimation::runAnimation(x, y, -345, 20, player_left->account, player2->account);
				abandon1(player_left);
			}
			else  if (qs < player_left->pq)
			{
				//log("输player_left");

				CommonAnimation::runAnimation(-345, 20, x, y, player_left->account, player2->account);
				abandon1(player2);
			}
		}
	}

}
void  GameScene::Open1(int q, Player*player2, int x, int y)
{

	int  AIgos = rand() % 4;
	int  qs = cardtype(player2, q);


	if (AIgos == 0)
	{
		if (player2 == player_self || isdate_self == false)
		{
			Open(q, player2, x, y);
		}
		else
		{
			int  qs1 = cardtype(player_self, player_self->pq);
			if (qs1 > qs)
			{
				//log("输给player_self");
				CommonAnimation::runAnimation(-80, -160, x, y, player_self->account, player2->account);
				abandon1(player2);
			}
			else  if (qs1 < qs)
			{
				//	log("赢player_self");
				CommonAnimation::runAnimation(x, y, -80, -160, player_self->account, player2->account);
				abandon1(player_self);
			}
			else  if (qs1 == qs)
			{
				cardtype1(player_self, player2, x, y);
			}
		}
	}
	else  if (AIgos == 1)
	{
		if (player2 == player_right || isdate_right == false)
		{
			Open(q, player2, x, y);
		}
		else {
			int qs2 = cardtype(player_right, player_right->pq);
			if (qs == qs2)
			{
				cardtype1(player2, player_right, x, y);

			}
			else  if (qs > qs2)
			{
				//log("赢player_right");

				CommonAnimation::runAnimation(x, y, 340, 20, player_right->account, player2->account);
				abandon1(player_right);

			}
			else  if (qs < qs2)
			{
				//	log("输player_right");

				CommonAnimation::runAnimation(340, 20, x, y, player_right->account, player2->account);
				abandon1(player2);

			}
		}
	}
	else  if (AIgos == 2)
	{
		if (player2 == player_rightupper || isdate_rightupper == false)
		{
			Open(q, player2, x, y);
		}
		else
		{
			int qs3 = cardtype(player_rightupper, player_rightupper->pq);
			if (qs == qs3)
			{
				cardtype1(player_rightupper, player2, x, y);
			}
			else  if (qs > qs3)
			{
				//log("赢player_rightupper");;
				CommonAnimation::runAnimation(x, y, 180, 200, player_rightupper->account, player2->account);
				abandon1(player_rightupper);
			}
			else  if (qs < qs3)
			{
				//log("输player_rightupper");
				CommonAnimation::runAnimation(180, 200, x, y, player_rightupper->account, player2->account);
				abandon1(player2);
			}
		}
	}
	else  if (AIgos == 3)
	{
		if (player2 == player_front || isdate_front == false)
		{
			Open(q, player2, x, y);
		}
		else {

			int  qs4 = cardtype(player_front, player_front->pq);
			if (qs == qs4)
			{
				cardtype1(player_front, player2, x, y);
			}
			else  if (qs > qs4)
			{
				//log("赢player_front");

				CommonAnimation::runAnimation(x, y, -130, 200, player_front->account, player2->account);
				abandon1(player_front);
			}
			else  if (qs < qs4)
			{
				//log("输player_front");
				CommonAnimation::runAnimation(-130, 200, x, y, player_front->account, player2->account);
				abandon1(player2);
			}
		}
	}
	else  if (AIgos == 4)
	{
		if (player2 == player_left || isdate_left == false)
		{
			Open(q, player2, x, y);
		}
		else {
			cardtype(player_left, player_left->pq);
			if (qs == player_left->pq)
			{
				cardtype1(player_left, player2, x, y);
			}
			else  if (qs > player_left->pq)
			{
				//	log("yingplayer_left");

				CommonAnimation::runAnimation(x, y, -345, 20, player_left->account, player2->account);
				abandon1(player_left);
			}
			else  if (qs < player_left->pq)
			{
				//log("输player_left");

				CommonAnimation::runAnimation(-345, 20, x, y, player_left->account, player2->account);
				abandon1(player2);
			}
		}
	}

}

void GameScene::abandon1(Player * player)
{
	//vector< Player* >::iterator k;
	if (player == player_self)
	{
		isdate_self = false;
		players->removeObject(player_self);

		CommonAnimation::weed(-535, -290);
	/* k = players.begin() ;
		players.erase(k);*/
	}
	else  if (player == player_right)
	{
		isdate_right= false;
		players->removeObject(player_right);

		CommonAnimation::weed(590, 60);
	/*	k = players.begin()+1;
		players.erase(k);*/
	}
	else  if (player == player_rightupper)
	{
		isdate_rightupper = false;
		players->removeObject(player_rightupper);

		CommonAnimation::weed(140, 315);
		/*k = players.begin() + 2;
		players.erase(k);*/
	}
	else  if (player == player_front)
	{
	isdate_front = false;
	players->removeObject(player_front);

	CommonAnimation::weed(-160, 315);
	/*	k = players.begin() + 3;
		players.erase(k);*/
	}
	else  if (player == player_left)
	{
		isdate_left= false;
		players->removeObject(player_left);

		CommonAnimation::weed(-610, 50);
		/*	k = players.begin() +4;
			players.erase(k);*/
	}

	//if (players.size() == 1)
	//{
	//	log("游戏结束");
	//	//加载设置层
	//	SettingLayer *layer = SettingLayer::create();
	//	/*layer->setScale(0.1f);*/
	//	addChild(layer, 6);
	//}

}
void GameScene::kanpai(Player*player)
{
	if (player == player_self)
	{
		Sprite*kan = Sprite::create("card_user_look.png");
		kan->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 40, VISIBLE_SIZE.height / 2 - 125));
		kan->setScale(0.8);
		addChild(kan, 4);
	}
	else if (player == player_right)
	{
		Sprite*kan1 = Sprite::create("card_user_look.png");
		kan1->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 460, VISIBLE_SIZE.height / 2 + 50));
		kan1->setScale(0.8);

		addChild(kan1, 4);
	}
	else  if (player == player_rightupper)
	{
		Sprite*kan1 = Sprite::create("card_user_look.png");
		kan1->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 280, VISIBLE_SIZE.height / 2 + 240));
		kan1->setScale(0.8);

		addChild(kan1, 4);
	}
	else  if (player == player_front)
	{
		Sprite*kan1 = Sprite::create("card_user_look.png");
		kan1->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 20, VISIBLE_SIZE.height / 2 + 240));
		kan1->setScale(0.8);


		addChild(kan1, 4);
	}
	else  if (player == player_left)
	{
		Sprite*kan1 = Sprite::create("card_user_look.png");
		kan1->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 240, VISIBLE_SIZE.height / 2 + 55));
		kan1->setScale(0.8);

		addChild(kan1, 4);
	}
}
void GameScene::meng()
{
	for (int i = 0; i < 3; i++) {
		if (ren==1)
		{
			hide[i] = Sprite::create("card_back_large.png");
			hide[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 120 + i * 60, VISIBLE_SIZE.height / 2 - 152));
			hide[i]->setScale(0.6);
			addChild(hide[i], 3);
		}
		if (ren==2)
		{

			hide[i] = Sprite::create("card_back_large.png");
			hide[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 120 + i * 60, VISIBLE_SIZE.height / 2 - 152));
			hide[i]->setScale(0.6);
			addChild(hide[i], 3);

			hide1[i] = Sprite::create("card_back_large.png");
			hide1[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 300 + i * 60, VISIBLE_SIZE.height / 2 + 10));
			hide1[i]->setScale(0.6);
			addChild(hide1[i], 3);
		}

		
		if (ren == 3)
		{

			hide[i] = Sprite::create("card_back_large.png");
			hide[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 120 + i * 60, VISIBLE_SIZE.height / 2 - 152));
			hide[i]->setScale(0.6);
			addChild(hide[i], 3);

			hide1[i] = Sprite::create("card_back_large.png");
			hide1[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 300 + i * 60, VISIBLE_SIZE.height / 2 + 10));
			hide1[i]->setScale(0.6);
			addChild(hide1[i], 3);

			hide2[i] = Sprite::create("card_back_large.png");
			hide2[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 120 + i * 60, VISIBLE_SIZE.height / 2 + 190));
			hide2[i]->setScale(0.6);
			addChild(hide2[i], 3);
		}
		if (ren == 4)
		{

			hide[i] = Sprite::create("card_back_large.png");
			hide[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 120 + i * 60, VISIBLE_SIZE.height / 2 - 152));
			hide[i]->setScale(0.6);
			addChild(hide[i], 3);

			hide1[i] = Sprite::create("card_back_large.png");
			hide1[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 300 + i * 60, VISIBLE_SIZE.height / 2 + 10));
			hide1[i]->setScale(0.6);
			addChild(hide1[i], 3);

			hide2[i] = Sprite::create("card_back_large.png");
			hide2[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 120 + i * 60, VISIBLE_SIZE.height / 2 + 190));
			hide2[i]->setScale(0.6);
			addChild(hide2[i], 3);

			hide3[i] = Sprite::create("card_back_large.png");
			hide3[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 180 + i * 60, VISIBLE_SIZE.height / 2 + 190));
			hide3[i]->setScale(0.6);
			addChild(hide3[i], 3);
		}
		if (ren == 5)
		{

			hide[i] = Sprite::create("card_back_large.png");
			hide[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 120 + i * 60, VISIBLE_SIZE.height / 2 - 152));
			hide[i]->setScale(0.6);
			addChild(hide[i], 3);

			hide1[i] = Sprite::create("card_back_large.png");
			hide1[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 300 + i * 60, VISIBLE_SIZE.height / 2 + 10));
			hide1[i]->setScale(0.6);
		addChild(hide1[i], 3);

			hide2[i] = Sprite::create("card_back_large.png");
			hide2[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 120 + i * 60, VISIBLE_SIZE.height / 2 + 190));
			hide2[i]->setScale(0.6);
			addChild(hide2[i], 3);

			hide3[i] = Sprite::create("card_back_large.png");
			hide3[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 180 + i * 60, VISIBLE_SIZE.height / 2 + 190));
			hide3[i]->setScale(0.6);
			addChild(hide3[i], 3);

			hide4[i] = Sprite::create("card_back_large.png");
			hide4[i]->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 400 + i * 60, VISIBLE_SIZE.height / 2 + 20));
			hide4[i]->setScale(0.6);
			addChild(hide4[i], 3);
		}
	}
}

void GameScene::qipao(Player * player, int i)
{
	Sprite* qp = Sprite::create("bubble_left.png");
	qp->setScale(0.6);
	if (player == player_self)
	{
		qp->setPosition(Vec2(VISIBLE_SIZE.width*0.3 - 145, VISIBLE_SIZE.height *0.2 - 70));
		Director::getInstance()->getRunningScene()->addChild(qp);
		qp->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		if (i == 1)
		{
			CCLabelTTF* labelFont = CCLabelTTF::create("跟注", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width*0.3 - 145, VISIBLE_SIZE.height *0.2 - 70));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
		else  if (i == 2)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("加注", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width*0.3 - 145, VISIBLE_SIZE.height *0.2 - 70));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));

		}
		else  if (i == 3)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("看牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width*0.3 - 145, VISIBLE_SIZE.height *0.2 - 70));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));

		}
		else  if (i == 4)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("弃牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width*0.3 - 145, VISIBLE_SIZE.height *0.2 - 70));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
		else   if (i == 5)
		{
			CCLabelTTF* labelFont = CCLabelTTF::create("比牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width*0.3 - 145, VISIBLE_SIZE.height *0.2 - 70));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}

	}
	else  if (player == player_right)
	{
		qp->setPosition(Vec2(VISIBLE_SIZE.width - 150, VISIBLE_SIZE.height / 2 + 85));
		qp->setRotation(180);
		Director::getInstance()->getRunningScene()->addChild(qp);
		qp->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		if (i == 1)
		{
			CCLabelTTF* labelFont = CCLabelTTF::create("跟注", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width - 150, VISIBLE_SIZE.height / 2 + 85));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
		else  if (i == 2)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("加注", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width - 150, VISIBLE_SIZE.height / 2 + 85));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));

		}
		else  if (i == 3)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("看牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width - 150, VISIBLE_SIZE.height / 2 + 85));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));

		}
		else  if (i == 4)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("弃牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width - 150, VISIBLE_SIZE.height / 2 + 85));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
		else   if (i == 5)
		{
			CCLabelTTF* labelFont = CCLabelTTF::create("比牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width - 150, VISIBLE_SIZE.height / 2 + 85));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
	}
	else  if (player == player_rightupper)
	{

		qp->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 290, VISIBLE_SIZE.height / 2 + 290));
		Director::getInstance()->getRunningScene()->addChild(qp);
		qp->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		if (i == 1)
		{
			CCLabelTTF* labelFont = CCLabelTTF::create("跟注", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 290, VISIBLE_SIZE.height / 2 + 290));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
		else  if (i == 2)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("加注", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 290, VISIBLE_SIZE.height / 2 + 290));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));

		}
		else  if (i == 3)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("看牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 290, VISIBLE_SIZE.height / 2 + 290));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));

		}
		else  if (i == 4)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("弃牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 290, VISIBLE_SIZE.height / 2 + 290));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
		else   if (i == 5)
		{
			CCLabelTTF* labelFont = CCLabelTTF::create("比牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width / 2 + 290, VISIBLE_SIZE.height / 2 + 290));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
	}
	else  if (player == player_front)
	{
		qp->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 20, VISIBLE_SIZE.height / 2 + 290));
		Director::getInstance()->getRunningScene()->addChild(qp);
		qp->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		if (i == 1)
		{
			CCLabelTTF* labelFont = CCLabelTTF::create("跟注", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 20, VISIBLE_SIZE.height / 2 + 290));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
		else  if (i == 2)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("加注", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 20, VISIBLE_SIZE.height / 2 + 290));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));

		}
		else  if (i == 3)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("看牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 20, VISIBLE_SIZE.height / 2 + 290));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));

		}
		else  if (i == 4)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("弃牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 20, VISIBLE_SIZE.height / 2 + 290));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
		else   if (i == 5)
		{
			CCLabelTTF* labelFont = CCLabelTTF::create("比牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 20, VISIBLE_SIZE.height / 2 + 290));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
	}
	else  if (player == player_left)
	{
		qp->setPosition(Vec2(VISIBLE_SIZE.width*0.1 + 100, VISIBLE_SIZE.height / 2 + 100));
		Director::getInstance()->getRunningScene()->addChild(qp);
		qp->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		if (i == 1)
		{
			CCLabelTTF* labelFont = CCLabelTTF::create("跟注", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width*0.1 + 100, VISIBLE_SIZE.height / 2 + 100));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
		else  if (i == 2)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("加注", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width*0.1 + 100, VISIBLE_SIZE.height / 2 + 100));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));

		}
		else  if (i == 3)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("看牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width*0.1 + 100, VISIBLE_SIZE.height / 2 + 100));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));

		}
		else  if (i == 4)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("弃牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width*0.1 + 100, VISIBLE_SIZE.height / 2 + 100));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
		else  if (i == 5)
		{

			CCLabelTTF* labelFont = CCLabelTTF::create("比牌", "arial.ttf", 26);
			labelFont->setPosition(Vec2(VISIBLE_SIZE.width*0.1 + 100, VISIBLE_SIZE.height / 2 + 100));
			Director::getInstance()->getRunningScene()->addChild(labelFont);
			labelFont->runAction(Sequence::create(DelayTime::create(1.5), RemoveSelf::create(), NULL));
		}
	}
}

void GameScene::setting(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}
	CommonAudio::playAudio(8);
	//cartoon = Cartoon::create();
	if (!issetting)
	{
		setting1->setVisible(true);
		setting2->setVisible(false);
		issetting = true;
		b->setVisible(true);
		settingbtn(issetting);

	}
	else
	{
		setting1->setVisible(false);
		setting2->setVisible(true);
		issetting = false;
		b->setVisible(false);
		settingbtn(issetting);
	}




}
void GameScene::settingbtn(bool s)
{

	Button*likaibtn = Button::create("li.png");
	likaibtn->setPosition(Vec2(50, 107));
	likaibtn->setScale(0.5);
	likaibtn->setTag(1);
	likaibtn->addTouchEventListener(CC_CALLBACK_2(GameScene::jump, this));
	b->addChild(likaibtn);

	Button*bangzhubtn = Button::create("bang.png");
	bangzhubtn->setPosition(Vec2(50, 67));
	bangzhubtn->setScale(0.5);
	bangzhubtn->setTag(2);
	bangzhubtn->addTouchEventListener(CC_CALLBACK_2(GameScene::jump, this));
	b->addChild(bangzhubtn);

	Button*shezhibtn = Button::create("she.png");
	shezhibtn->setPosition(Vec2(50, 27));
	shezhibtn->setScale(0.5);
	shezhibtn->setTag(3);
	shezhibtn->addTouchEventListener(CC_CALLBACK_2(GameScene::jump, this));
	b->addChild(shezhibtn);

}

void GameScene::jump(Ref * it, Widget::TouchEventType type) {
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}
	CommonAudio::playAudio(8);
	Menu*item = (Menu*)it;
	if (item->getTag() == 1)
	{
		if (!game->is_denglu)
		{

			Director::getInstance()->replaceScene(DengluScene::scene());//切换场景

		}
		else	if (game->is_denglu)
		{
		
			auto transition = TransitionMoveInR::create(0.5f, GameHall::create());
			Director::getInstance()->replaceScene(transition);//切换场景

		}
	}
	else if (item->getTag() == 2)
	{

		bangzhu = Sprite::create("guizhe.jpg");
		bangzhu->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
		addChild(bangzhu, 8);
		auto exitbtn = Button::create("close1.png");
		exitbtn->setScale(1.3);
		exitbtn->setPosition(Vec2(VISIBLE_SIZE.width/2+132,VISIBLE_SIZE.height/2+260));
		exitbtn->addTouchEventListener(CC_CALLBACK_2(GameScene::jump1, this));
		exitbtn->setTag(1);
		bangzhu->addChild(exitbtn, 8);
		setting1->setVisible(false);
		setting2->setVisible(true);
		issetting = false;
		b->setVisible(false);
		Director::getInstance()->stopAnimation();
	}
	else if (item->getTag() == 3)
	{
		if (type == Widget::TouchEventType::ENDED) {
			//加载设置层
			SetLayer *layer = SetLayer::create();
			layer->setPosition(Vec2(180 , 50));
			addChild(layer, 8);
			setting1->setVisible(false);
			setting2->setVisible(true);
			issetting = false;
			b->setVisible(false);
		}
	}
}

void GameScene::jump1(Ref * it, Widget::TouchEventType type) {

	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}
	CommonAudio::playAudio(8);
	Menu*item = (Menu*)it;
	if (item->getTag() == 1)
	{

		bangzhu->setVisible(false);
		Director::getInstance()->startAnimation();
	}



}

void GameScene::taskButtonClicked(Ref * it, Widget::TouchEventType type)
{

	if (type == Widget::TouchEventType::ENDED) {

		CommonAudio::playAudio(8);

		TaskLayer *layer = TaskLayer::create();
		layer->setPosition(Vec2(VISIBLE_SIZE.width / 2-80 , VISIBLE_SIZE.height / 4 - 55));
		layer->setScale(1.3);
		addChild(layer, 10);
	}


}

void GameScene::residue()
{
	int  shen1;
	int  shen2;
	int  shen3;
	int  shen4;
	int  shen5;

	string file_integral1;
	string file_integral2;
	string file_integral3;
	string file_integral4;
	string file_integral5;


	//if (ren==2)
	//{
	//	self_money_shen = player_self->money;
	//	right_money_shen = player_right->money;

	//	file_integral1 = player_self->account;
	//	file_integral2 = player_right->account;

	//	
	//

	//}
	//else 	if (ren == 3)
	//{
	//	self_money_shen = player_self->money;
	//	right_money_shen = player_right->money;
	//	rightupper_money_shen = player_rightupper->money;

	//	file_integral1 = player_self->account;
	//	file_integral2 = player_right->account;
	//	file_integral3 = player_rightupper->account;
	//
	//}
	//else 	if (ren == 4)
	//{
	//	self_money_shen = player_self->money;
	//	right_money_shen = player_right->money;
	//	rightupper_money_shen = player_rightupper->money;
	//	front_money_shen = player_front->money;


	//	file_integral1 = player_self->account;
	//	file_integral2 = player_right->account;
	//	file_integral3 = player_rightupper->account;
	//	file_integral4 = player_front->account;
	//}
	//else 	if (ren == 5)
	//{
		self_money_shen = player_self->money;
		right_money_shen = player_right->money;
		rightupper_money_shen = player_rightupper->money;
		front_money_shen = player_front->money;
		left_money_shen = player_left->money;


		file_integral1 = player_self->account;
		file_integral2 = player_right->account;
		file_integral3 = player_rightupper->account;
		file_integral4 = player_front->account;
		file_integral5 = player_left->account;
	//}


		

	if (isdate_self)
	{
	
			self_money_shen = self_money_shen + Endpoints;
			shen2 = right_money - right_money_shen;
		shen3 = rightupper_money - rightupper_money_shen;
		shen4 = front_money - front_money_shen;
		shen5 = left_money - left_money_shen;
	
		
		game->bottomPlayer[0][1] = Value(Endpoints).asString();
		game->bottomPlayer[1][1] = Value(shen2).asString();
		game->bottomPlayer[2][1] = Value(shen3).asString();
		game->bottomPlayer[3][1] = Value(shen4).asString();
		game->bottomPlayer[4][1] = Value(shen5).asString();



	
	     	game->bottomPlayer[0][0] = file_integral1;
		    game->bottomPlayer[1][0] = file_integral2;
			game->bottomPlayer[2][0] = file_integral3;
			game->bottomPlayer[3][0] = file_integral4;
			game->bottomPlayer[4][0] = file_integral5;

			game->shengli = 1;


	}
	else  if (isdate_right)
	{

		right_money_shen = right_money_shen + Endpoints;
		shen1 = self_money - self_money_shen;

		shen3 = rightupper_money - rightupper_money_shen;
		shen4 = front_money - front_money_shen;
		shen5 = left_money - left_money_shen;
		

		game->bottomPlayer[0][1] = Value(Endpoints).asString();
		game->bottomPlayer[1][1] = Value(shen1).asString();
		game->bottomPlayer[2][1] = Value(shen3).asString();
		game->bottomPlayer[3][1] = Value(shen4).asString();
		game->bottomPlayer[4][1] = Value(shen5).asString();


		game->bottomPlayer[0][0] = file_integral2;
		game->bottomPlayer[1][0] = file_integral1;
		game->bottomPlayer[2][0] = file_integral3;
		game->bottomPlayer[3][0] = file_integral4;
		game->bottomPlayer[4][0] = file_integral5;


	
	}
	else  if (isdate_rightupper)
	{
		rightupper_money_shen = rightupper_money_shen + Endpoints;
		shen1 = self_money - self_money_shen;
		shen2 = right_money - right_money_shen;
		shen4 = front_money - front_money_shen;
		shen5 = left_money - left_money_shen;
		
		game->bottomPlayer[0][1] = Value(Endpoints).asString();
		game->bottomPlayer[1][1] = Value(shen1).asString();
		game->bottomPlayer[2][1] = Value(shen2).asString();
		game->bottomPlayer[3][1] = Value(shen4).asString();
		game->bottomPlayer[4][1] = Value(shen5).asString();
		
		game->bottomPlayer[0][0] = file_integral3;
		game->bottomPlayer[1][0] = file_integral1;
		game->bottomPlayer[2][0] = file_integral2;
		game->bottomPlayer[3][0] = file_integral4;
		game->bottomPlayer[4][0] = file_integral5;

	}
	else  if (isdate_front)
	{
		front_money_shen = front_money_shen + Endpoints;
		shen1 = self_money - self_money_shen;
		shen2 = right_money - right_money_shen;
		shen3 = rightupper_money - rightupper_money_shen;
		shen5 = left_money - left_money_shen;

		game->bottomPlayer[0][1] = Value(Endpoints).asString();
		game->bottomPlayer[1][1] = Value(shen1).asString();
		game->bottomPlayer[2][1] = Value(shen2).asString();
		game->bottomPlayer[3][1] = Value(shen3).asString();
		game->bottomPlayer[4][1] = Value(shen5).asString();
		
		game->bottomPlayer[0][0] = file_integral4;
		game->bottomPlayer[1][0] = file_integral1;
		game->bottomPlayer[2][0] = file_integral2;
		game->bottomPlayer[3][0] = file_integral3;
		game->bottomPlayer[4][0] = file_integral5;

	}
	else  if (isdate_front)
	{
		left_money_shen = left_money_shen + Endpoints;
		shen1 = self_money - self_money_shen;
		shen2 = right_money - right_money_shen;
		shen3 = rightupper_money - rightupper_money_shen;
		shen4 = front_money - front_money_shen;
	
		game->bottomPlayer[0][1] = Value(Endpoints).asString();
		game->bottomPlayer[1][1] = Value(shen1).asString();
		game->bottomPlayer[2][1] = Value(shen2).asString();
		game->bottomPlayer[3][1] = Value(shen3).asString();
		game->bottomPlayer[4][1] = Value(shen4).asString();
			

		game->bottomPlayer[0][0] = file_integral5;
		game->bottomPlayer[1][0] = file_integral1;
		game->bottomPlayer[2][0] = file_integral2;
		game->bottomPlayer[3][0] = file_integral3;
		game->bottomPlayer[4][0] = file_integral4;
	}

		game->golds = self_money_shen;
		game->right_money = right_money_shen;
		game->rightupper_money = rightupper_money_shen;
		game->front_money = front_money_shen;
		game->left_money = left_money_shen;
	


		game->is_again = true;

		game->cishu += 1;


}

void GameScene::provide()
{
	if (game->golds<=0)
	{

		game->golds = 4000;
	}
	else if (game->right_money <= 0) {

		game->right_money = 4000;

	}
	else if (game->rightupper_money <= 0) {

		game->rightupper_money = 4000;

	}
	else if (game->front_money <= 0) {

		game->front_money = 4000;

	}
	else if (game->left_money <= 0) {

		game->left_money = 4000;

	}



}






