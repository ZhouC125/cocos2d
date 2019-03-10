#pragma once
#include "cocos2d.h"
#include <time.h>
#include "vector"
#include "Player.h"
USING_NS_CC;
using namespace std;
//ö������
typedef enum {

	//����
	POKER_TYPE_SINGLE,
	//����
	POKER_TYPE_DOUBLE,
	//˳��
	POKER_TYPE_STRAIGHT,
	//��
	POKER_TYPE_GOLDEN_FLOWER,
	//˳��
	POKER_TYPE_STRAIGHT_FLUSH,
	//����
	POKER_TYPE_LEOPARD,
}PokerType;
class CardGame
{
public:
	Node* card;
	CardGame();//���캯��

	void shuffle(int a[], int len);//ϴ�ƺ���
	bool gameDidBegan;//��Ϸ�Ƿ�ʼ
	int golds;   //���
	int jewel;    //��ʯ
	static CardGame*getInstance();//��Ϸ����
	static void cleanInstance();//������
	bool ispurchase=false;//�Ƿ�����

	int sort;   //�̳�ѡ�������
	bool  is_ok=false; //���ֵ�ɹ�
	bool is_pay=false;//�Ƿ�֧��

	bool is_denglu=false;//�Ƿ��¼

	string account= "wanjiak"; //�˺���

	string question="1" ; //�˺���
	bool  is_got[4] = { false,false,false,false};//�Ƿ��Ѿ���ȡ
	float pmgressbar[4] = { 0,0,0,0 };           //���������
	std::string text[4] = { "0","0","0","0" };    //�������ֱ���
	bool is_accomplish = false;                   //�Ƿ����һ����Ϸ
	bool  is_toot = false;
	bool is_access = false;                           //δ���һ����Ϸ�Ƿ����

	int ren;                                                  //��Ҷ�ս�˻��ǵ�����

	/*vector<string> topPlayer = { {"A","0"} };*/
	vector<vector<string>> bottomPlayer = { {"0","0"}, {"0","0"},{"0","0"},{"0","0"},{"0","0"} };

	bool is_again = false;                               //����

		//����Լ��ƵĽڵ�
	Node* selfCards_node;
	
	int right_money;
	int rightupper_money ;
	int front_money ;
	int left_money;


	int genzhu = 0;                    //�����ע3��
	int  shengli = 0;                    //����ʤ��һ��

	bool  is_yinxiao=true;                        //��Ч����


	int  cishu;                           //ս������

	bool  is_do = true;
	//��ȡ����
	PokerType getPokerTypeWithCards(vector<int> arr, const int *hua);
	//�ж��Լ�ѡ������ܲ���ѹ���ϼҳ�����
	bool  biggerThanLast(vector<int> selfCards, vector<int> lastCards, const int *color1, const int *color2);
    
	int  shop();

};