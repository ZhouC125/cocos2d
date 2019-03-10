
#pragma once
//  �����
#include <cocos2d.h>
// ������Ϸ������
#include "CardGame.h"


#include "network/HttpClient.h"
USING_NS_CC;
using namespace cocos2d::network;
using namespace cocos2d;
using namespace std;
class Player :public Ref{
public:
	
	string headImgUrl;
	string account; //�˺���
	string account_id;//id
	string gender;//�Ա�
	string avatar;//ͷ��
	int position;//λ��

	int money=5000;//���
	int  zuanshi=100;//��ʯ
	char pos_char;
	Node *node;              //����UI����Ľڵ� 
	void createPlayerNode();
	Sprite *avatarSprite;
	int out = 0;
	//bool isdate = true;
	int loadImgSuccess = 0;
	int pq = 0;
	bool islook = false;
	Sprite*hide[3];

	int cards[26];//�������
	void initCards();//��ʼ�����Ʒ�ֹ���ݳ�ͻ
	void sortCards();
	int countCards();//����



	Sprite *avararSprite;//ͷ����	
	void createHttpOfHeadImg(string headImgUrl, const cocos2d::network::ccHttpRequestCallback &callBack);
	void getHeadImgResponse(cocos2d::network::HttpClient*sender
		, cocos2d::network::HttpResponse*response);
};