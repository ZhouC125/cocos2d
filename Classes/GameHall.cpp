#include "constart.h"
#include "GameHall.h"
#include "cocostudio/CocoStudio.h"
//#include "SetLayer.h"
//#include "HelloWorldScene.h"
#include "GameScene.h"
#include "RecordLayer.h"
#include "ShopScene.h"
#include "SetLayer.h"
#include "RulesLayer.h"
#include "Feedback.h"
//#include "LevelUtils.h"
#include<string.h>
#include "MailboxLayer.h"
#include "CommonAudio.h"
#include"ui/CocosGUI.h"
#include "CardGame.h"

#pragma execution_character_set("utf-8")
USING_NS_CC;
GameHall * GameHall::scene()
{
	return GameHall::create();
}

bool GameHall::init()
{
	if (!Scene::init())
		return false;
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameHall::onTouchBegan, this);
	//��û�ײ��¼�
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);



	auto rootNode = CSLoader::createNode("SceneHall.csb");
	addChild(rootNode);	
    //����
	Button* set = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	//��Ӽ���
	set->addTouchEventListener(CC_CALLBACK_2(GameHall::settingButtonClicked, this));


	//�ʼ�
	Button* mail = dynamic_cast<Button*>(rootNode->getChildByName("Button_4"));
	mail->addTouchEventListener(CC_CALLBACK_2(GameHall::mailbox, this));

	//�淨
	Button* played = dynamic_cast<Button*>(rootNode->getChildByName("Button_3"));
	played->addTouchEventListener(CC_CALLBACK_2(GameHall::guize1ButtonClicked, this));

	//����
	Button* feedback = dynamic_cast<Button*>(rootNode->getChildByName("Button_5"));
	feedback->addTouchEventListener(CC_CALLBACK_2(GameHall::isuepo, this));

	//ս��
	Button* Record = dynamic_cast<Button*>(rootNode->getChildByName("Button_2"));
	Record->addTouchEventListener(CC_CALLBACK_2(GameHall::tableCellTouched, this));
	Record->setTag(3);
	//�̳�
	Button* shop = dynamic_cast<Button*>(rootNode->getChildByName("Button_6"));
	shop->addTouchEventListener(CC_CALLBACK_2(GameHall::shopButtonclicked, this));

	//������
	Button* room1 = dynamic_cast<Button*>(rootNode->getChildByName("Button_7"));
	room1->addTouchEventListener(CC_CALLBACK_2(GameHall::tableCellTouched, this));
	room1->setTag(1);

	//�߼���
	Button* room2 = dynamic_cast<Button*>(rootNode->getChildByName("Button_8"));
	room2->addTouchEventListener(CC_CALLBACK_2(GameHall::tableCellTouched, this));
	room2->setTag(2);



	Button* addgold = dynamic_cast<Button*>(rootNode->getChildByName("Button_9"));
	addgold->addTouchEventListener(CC_CALLBACK_2(GameHall::shopButtonclicked, this));
	addgold->setTag(2);

	Button* add = dynamic_cast<Button*>(rootNode->getChildByName("Button_9_0"));
	add->addTouchEventListener(CC_CALLBACK_2(GameHall::shopButtonclicked, this));
	add->setTag(2);


	auto node = static_cast<Node*>(rootNode->getChildByName("Node_1"));

	avararSprite = Sprite::create("101.png");
	Node *stencil = Node::create();//ģ��ڵ�
	Sprite *circle = Sprite::create("avatar1.png");
	circle->setScale(120.f / 320);
	stencil->addChild(circle);
	ClippingNode  *clippingNode = ClippingNode::create(stencil);//��Ҫģ��
	clippingNode->addChild(avararSprite); //ģ���ͼƬ�ߴ羡����ͬ
	//Alpha��ֵ��
	clippingNode->setAlphaThreshold(0.9);
	clippingNode->setInverted(false);
	clippingNode->setPosition(Vec2(node->getPositionX(), node->getPositionY()));
	clippingNode->setTag(1);
   addChild(clippingNode, 5);
   createHttpOfHeadImg("http://www.telnote.cn/qqtouxiang/images/20120408/20120408093053751.jpg", CC_CALLBACK_2(GameHall::getHeadImgResponse, this));

	CommonAudio::playAudio(9);

	game = CardGame::getInstance();

	

	auto Image = dynamic_cast<ImageView*>(rootNode->getChildByName("Image_5"));

	//����Լ����
	_goldsLabel = Label::create(String::createWithFormat("%d", game->golds)->getCString(), "Arial", 26);
	_goldsLabel->setAnchorPoint(Vec2(0, 0));
	_goldsLabel->setPosition(Vec2(Image->getPositionX()-30,Image->getPositionY()-18));
	addChild(_goldsLabel, 3);
	auto Image1 = dynamic_cast<ImageView*>(rootNode->getChildByName("Image_8"));
	//�����ʯ
	_jewelLabel = Label::create(String::createWithFormat("%d", game->jewel)->getCString(), "Arial", 26);
	_jewelLabel->setAnchorPoint(Vec2(0, 0));
	_jewelLabel->setPosition(Vec2(Image1->getPositionX()-30, Image1->getPositionY()-18));
	addChild(_jewelLabel, 3);



	auto _self_name = static_cast<Text*>(rootNode->getChildByName("Text_1"));
	_self_name->setText(game->account.c_str());

	  game->is_denglu = true;
	


	this->scheduleUpdate();
	return true;

}
void GameHall::update(float delta)
{
	if (game->is_do)
	{
		game->shop();
		game->is_do=false;
	}
	log("%d", game->golds);
	_goldsLabel->setString(StringUtils::format("%d", game->golds));
	_jewelLabel->setString(StringUtils::format("%d", game->jewel));

}
void GameHall::tableCellTouched(Ref *sender, Widget::TouchEventType type)
{
	

	if (type == Widget::TouchEventType::ENDED) {

		CommonAudio::playAudio(8);
		Button*n = (Button*)sender;
		if (n->getTag()==1)
		{

				auto transition = TransitionMoveInR::create(0.5f, GameScene::create());
				Director::getInstance()->replaceScene(transition);//�л�����


		}
		else if (n->getTag() == 2) {

			if (game->golds>=10000)
			{

				if (game->is_accomplish)
				{
					auto transition = TransitionMoveInR::create(0.5f, GameScene::create());
					Director::getInstance()->replaceScene(transition);//�л�����
				}
				else
				{
					auto transition = TransitionMoveInR::create(0.5f, GameScene::create());
					Director::getInstance()->replaceScene(transition);//�л�����

				}

			}
			else
			{

				auto so = Sprite::create("match_bg.png");
				so->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
				so->setScale(1.2);
				so->setOpacity(0);//���Ӷ�Ϊ0,1Ϊ��ȫ�ɼ�
				addChild(so, 10);
				FadeIn* fadeIn = FadeIn::create(1);
				so->runAction(Sequence::create(fadeIn, DelayTime::create(1), RemoveSelf::create(), NULL));

				Text* text = Text::create("��Ǹ���޷�����", "Arail", 40);
				text->setPosition(Vec2(260, 35));
				text->setColor(Color3B(255, 0, 0));
				text->setTag(15);
				so->addChild(text, 11);

			}

		}
		else if (n->getTag()==3)
		{

			RecordLayer *layer = RecordLayer::create();
			/*	layer->setAnchorPoint(ccp(1, 1));*/
			layer->setPosition(Vec2(VISIBLE_SIZE.width / 4 - 170, VISIBLE_SIZE.height / 4 - 100/*- VISIBLE_SIZE.height / 2.5*/));
			this->addChild(layer, 3);

		}
		
	}

}
//�̳�
void GameHall::shopButtonclicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {

		
		CommonAudio::playAudio(8);
		//�������ò�m
		ShopScene *layer = ShopScene::create();
		/*	layer->setAnchorPoint(ccp(1, 1));*/
		layer->setPosition(Vec2(VISIBLE_SIZE.width / 4 - 170, VISIBLE_SIZE.height / 4 - 100/*- VISIBLE_SIZE.height / 2.5*/));
		this->addChild(layer, 3);
	}


}
//����
void GameHall::settingButtonClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		//�������ò�m
		SetLayer *layer = SetLayer::create();
	/*	layer->setAnchorPoint(ccp(1, 1));*/
		layer->setPosition(Vec2(VISIBLE_SIZE.width / 4-170, VISIBLE_SIZE.height / 4-100/*- VISIBLE_SIZE.height / 2.5*/));
		this->addChild(layer,3);
	}
}
//���ع����
void GameHall::guize1ButtonClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		//���ع����
		RulesLayer *layer = RulesLayer::create();
		layer->setPosition(Vec2(VISIBLE_SIZE.width / 4 - 170, VISIBLE_SIZE.height / 4 - 100));
		addChild(layer,3);
	}

}

void GameHall::isuepo(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		Feedback *layer = Feedback::create();
		layer->setPosition(Vec2(VISIBLE_SIZE.width / 4 - 170, VISIBLE_SIZE.height / 4 - 100));
		addChild(layer, 3);
	}

}

void GameHall::mailbox(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		CommonAudio::playAudio(8);
		MailboxLayer *layer = MailboxLayer::create();
		layer->setPosition(Vec2(VISIBLE_SIZE.width / 4 - 170, VISIBLE_SIZE.height / 4 - 100));
		addChild(layer, 3);
	}

}


bool GameHall::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}
void GameHall::createHttpOfHeadImg(string headImgUrl,
	const cocos2d::network::ccHttpRequestCallback &callBack)
{
	//�½��������
	auto request = new HttpRequest();
	//���������ַ

	request->setUrl(headImgUrl.c_str());//("http://pic63.nipic.com/file/20150330/8993928_082652755616_2.jpg");
										//������������
	request->setRequestType(HttpRequest::Type::GET);
	//��������Ļص�
	request->setResponseCallback(CC_CALLBACK_2(GameHall::getHeadImgResponse, this));
	//��������
	HttpClient::getInstance()->send(request);
	//�ͷŶ���
	request->release();
}

void GameHall::getHeadImgResponse(cocos2d::network::HttpClient * Sender, cocos2d::network::HttpResponse * response)
{
	log("===========");



	////��ȡ�ص�ֵ

	//std::vector<char>* buffer = response->getResponseData();
	////����ͼƬ
	//Image* img = new Image();
	//img->initWithImageData((unsigned char*)buffer->data(), buffer->size());
	////�����ص�ֵ
	//Texture2D* texture = new Texture2D();
	//bool isImg = texture->initWithImage(img);
	//if (isImg)
	//{//��ʾͷ��
	//	avararSprite->setTexture(texture);
	//}

}
