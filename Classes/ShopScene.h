#pragma once
#include <cocos2d.h>
#include "ui/CocosGUI.h"

#include "CardGame.h"
using namespace cocos2d::ui;
USING_NS_CC;
class ShopScene :public Scene
{
public:
	static ShopScene* scene();
	CREATE_FUNC(ShopScene);
	virtual bool init();
	//����
	void backButtonclicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void fButtonClicked1(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	//��ֵ���ѿ�
	void  remind(int t);
	
	CardGame*game;//����
};
