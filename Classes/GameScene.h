#pragma once
#include <cocos2d.h>
#include "Player.h"
#include"CardGame.h"
#include"ui/CocosGUI.h"
#include <array>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;

class GameScene :public Scene
{
public:
	static GameScene* scene();

	CREATE_FUNC(GameScene);
	virtual bool init();

	CardGame *game;
	Player * player_self;
	Player * player_left;
	Player * player_right;
	Player * player_front;
	Player*  player_rightupper;
	Button *ta;
	Button *ta1;
	Button *ta2;
	Button *ta3;
	Button *fill;
	int ren = 1;
	int s = 0;
	bool self = false;
	bool  left = false;
	bool  right = false;
	bool  front = false;
	bool  rightupper = false;

	int flower1[2];
	int flower2[2];
	int hua[3];


	float tt1 =0;
	int  tt2 = 0;
	int g1=0;
	int g2 = 0;
	int ct1 = 0;;
	bool isie = false;
	bool  isze = false;
	Label* _goldLabel;//总分数label
	Label* _selfLabel;//自己分数label
	Label* _rightLabel;//右侧分数label
	Label* _rightupperLabel;//右上分数label
	Label* _frontLabel;//对面分数label
	Label* _leftLabel;//左侧分数label

	int Endpoints=0;      //总分


	bool   isself=false;
	int currentzu = 100;

	bool isdate_self=true;
	bool isdate_right = false;
	bool isdate_rightupper = false;
	bool isdate_front = false;
	bool isdate_left = false;



	int bei1 = 1;
	int  check = 1;
	int g = 0;

	int i = 0;
	int j = 0;
	int y = 0;
	bool  e = true;
	Sprite*win;
	Sprite*lose;

	//bool  bipai = false;

	Sprite*hide[3];
	Sprite*hide1[3];
	Sprite*hide2[3];
	Sprite*hide3[3];
	Sprite*hide4[3];

	bool  bout = true;

	int  ie = 0;
	//std::vector<Player*>players;


	cocos2d::CCProgressTimer *progresstime1;
	Button *compares;
	Button* setting1;
	Button* setting2;
	bool  issetting = false;
	Sprite*b;
	//帮助
	Sprite*bangzhu;
	CCSprite *s2;
	bool isbegin=false;//是否开始游戏


	Sprite *bvatarSprite;
	Sprite *bvatarSprite1;
	Sprite *bvatarSprite2;
	Sprite *bvatarSprite4;


	//创建 _Array* 类型的变量list，参数为它的初始容量

	__Array* players;

	int self_money;
	int left_money;
	int right_money;
	int rightupper_money;
	int front_money;

	int self_money_shen;
	int left_money_shen;
	int right_money_shen;
	int rightupper_money_shen;
	int front_money_shen;

	int qs = 0;
	int  ss = 0;

private:
	void addplayers();

	//添加玩家
	void aaa(Ref*sss, Widget::TouchEventType type);
	//删除玩家
	void reducePlayer(int r);
	/*this->schedule(schedule_selector(GameScene::dijishenchen), 1);*/
	void update(float delta);//回调更新函数，该函数每一帧都被调用
	//加载玩家UI界面
	void loadPlayerUI(Player *player);
	//将椅子号1234转换成场景中的具体位置
	char getPlayerCharPosition(int pos);
	//菜单项被点击
	void menuItemClicked(int  sender);
	//开始游戏
	void beginGame(Ref *sender, Widget::TouchEventType type);
	void  pai(Player*ss, int a, int b);
	 //比牌
	void compare(Ref * sss, Widget::TouchEventType type);
	//牌型
	int   cardtype(Player*palayer,   int qs);
	//同类型牌比较
	void cardtype1(Player * palayer1, Player * palayer2, int x, int y);

	//加注
	void  multiplyingpower(Ref * it, Widget::TouchEventType type);
	//跟注,加注,看牌,弃牌
	void operation(int t,Player*player,Label*integrallabel);

	void 	compareframe(bool bipai);

	//人机判断
	void  AIjudge(Player*player,int integral, Label*integrallabel,int q, int x, int y);
	//人机比牌
	void  Open(int q, Player*player2,int x,int y);
	void  Open1(int q, Player*player2, int x, int y);
	void gen(int integral, Label*integrallabel,Player*player,int q, int x, int y);
  //弃牌
	void 	 abandon(Player*player);
	void  abandon1(Player*player);

	//看牌
	void  kanpai(Player*player);
	//蒙牌
	void meng();
	//气泡
	void qipao(Player*player,int i);
	//计时器
	void updateReadyTimer(float delta);
	//游戏场景按钮(退出,帮助,设置)
	void   setting(Ref* pSender, Widget::TouchEventType type);

	void settingbtn(bool s);
	//离开,帮助,设置按钮的跳转
	void jump(Ref * it, Widget::TouchEventType type);
	void jump1(Ref * it, Widget::TouchEventType type);

	void  taskButtonClicked(Ref * it, Widget::TouchEventType type);
	//结束后计算剩余的金币
	void   residue();
	//当玩家没有钱后发放金币
	void  provide();

};
