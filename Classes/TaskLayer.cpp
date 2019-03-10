#include "TaskLayer.h"
#include "constart.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CommonAudio.h"
using namespace std;
using namespace cocos2d::ui;
#pragma execution_character_set("utf-8")
USING_NS_CC;
bool TaskLayer::init() {
	if (!Layer::init()) {
		return false;
	}


	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TaskLayer::onTouchBegan, this);
	//吞没底层事件
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	
	auto rootNode = CSLoader::createNode("TaskLayer.csb");
	addChild(rootNode);

	auto scrollView = static_cast<ScrollView*>(rootNode->getChildByName("ScrollView_2"));

	Button* taskbtn = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	//添加监听
	taskbtn->addTouchEventListener(CC_CALLBACK_2(TaskLayer::closeButtonClicked, this));

	game = CardGame::getInstance();

	//const std::string& text = game->text;
	//float pmgressbar;

	//任务1
	auto Sprite1 = static_cast<Sprite*>(scrollView->getChildByName("vip_priceBg_8_0"));
	auto Sprite2 = static_cast<Sprite*>(Sprite1->getChildByName("progress_bg_1"));

	//文本
	auto textView1 = static_cast<Text*>(Sprite2->getChildByName("Text_2_0_0_0"));
	textView1->setText(game->text[0]);
	//进度条
	auto LoadingBar_1 = (LoadingBar*)Sprite2->getChildByName("LoadingBar_1");
	LoadingBar_1->setPercent(game->pmgressbar[0]);
	//按钮
    button1 = dynamic_cast<Button*>(Sprite1->getChildByName("Button_2"));
	button1->addTouchEventListener(CC_CALLBACK_2(TaskLayer::getButtonClicked1, this));
	button1->setBright(false);
	button1->setTouchEnabled(false);
	button1->setTag(2);

	//已经领取
	got1 = static_cast<Sprite*>(Sprite1->getChildByName("haveGot_7"));




	//任务2
	auto Sprite3 = static_cast<Sprite*>(scrollView->getChildByName("vip_priceBg_8_0_1"));
	auto Sprite4 = static_cast<Sprite*>(Sprite3->getChildByName("progress_bg_1_0"));
	//文本
	auto textView2 = static_cast<Text*>(Sprite4->getChildByName("Text_2_0_0_1"));
	textView2->setText(game->text[1]);
	//进度条
	auto LoadingBar_2 = (LoadingBar*)Sprite4->getChildByName("LoadingBar_3");
	LoadingBar_2->setPercent(game->pmgressbar[1]);
	//按钮
	button2 = dynamic_cast<Button*>(Sprite3->getChildByName("Button_3"));
	button2->addTouchEventListener(CC_CALLBACK_2(TaskLayer::getButtonClicked1, this));
	button2->setBright(false);
	button2->setTouchEnabled(false);
	button2->setTag(3);
	//已经领取
	got2 = static_cast<Sprite*>(Sprite3->getChildByName("haveGot_7_0"));


	//任务3
	auto Sprite5 = static_cast<Sprite*>(scrollView->getChildByName("vip_priceBg_8_0_1_0"));
	auto Sprite6	 = static_cast<Sprite*>(Sprite5->getChildByName("progress_bg_1_0_0"));
	//文本
	auto textView3 = static_cast<Text*>(Sprite6->getChildByName("Text_2_0_0_3"));
	textView3->setText(game->text[2]);
	//进度条
	auto LoadingBar_3 = (LoadingBar*)Sprite6->getChildByName("LoadingBar_4");
	LoadingBar_3->setPercent(game->pmgressbar[2]);
	//按钮
	button3 = dynamic_cast<Button*>(Sprite5->getChildByName("Button_4"));
	button3->addTouchEventListener(CC_CALLBACK_2(TaskLayer::getButtonClicked1, this));
	button3->setBright(false);
	button3->setTouchEnabled(false);
	button3->setTag(4);
	//已经领取
	got3 = static_cast<Sprite*>(Sprite5->getChildByName("haveGot_7_0_0"));



	//任务4
	auto Sprite7 = static_cast<Sprite*>(scrollView->getChildByName("vip_priceBg_8_0_1_0_0"));
	auto Sprite8 = static_cast<Sprite*>(Sprite7->getChildByName("progress_bg_1_0_0_0"));
	//文本
	auto textView4= static_cast<Text*>(Sprite8->getChildByName("Text_2_0_0_4"));
	textView4->setText(game->text[3]);
	//进度条
	auto LoadingBar_4 = (LoadingBar*)Sprite8->getChildByName("LoadingBar_5");
	LoadingBar_4->setPercent(game->pmgressbar[3]);
	//按钮
    button4 = dynamic_cast<Button*>(Sprite7->getChildByName("Button_5"));
	button4->addTouchEventListener(CC_CALLBACK_2(TaskLayer::getButtonClicked1, this));
	button4->setBright(false);
	button4->setTouchEnabled(false);
	button4->setTag(5);
	//已经领取
	got4 = static_cast<Sprite*>(Sprite7->getChildByName("haveGot_7_0_0_0"));

	if (game->genzhu == 34)
	{

		game->pmgressbar[3] = game->genzhu;
		game->text[3] = "1";
		LoadingBar_4->setPercent(game->pmgressbar[3]);
		textView4->setText(game->text[3]);
	}
	else  if (game->genzhu == 68)
	{
		game->pmgressbar[3] = game->genzhu;
		game->text[3] = "2";
		LoadingBar_4->setPercent(game->pmgressbar[3]);
		textView4->setText(game->text[3]);
	}
	else  if (game->genzhu >= 100)
	{
		game->pmgressbar[3] = game->genzhu;
		game->text[3] = "3";
		button4->setBright(true);
		button4->setTouchEnabled(true);
		LoadingBar_4->setPercent(game->pmgressbar[3]);
		textView4->setText(game->text[3]);
	}


	if (game->shengli==1)
	{

		button2->setBright(true);
		button2->setTouchEnabled(true);
		LoadingBar_2->setPercent(100);
		textView2->setText("1");



	}





	if (game->is_got[0] == false)
	{
		got1->setVisible(false);

	}
		if (game->is_got[1] == false)
	{
		got2->setVisible(false);
	}
		if (game->is_got[2] == false)
	{
		got3->setVisible(false);
	}
		if (game->is_got[3] == false)
	{
		got4->setVisible(false);
	}


	if (game->pmgressbar[0]==100&&game->is_got[0]==false)
	{

		button1->setBright(true);
		button1->setTouchEnabled(true);
	}
	 	if (game->pmgressbar[1] == 100 && game->is_got[1] == false)
	{

		button2->setBright(true);
		button2->setTouchEnabled(true);
	}
	 if (game->pmgressbar[2] == 100 && game->is_got[2] == false)
	{

		button3->setBright(true);
		button3->setTouchEnabled(true);
	}
	 if (game->pmgressbar[3] >=100 && game->is_got[3] == false)
	{

		button4->setBright(true);
		button4->setTouchEnabled(true);
	}



	 
		





	return true;
}



//关闭
void TaskLayer::closeButtonClicked(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {

		CommonAudio::playAudio(8);
		removeAllChildrenWithCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	}

}

void TaskLayer::getButtonClicked1(Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		return;
	}
	CommonAudio::playAudio(8);
	Button*n = (Button*)sender;
	switch (n->getTag())
	{

	case 2:
		game->jewel += 10;
		got1->setVisible(true);
		button1->setBright(false);
		button1->setTouchEnabled(false);
		game->is_got[0] = true;
		break;
	case 3:

		game->golds += 1000;
		got2->setVisible(true);
		button2->setBright(false);
		button2->setTouchEnabled(false);
		game->is_got[1] = true;
		game->shengli = 0;

		break;
	case 4:

		break;

	case 5:
		game->jewel += 5;
		got4->setVisible(true);
		button4->setBright(false);
		button4->setTouchEnabled(false);
		game->is_got[3] = true;
		game->genzhu = 0;
	break; 
	default:
		break;
	}



}


bool TaskLayer::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

