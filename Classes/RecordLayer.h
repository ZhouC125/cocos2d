#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "CardGame.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d;
using namespace cocos2d::ui;
//Layer:层
//一个场景可以有多个Layer(Layer上可以有其他子节点)
class RecordLayer :public Layer {
public:
	CREATE_FUNC(RecordLayer);
	virtual bool init();
	EventListenerTouchOneByOne *listener;
	void closeButtonClicked(Ref *sender, Widget::TouchEventType type);
	bool onTouchBegan(Touch *touch, Event *event);
	void playernumbers(int t);
	CardGame*game;

	Sprite*sprtie1;
	Sprite*sprtie2;
	Sprite*sprtie3;
	Sprite*sprtie4;


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

	Text*player_integral_1;
	Text*player_integral_2;
	Text*player_integral_3;
	Text*player_integral_4;
	Text*player_integral_5;


	Text*player_name_1;
	Text*player_name_2;
	Text*player_name_3;
	Text*player_name_4;
	Text*player_name_5;
	
};