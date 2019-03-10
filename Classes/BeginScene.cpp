#include "constart.h"
#include "BeginScene.h"
#include "DengluScene.h"
#include"ui/CocosGUI.h"
#include "GameHall.h"
#pragma execution_character_set("utf-8")

USING_NS_CC;
BeginScene * BeginScene::scene()
{
	return BeginScene::create();
}

bool BeginScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	schedule(schedule_selector(BeginScene::updateReadyTimer), 1, kRepeatForever, 0);
	// �����ز�
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("lor.plist", "lor.png");
	bg = Sprite::create("20181211110332.png");
	bg->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	this->addChild(bg);//����ͼ

	//����������
	Sprite	*ta = Sprite::create("tips.png");
	ta->setPosition(Vec2(VISIBLE_SIZE.width / 2 - 10, VISIBLE_SIZE.height*0.1 - 40));
	//ta->setScale(0.8);
	addChild(ta);
	

	return true;
}



void BeginScene::updateReadyTimer(float data) {

	time += 1;
	if (time<=1) {
	

		FadeOut *fadeout = FadeOut::create(2);
		FadeOut *fadeout2 = FadeOut::create(0);
		FadeIn *fadein = FadeIn::create(2);
	
		bg->runAction(fadeout);
		Sequence* action = Sequence::create(fadein, fadeout2, NULL);
		bg->runAction(action);
	}
	else if (time == 4) {
		FadeOut *fadeout = FadeOut::create(0);
		FadeOut *fadeout2 = FadeOut::create(2);
		FadeIn *fadein = FadeIn::create(2);
		Sprite* bg = Sprite::create("splash(2).png");
		bg->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
		addChild(bg);
		bg->runAction(fadeout);
		Sequence* action = Sequence::create(fadein, fadeout2, NULL);
		bg->runAction(action);
	}
	else if (time == 8) {

			Sprite	*tenxun = Sprite::create("fenkuang_bg1.png");
			float scaleW = VISIBLE_SIZE.width / tenxun->getBoundingBox().size.width;
			float scaleH = VISIBLE_SIZE.height / tenxun->getBoundingBox().size.width;
			tenxun->setScale(scaleW > scaleH ? scaleW : scaleH);
			tenxun->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
		   addChild(tenxun);
			Sprite	*tas = Sprite::create("loadifet.png");
			tas->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height/2-180));
			tas->setScale(0.8);
			addChild(tas);

		//��ȡ�����ȫ������֡
		Vector<SpriteFrame *> vectors = getSpriteFrame("s_%d.png", 17);
		//��ȡ���ﾫ��֡��ĵ�һ֡������ʼ����ʾ
		Sprite *person = Sprite::createWithSpriteFrame(vectors.front());
		person->setPosition(Vec2(VISIBLE_SIZE.width/2, VISIBLE_SIZE.height/2));
		person->setScale(0.8);
		addChild(person);
		//��������������֡������
		Animation* animation = Animation::createWithSpriteFrames(vectors, 1.f / 8);
		person->runAction(RepeatForever::create(Animate::create(animation)));
	}
	else if (time >=12) {
		this->unschedule(schedule_selector(BeginScene::updateReadyTimer));
		doi();
	}
}

void BeginScene::doi()
{


	Director::getInstance()->replaceScene(GameHall::scene());//�л�����



}


Vector<SpriteFrame *> BeginScene::getSpriteFrame(const char *format, int count)
{
	Vector<SpriteFrame *> vector;
	//ѭ��ÿһ������֡����ӽ�Vector��
	for (int i = 1; i < count; i++)
	{
		SpriteFrame *sf = SpriteFrameCache::getInstance()
			->getSpriteFrameByName(StringUtils::format(format, i));
		vector.pushBack(sf);
	}
	return vector;
}
