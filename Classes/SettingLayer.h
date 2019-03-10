#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "CardGame.h"
#include "network/HttpClient.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::network;
using namespace std;
USING_NS_CC;
//Layer:层
//一个场景可以有多个Layer(Layer上可以有其他子节点)
class SettingLayer :public Layer {
public:
	CREATE_FUNC(SettingLayer);
	virtual bool init();
	EventListenerTouchOneByOne *listener;
	void closeButtonClicked(Ref *sender, Widget::TouchEventType type);
	bool onTouchBegan(Touch *touch, Event *event);
	void playernumbers(int t);
	CardGame*game;

	Sprite*player1;
	Sprite*player2;
	Sprite*player3;
	Sprite*player4;


	Text*player_integral1;
	Text*player_integral2;
	Text*player_integral3;
	Text*player_integral4;
	Text*player_integral5;


	Text*player_name1;
	Text*player_name2;
	Text*player_name3;
	Text*player_name4;
	Text*player_name5;

	Sprite *avararSprite1;//头像精灵	
	Sprite *avararSprite2;//头像精灵	
	Sprite *avararSprite3;//头像精灵	
	Sprite *avararSprite4;//头像精灵	
	Sprite *avararSprite5;//头像精灵	

	void createHttpOfHeadImg(string headImgUrl, const cocos2d::network::ccHttpRequestCallback &callBack);
	void getHeadImgResponse(cocos2d::network::HttpClient*sender
		, cocos2d::network::HttpResponse*response);
};