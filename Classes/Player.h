
#pragma once
//  玩家类
#include <cocos2d.h>
// 导入游戏单例类
#include "CardGame.h"


#include "network/HttpClient.h"
USING_NS_CC;
using namespace cocos2d::network;
using namespace cocos2d;
using namespace std;
class Player :public Ref{
public:
	
	string headImgUrl;
	string account; //账号名
	string account_id;//id
	string gender;//性别
	string avatar;//头像
	int position;//位置

	int money=5000;//金币
	int  zuanshi=100;//钻石
	char pos_char;
	Node *node;              //放置UI组件的节点 
	void createPlayerNode();
	Sprite *avatarSprite;
	int out = 0;
	//bool isdate = true;
	int loadImgSuccess = 0;
	int pq = 0;
	bool islook = false;
	Sprite*hide[3];

	int cards[26];//存放手牌
	void initCards();//初始化手牌防止数据冲突
	void sortCards();
	int countCards();//数牌



	Sprite *avararSprite;//头像精灵	
	void createHttpOfHeadImg(string headImgUrl, const cocos2d::network::ccHttpRequestCallback &callBack);
	void getHeadImgResponse(cocos2d::network::HttpClient*sender
		, cocos2d::network::HttpResponse*response);
};