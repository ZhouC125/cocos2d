#include "Player.h"
#include "ui/CocosGUI.h"
#include "constart.h"
#include<string.h>
#include "CardGame.h"
USING_NS_CC;

void Player::initCards() {
	for (int i = 0; i < 3; i++) {
		cards[i] = -1;
	}
}
int Player::countCards() {
	int count = 0;
	for (int i = 0; i < 3; i++) {
		if (cards[i] == -1) {
			break;
		}
		count++;
	}
	return count;
}

void Player::sortCards() {
	//外层循环,记录当前处理的位置(实际上就是为了找到这个位置该放的值)
	int len = countCards();
	int idx;
	for (int i = 0; i < len - 1; i++) {
		idx = i;
		//内层循环,用来寻找当前的最大值
		for (int j = i + 1; j < len; j++) {
			//比较当前最大值与j索引值大小
			int p1 = cards[idx] % 13 + 1;//idx牌面值
			int p2 = cards[j] % 13 + 1;//j牌面值

			if (p1 == 1) {
				p1 = 14;
			}
			if (p2 == 1) {
				p2 = 14;
			}
			if (p1 < p2) {
				idx = j;
			}
			if (p1 == p2)//仅花色不同的情况
			{
				if (cards[idx] < cards[j])
					idx = j;
			}

		}
		//如果最大值的索引发生改变，则交换两个位置的值
		if (idx != i) {
			int tmp = cards[i];
			cards[i] = cards[idx];
			cards[idx] = tmp;
		}
	}

}

void Player::createPlayerNode() {

	auto game = CardGame::getInstance();
	if (game->is_denglu)
	{
		createHttpOfHeadImg(headImgUrl, CC_CALLBACK_2(Player::getHeadImgResponse, this));
	}

	
	

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Label *nameLabel = Label::create();
	this->node = Node::create();
	float labelHalfwidth = nameLabel->getBoundingBox().size.width / 2;
	float laberlHalfHeight = nameLabel->getBoundingBox().size.height / 2;
	if (this->pos_char == 's') {
		//	nameLabel->setAnchorPoint(Vec2(0, 0));
		nameLabel->setPosition(Vec2(labelHalfwidth + 80, laberlHalfHeight + 30));
	}
	else if (this->pos_char == 'r') {
		//	nameLabel->setAnchorPoint(Vec2(1, 0));
		nameLabel->setPosition(Vec2(visibleSize.width -  labelHalfwidth-130, visibleSize.height / 2 + laberlHalfHeight));
	}
	else if (this->pos_char == 'f') {
		//nameLabel->setAnchorPoint(Vec2(0, 1));
		nameLabel->setPosition(Vec2(visibleSize.width / 2 + labelHalfwidth - 200, visibleSize.height - 200 + laberlHalfHeight + 80));
	}
	else if (this->pos_char == 'l') {
		//nameLabel->setAnchorPoint(Vec2(0, 0));
		nameLabel->setPosition(Vec2(50 + labelHalfwidth, visibleSize.height / 2 + laberlHalfHeight));
	}
	else if (this->pos_char == 'e') {
		//nameLabel->setAnchorPoint(Vec2(0, 0));
		nameLabel->setPosition(Vec2(visibleSize.width / 2 + labelHalfwidth + 100, visibleSize.height - 200 + laberlHalfHeight + 80));
	}

	Node *stencil = Node::create();//模板节点
	Sprite *circle = Sprite::create("avatar1.png");
	circle->setScale(120.f / 320);
	stencil->addChild(circle);
	ClippingNode  *clippingNode = ClippingNode::create(stencil);//需要模板
	//创建头像精灵
	avatarSprite = Sprite::create("101.png");
	//avatarSprite->setPosition(Vec2(nameLabel->getPositionX(), nameLabel->getBoundingBox().getMaxY()+avatarSprite->getBoundingBox().size.height/2));
	//设置底板
	clippingNode->addChild(avatarSprite); //模板和图片尺寸尽量相同
	//Alpha阀值：
	clippingNode->setAlphaThreshold(0.9);
	clippingNode->setInverted(false);
	clippingNode->setPosition(Vec2(nameLabel->getPositionX(), nameLabel->getBoundingBox().getMaxY() + clippingNode->getBoundingBox().size.height / 2 + 60));
	clippingNode->setTag(1);
	//背景
	Sprite *bvatarSprite = Sprite::create("bg_cardszone.png");
	bvatarSprite->setPosition(clippingNode->getPositionX() + 45, clippingNode->getPositionY());
	bvatarSprite->setScale(0.7);
	this->node->addChild(clippingNode, 1);
	this->node->addChild(nameLabel, 1);
	this->node->addChild(bvatarSprite);

	////Rect rect = clippingNode->getBoundingBox();
	///*if (this->pos_char == 'l') {
	//	bvatarSprite->setScale(0.3, 1.1);
	//	bvatarSprite->setPosition(clippingNode->getPositionX(), clippingNode->getPositionY() - 21);
	//}
	//if (this->pos_char == 'r') {
	//	bvatarSprite->setScale(0.3, 1.1);
	//	bvatarSprite->setPosition(clippingNode->getPositionX(), clippingNode->getPositionY() - 21);
	//}*/


}
void Player::createHttpOfHeadImg(string headImgUrl,
	const cocos2d::network::ccHttpRequestCallback &callBack)
{
	//新建请求对象
	auto request = new HttpRequest();
	//设置请求地址

	request->setUrl(headImgUrl.c_str());//("http://pic63.nipic.com/file/20150330/8993928_082652755616_2.jpg");
										//设置请求类型
	request->setRequestType(HttpRequest::Type::GET);
	//设置请求的回调
	request->setResponseCallback(CC_CALLBACK_2(Player::getHeadImgResponse, this));
	//发送请求
	HttpClient::getInstance()->send(request);
	//释放对象
	request->release();
}

void Player::getHeadImgResponse(cocos2d::network::HttpClient * Sender, cocos2d::network::HttpResponse * response)
{
	log("===========");



	////获取回调值

	//std::vector<char>* buffer = response->getResponseData();
	////创建图片
	//Image* img = new Image();
	//img->initWithImageData((unsigned char*)buffer->data(), buffer->size());
	////创建回调值
	//Texture2D* texture = new Texture2D();
	//bool isImg = texture->initWithImage(img);
	//if (isImg)
	//{//显示头像
	//	avatarSprite->setTexture(texture);
	//}
	
}


