#include "SettingLayer.h"
#include "constart.h"
#include "audio/include/SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "GameHall.h"
#include "DengluScene.h"
#include "GameScene.h"
using namespace std;
using namespace cocos2d::ui;
USING_NS_CC;
bool SettingLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SettingLayer::onTouchBegan, this);
	//吞没底层事件
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto rootNode = CSLoader::createNode("SettingLayer.csb");
	//rootNode->setPosition(Vec2(VISIBLE_SIZE.width / 2-333, VISIBLE_SIZE.height / 2-187));
	addChild(rootNode);

	//通过按钮的名字获得按钮
	Button* button = dynamic_cast<Button*>(rootNode->getChildByName("Button_9"));
	//添加监听
	button->addTouchEventListener(CC_CALLBACK_2(SettingLayer::closeButtonClicked, this));
	button->setTag(1);

	Button* button1 = dynamic_cast<Button*>(rootNode->getChildByName("Button_10"));
	//添加监听
	button1->addTouchEventListener(CC_CALLBACK_2(SettingLayer::closeButtonClicked, this));
	button1->setTag(2);

	   player1 = static_cast<Sprite*>(rootNode->getChildByName("biao1"));
	   player2 = static_cast<Sprite*>(rootNode->getChildByName("biao1_0"));
	   player3 = static_cast<Sprite*>(rootNode->getChildByName("biao1_1"));
	   player4 = static_cast<Sprite*>(rootNode->getChildByName("biao1_2"));

	   player_integral1 = static_cast<Text*>(rootNode->getChildByName("Text_2"));
	   player_integral2 = static_cast<Text*>(player1->getChildByName("Text_2_0"));
	   player_integral3 = static_cast<Text*>(player2->getChildByName("Text_2_1"));
	   player_integral4 = static_cast<Text*>(player3->getChildByName("Text_2_2"));
	   player_integral5 = static_cast<Text*>(player4->getChildByName("Text_2_3"));


	   player_name1 = static_cast<Text*>(rootNode->getChildByName("Text_11"));
	   player_name2 = static_cast<Text*>(player1->getChildByName("Text_1"));
	   player_name3 = static_cast<Text*>(player2->getChildByName("Text_2"));
	   player_name4 = static_cast<Text*>(player3->getChildByName("Text_3"));
	   player_name5 = static_cast<Text*>(player4->getChildByName("Text_4"));

	//用户名、胜负

	game = CardGame::getInstance();

	playernumbers(game->ren);

	string file_name1;
	string file_name2;
	string file_name3;
	string file_name4;
	string file_name5;


	string file_integral1;
	string file_integral2;
	string file_integral3;
	string file_integral4;
	string file_integral5;



	file_integral1 = game->bottomPlayer[0][1];
	player_integral1->setText(file_integral1);

	file_integral2 = game->bottomPlayer[1][1];
	player_integral2->setText(file_integral2);

	file_integral3 = game->bottomPlayer[2][1];
	player_integral3->setText(file_integral3);

	file_integral4 = game->bottomPlayer[3][1];
	player_integral4->setText(file_integral4);

	file_integral5 = game->bottomPlayer[4][1];
	player_integral5->setText(file_integral5);



	file_name1 = game->bottomPlayer[0][0];
	player_name1->setText(file_name1);

	file_name2 = game->bottomPlayer[1][0];
	player_name2->setText(file_name2);


	file_name3 = game->bottomPlayer[2][0];
	player_name3->setText(file_name3);

		file_name4 = game->bottomPlayer[3][0];
	player_name4->setText(file_name4);

	file_name5 = game->bottomPlayer[4][0];
	player_name5->setText(file_name5);



	auto node1 = static_cast<Node*>(rootNode->getChildByName("Node_1"));
	auto node2 = static_cast<Node*>(player1->getChildByName("Node_1_0"));
	auto node3 = static_cast<Node*>(player2->getChildByName("Node_1_0_0"));
	auto node4 = static_cast<Node*>(player3->getChildByName("Node_1_0_0_0"));
	auto node5 = static_cast<Node*>(player4->getChildByName("Node_1_0_0_0_0"));



	avararSprite1 = Sprite::create("101.png");
	Node *stencil = Node::create();//模板节点
	Sprite *circle = Sprite::create("avatar1.png");
	circle->setScale(120.f / 410);
	stencil->addChild(circle);
	ClippingNode  *clippingNode = ClippingNode::create(stencil);//需要模板
	clippingNode->addChild(avararSprite1); //模板和图片尺寸尽量相同
	//Alpha阀值：
	clippingNode->setAlphaThreshold(0.9);
	clippingNode->setInverted(false);
	clippingNode->setPosition(Vec2(node1->getPositionX(), node1->getPositionY()));
	clippingNode->setTag(1);
	addChild(clippingNode, 5);




	avararSprite2 = Sprite::create("101.png");
	Node *stencil1 = Node::create();//模板节点
	Sprite *circle1 = Sprite::create("avatar1.png");
	circle1->setScale(120.f / 410);
	stencil1->addChild(circle1);

	ClippingNode  *clippingNode1 = ClippingNode::create(stencil1);//需要模板
	clippingNode1->addChild(avararSprite2); //模板和图片尺寸尽量相同
	//Alpha阀值：
	clippingNode1->setAlphaThreshold(0.9);
	clippingNode1->setInverted(false);
	clippingNode1->setPosition(Vec2(node1->getPositionX(), node1->getPositionY()-73));
	clippingNode1->setTag(1);
	addChild(clippingNode1, 5);


	avararSprite3 = Sprite::create("101.png");
	Node *stencil2 = Node::create();//模板节点
	Sprite *circle2 = Sprite::create("avatar1.png");
	circle2->setScale(120.f / 410);
	stencil2->addChild(circle2);
	ClippingNode  *clippingNode2 = ClippingNode::create(stencil2);//需要模板
	clippingNode2->addChild(avararSprite3); //模板和图片尺寸尽量相同

//Alpha阀值：
	clippingNode2->setAlphaThreshold(0.9);
	clippingNode2->setInverted(false);
	clippingNode2->setPosition(Vec2(node1->getPositionX(), node1->getPositionY()-140));
	clippingNode2->setTag(1);
	addChild(clippingNode2, 5);

	avararSprite4= Sprite::create("101.png");
	Node *stencil3= Node::create();//模板节点
	Sprite *circle3 = Sprite::create("avatar1.png");
	circle3->setScale(120.f / 400);
	stencil3->addChild(circle3);
	ClippingNode  *clippingNode3= ClippingNode::create(stencil3);//需要模板
	clippingNode3->addChild(avararSprite4); //模板和图片尺寸尽量相同

//Alpha阀值：
	clippingNode3->setAlphaThreshold(0.9);
	clippingNode3->setInverted(false);
	clippingNode3->setPosition(Vec2(node1->getPositionX(), node1->getPositionY()-213));
	clippingNode3->setTag(1);
	addChild(clippingNode3, 5);


	avararSprite5 = Sprite::create("101.png");
	Node *stencil4 = Node::create();//模板节点
	Sprite *circle4 = Sprite::create("avatar1.png");
	circle4->setScale(120.f / 400);
	stencil4->addChild(circle4);
	ClippingNode  *clippingNode4 = ClippingNode::create(stencil4);//需要模板
	clippingNode4->addChild(avararSprite5); //模板和图片尺寸尽量相同

//Alpha阀值：
	clippingNode4->setAlphaThreshold(0.9);
	clippingNode4->setInverted(false);
	clippingNode4->setPosition(Vec2(node1->getPositionX(), node1->getPositionY() - 285));
	clippingNode4->setTag(1);
	addChild(clippingNode4, 5);

	//createHttpOfHeadImg("https://img5.duitang.com/uploads/item/201409/20/20140920163111_fsSQj.thumb.700_0.png", CC_CALLBACK_2(SettingLayer::getHeadImgResponse, this));

	return true;
}
void SettingLayer::closeButtonClicked(Ref *sender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {

		Button*n = (Button*)sender;
		if (n->getTag()==1)
		{
			auto transition = TransitionFade::create(0.0f, GameScene::scene());
		    Director::getInstance()->replaceScene(transition);//切换场景

		
		}
		else if (n->getTag() == 2) {

			if (!game->is_denglu)
			{
				auto transition = TransitionMoveInR::create(0.5f, DengluScene::create());
				Director::getInstance()->replaceScene(transition);//切换场景

			}
			else 	if (game->is_denglu)
			{
				auto transition = TransitionMoveInR::create(0.5f, GameHall::create());
				Director::getInstance()->replaceScene(transition);//切换场景
			}

			
		}



	}
}
bool SettingLayer::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

void SettingLayer::playernumbers(int t)
{

	if (t==2)
	{
		    player2->setVisible(false);
			player3->setVisible(false);
			player4->setVisible(false);

	}
	else	if (t == 3)
	{
		player3->setVisible(false);
		player4->setVisible(false);
	}
	else	if (t == 4)
	{
		player4->setVisible(false);
	}





}

void SettingLayer::createHttpOfHeadImg(string headImgUrl,
	const cocos2d::network::ccHttpRequestCallback &callBack)
{
	//新建请求对象
	auto request = new HttpRequest();
	//设置请求地址

	request->setUrl(headImgUrl.c_str());//("http://pic63.nipic.com/file/20150330/8993928_082652755616_2.jpg");
										//设置请求类型
	request->setRequestType(HttpRequest::Type::GET);
	//设置请求的回调
	request->setResponseCallback(CC_CALLBACK_2(SettingLayer::getHeadImgResponse, this));
	//发送请求
	HttpClient::getInstance()->send(request);
	//释放对象
	request->release();
}

void SettingLayer::getHeadImgResponse(cocos2d::network::HttpClient * Sender, cocos2d::network::HttpResponse * response)
{
	log("===========");



	//获取回调值

	std::vector<char>* buffer = response->getResponseData();
	//创建图片
	Image* img = new Image();
	img->initWithImageData((unsigned char*)buffer->data(), buffer->size());
	//创建回调值
	Texture2D* texture = new Texture2D();
	bool isImg = texture->initWithImage(img);
	if (isImg)
	{//显示头像
		/*avararSprite1->setTexture(texture);
		avararSprite2->setTexture(texture);
		avararSprite3->setTexture(texture);
		avararSprite4->setTexture(texture);*/
	}

}