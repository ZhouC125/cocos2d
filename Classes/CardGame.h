#pragma once
#include "cocos2d.h"
#include <time.h>
#include "vector"
#include "Player.h"
USING_NS_CC;
using namespace std;
//枚举牌型
typedef enum {

	//单张
	POKER_TYPE_SINGLE,
	//对子
	POKER_TYPE_DOUBLE,
	//顺子
	POKER_TYPE_STRAIGHT,
	//金花
	POKER_TYPE_GOLDEN_FLOWER,
	//顺金
	POKER_TYPE_STRAIGHT_FLUSH,
	//豹子
	POKER_TYPE_LEOPARD,
}PokerType;
class CardGame
{
public:
	Node* card;
	CardGame();//构造函数

	void shuffle(int a[], int len);//洗牌函数
	bool gameDidBegan;//游戏是否开始
	int golds;   //金币
	int jewel;    //钻石
	static CardGame*getInstance();//游戏单例
	static void cleanInstance();//清理单例
	bool ispurchase=false;//是否购买金币

	int sort;   //商城选择金币类别
	bool  is_ok=false; //否充值成功
	bool is_pay=false;//是否支付

	bool is_denglu=false;//是否登录

	string account= "wanjiak"; //账号名

	string question="1" ; //账号名
	bool  is_got[4] = { false,false,false,false};//是否已经领取
	float pmgressbar[4] = { 0,0,0,0 };           //任务进度条
	std::string text[4] = { "0","0","0","0" };    //任务数字比例
	bool is_accomplish = false;                   //是否完成一局游戏
	bool  is_toot = false;
	bool is_access = false;                           //未完成一局游戏是否进入

	int ren;                                                  //玩家对战人机是的人数

	/*vector<string> topPlayer = { {"A","0"} };*/
	vector<vector<string>> bottomPlayer = { {"0","0"}, {"0","0"},{"0","0"},{"0","0"},{"0","0"} };

	bool is_again = false;                               //重玩

		//存放自己牌的节点
	Node* selfCards_node;
	
	int right_money;
	int rightupper_money ;
	int front_money ;
	int left_money;


	int genzhu = 0;                    //任务跟注3次
	int  shengli = 0;                    //任务胜利一次

	bool  is_yinxiao=true;                        //音效开关


	int  cishu;                           //战绩次数

	bool  is_do = true;
	//获取牌型
	PokerType getPokerTypeWithCards(vector<int> arr, const int *hua);
	//判断自己选择的牌能不能压过上家出的牌
	bool  biggerThanLast(vector<int> selfCards, vector<int> lastCards, const int *color1, const int *color2);
    
	int  shop();

};