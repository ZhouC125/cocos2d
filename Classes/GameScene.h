#pragma once
#include <cocos2d.h>
#include "Player.h"
#include"CardGame.h"
#include"ui/CocosGUI.h"
#include <array>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;

class GameScene :public Scene
{
public:
	static GameScene* scene();

	CREATE_FUNC(GameScene);
	virtual bool init();

	CardGame *game;
	Player * player_self;
	Player * player_left;
	Player * player_right;
	Player * player_front;
	Player*  player_rightupper;
	Button *ta;
	Button *ta1;
	Button *ta2;
	Button *ta3;
	Button *fill;
	int ren = 1;
	int s = 0;
	bool self = false;
	bool  left = false;
	bool  right = false;
	bool  front = false;
	bool  rightupper = false;

	int flower1[2];
	int flower2[2];
	int hua[3];


	float tt1 =0;
	int  tt2 = 0;
	int g1=0;
	int g2 = 0;
	int ct1 = 0;;
	bool isie = false;
	bool  isze = false;
	Label* _goldLabel;//�ܷ���label
	Label* _selfLabel;//�Լ�����label
	Label* _rightLabel;//�Ҳ����label
	Label* _rightupperLabel;//���Ϸ���label
	Label* _frontLabel;//�������label
	Label* _leftLabel;//������label

	int Endpoints=0;      //�ܷ�


	bool   isself=false;
	int currentzu = 100;

	bool isdate_self=true;
	bool isdate_right = false;
	bool isdate_rightupper = false;
	bool isdate_front = false;
	bool isdate_left = false;



	int bei1 = 1;
	int  check = 1;
	int g = 0;

	int i = 0;
	int j = 0;
	int y = 0;
	bool  e = true;
	Sprite*win;
	Sprite*lose;

	//bool  bipai = false;

	Sprite*hide[3];
	Sprite*hide1[3];
	Sprite*hide2[3];
	Sprite*hide3[3];
	Sprite*hide4[3];

	bool  bout = true;

	int  ie = 0;
	//std::vector<Player*>players;


	cocos2d::CCProgressTimer *progresstime1;
	Button *compares;
	Button* setting1;
	Button* setting2;
	bool  issetting = false;
	Sprite*b;
	//����
	Sprite*bangzhu;
	CCSprite *s2;
	bool isbegin=false;//�Ƿ�ʼ��Ϸ


	Sprite *bvatarSprite;
	Sprite *bvatarSprite1;
	Sprite *bvatarSprite2;
	Sprite *bvatarSprite4;


	//���� _Array* ���͵ı���list������Ϊ���ĳ�ʼ����

	__Array* players;

	int self_money;
	int left_money;
	int right_money;
	int rightupper_money;
	int front_money;

	int self_money_shen;
	int left_money_shen;
	int right_money_shen;
	int rightupper_money_shen;
	int front_money_shen;

	int qs = 0;
	int  ss = 0;

private:
	void addplayers();

	//������
	void aaa(Ref*sss, Widget::TouchEventType type);
	//ɾ�����
	void reducePlayer(int r);
	/*this->schedule(schedule_selector(GameScene::dijishenchen), 1);*/
	void update(float delta);//�ص����º������ú���ÿһ֡��������
	//�������UI����
	void loadPlayerUI(Player *player);
	//�����Ӻ�1234ת���ɳ����еľ���λ��
	char getPlayerCharPosition(int pos);
	//�˵�����
	void menuItemClicked(int  sender);
	//��ʼ��Ϸ
	void beginGame(Ref *sender, Widget::TouchEventType type);
	void  pai(Player*ss, int a, int b);
	 //����
	void compare(Ref * sss, Widget::TouchEventType type);
	//����
	int   cardtype(Player*palayer,   int qs);
	//ͬ�����ƱȽ�
	void cardtype1(Player * palayer1, Player * palayer2, int x, int y);

	//��ע
	void  multiplyingpower(Ref * it, Widget::TouchEventType type);
	//��ע,��ע,����,����
	void operation(int t,Player*player,Label*integrallabel);

	void 	compareframe(bool bipai);

	//�˻��ж�
	void  AIjudge(Player*player,int integral, Label*integrallabel,int q, int x, int y);
	//�˻�����
	void  Open(int q, Player*player2,int x,int y);
	void  Open1(int q, Player*player2, int x, int y);
	void gen(int integral, Label*integrallabel,Player*player,int q, int x, int y);
  //����
	void 	 abandon(Player*player);
	void  abandon1(Player*player);

	//����
	void  kanpai(Player*player);
	//����
	void meng();
	//����
	void qipao(Player*player,int i);
	//��ʱ��
	void updateReadyTimer(float delta);
	//��Ϸ������ť(�˳�,����,����)
	void   setting(Ref* pSender, Widget::TouchEventType type);

	void settingbtn(bool s);
	//�뿪,����,���ð�ť����ת
	void jump(Ref * it, Widget::TouchEventType type);
	void jump1(Ref * it, Widget::TouchEventType type);

	void  taskButtonClicked(Ref * it, Widget::TouchEventType type);
	//���������ʣ��Ľ��
	void   residue();
	//�����û��Ǯ�󷢷Ž��
	void  provide();

};
