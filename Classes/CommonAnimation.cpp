#include "CommonAnimation.h"
#include "CommonAudio.h"
#include "constart.h"
#include "CardGame.h"
#pragma execution_character_set("utf-8")
using namespace std;
USING_NS_CC;
vector<int> a = { 10000,5000,2000,1000,800,500,200,100 };
vector<int> q = { 0,0,0,0,0,0,0,0 };

void CommonAnimation::runAnimation(int x, int y, int x1, int y1, std::string path_player, std::string path_player1) {

	CommonAudio::playAudio(4);
	  auto visibleSize = Director::getInstance()->getVisibleSize();
		Sprite* A = Sprite::create("vs6.png");
		A->setPosition(Vec2(visibleSize.width / 2 - 500, visibleSize.height / 2));
	
		Director::getInstance()->getRunningScene()->addChild(A,5);
		//Sprite* B = Sprite::create("vs6.png");
		//B->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		//B->setScale(0.5);
		//B->setOpacity(0);//可视度为0,1为完全可见
		//Director::getInstance()->getRunningScene()->addChild(B);

		Sprite* B = Sprite::create("vsbg.png");
		B->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		B->setScale(1.4);
		B->setOpacity(0);//可视度为0,1为完全可见
	   Director::getInstance()->getRunningScene()->addChild(B,4);
	   string path = path_player;
	   string path1 = path_player1;


	   CCLabelTTF* player = CCLabelTTF::create(path, "arial.ttf", 50);
	   player->setPosition(Vec2(260, 250));
	  B->addChild(player);
	  player->runAction(Sequence::create(DelayTime::create(2), RemoveSelf::create(), NULL));

	  CCLabelTTF* player1 = CCLabelTTF::create(path1, "arial.ttf", 50);
	  player1->setPosition(Vec2(700, 250));
	  B->addChild(player1);
	  player1->runAction(Sequence::create(DelayTime::create(2), RemoveSelf::create(), NULL));


		MoveBy* moveby = MoveBy::create(0.6f, Vec2(500, 0));
		FadeOut* fadeout = FadeOut::create(0.15f);
		FadeIn* fadeIn = FadeIn::create(1);
		auto	  win = Sprite::create("bipaiying.png");
		win->setPosition(Vec2(VISIBLE_SIZE.width / 2 + x, VISIBLE_SIZE.height / 2 + y));
		win->setOpacity(0);//可视度为0,1为完全可见
		win->setScale(1.2);
		Director::getInstance()->getRunningScene()->addChild(win, 3);

		win->runAction(Sequence::create(DelayTime::create(2.5), fadeIn,DelayTime::create(3), RemoveSelf::create(), NULL));
		auto  	lose = Sprite::create("bipaishu.png");
		lose->setPosition(Vec2(VISIBLE_SIZE.width / 2 + x1, VISIBLE_SIZE.height / 2 + y1));
		lose->setScale(1.2);
		lose->setOpacity(0);//可视度为0,1为完全可见
		FadeIn* fadeIn1 = FadeIn::create(1);
		Director::getInstance()->getRunningScene()->addChild(lose, 3);
		lose->runAction(Sequence::create(DelayTime::create(2.5), fadeIn1, DelayTime::create(3), RemoveSelf::create(), NULL));
		A->runAction(Sequence::create(moveby, DelayTime::create(2), fadeout, RemoveSelf::create(),  NULL));

	/*	FadeIn* fadeIn = FadeIn::create(1);*/
		B->runAction(Sequence::create(fadeIn, DelayTime::create(2), fadeout, RemoveSelf::create(), NULL));

	/*	isjieshu = true;*/


}
void CommonAnimation::weed(int x, int y)
{

	auto wd = Sprite::create("eliminate.png");
	wd->setScale(0.5);
	wd->setPosition(Vec2(VISIBLE_SIZE.width / 2 + x, VISIBLE_SIZE.height / 2 + y));
	wd->setOpacity(0);//可视度为0,1为完全可见
	Director::getInstance()->getRunningScene()->addChild(wd, 3);
	FadeIn* fadeIn = FadeIn::create(1);
	wd->runAction(Sequence::create(DelayTime::create(0.8), fadeIn,  NULL));
}

void CommonAnimation::Payphone(std::string a)
{

	vector<Sprite*>sprite;
	int  xx =500+ rand() % 270;
	int  yy = 300 + rand() % 130;
	auto y = Sprite::create(a);
	sprite.push_back(y);
	y->setScale(0.7);
	y->setPosition(Vec2(xx,yy));
	Director::getInstance()->getRunningScene()->addChild(y, 3);



}
///购买提示场景
void CommonAnimation::ShopAnimation(int i)
{
	if (i==1)
	{
	

	
	}
	else	if (i == 2)
	{

		


	}




}

//void CommonAnimation::shopfor(int a, int q)
//{
//
//
//
//	//金币
//auto _moneyLabel = Label::create(String::createWithFormat("%d", a)->getCString(), "Arial", 25);
//   _moneyLabel->setAnchorPoint(Vec2(0, 0));
//   _moneyLabel->setPosition(Vec2((VISIBLE_SIZE.width / 2 + 135) * 0.05  , VISIBLE_SIZE.height*0.943+16));
//   Director::getInstance()->getRunningScene()->addChild(_moneyLabel, 3);
//
//   //钻石
//  auto    _jewelLabel = Label::create(String::createWithFormat("%d", q)->getCString(), "Arial", 25);
//   _jewelLabel->setAnchorPoint(Vec2(0, 0));
//   _jewelLabel->setPosition(Vec2((VISIBLE_SIZE.width / 2 + 235) * 0.05, VISIBLE_SIZE.height*0.943 + 16));
//   Director::getInstance()->getRunningScene()->addChild(_jewelLabel, 3);
//}

void CommonAnimation::jetton(int money)
{
	int shen=0;                                                           //定义剩下的金币
	for (int i = 0; i < a.size(); i++)                              //for循环总面值的筹码
	{
		q[i] = money /a[i];                                           //判断当前金币可以除尽当前面值的筹码
		int e = q[i];        
		if (q[i] >0)
		{
			shen = money - a[i] * q[i];                          //给剩余的钱赋值
			if (shen>0)
			{
				money = shen;
			}
			else
			{
				break;
			}
		}
		else
		{
		for (int j= 0; j < e; j++)
			{
				string	name = StringUtils::format("chouma/chip_%d.png", a[i]);          //筹码图片
				Payphone(name);
				
			}
	         
			if (shen<=0)
			{
				q={ 0, 0, 0, 0, 0, 0, 0, 0 };
			}
		
		}
		
	}
	for (int i = 0; i < q.size(); i++)
	{
		/*log("%d", q[i]);*/
		if (q[i] > 0)
		{
			for (int j = 0; j < q[i]; j++)
			{
				string	name = StringUtils::format("chouma/chip_%d.png", a[i]);
				Payphone(name);
			}

		}

	}
	
}


