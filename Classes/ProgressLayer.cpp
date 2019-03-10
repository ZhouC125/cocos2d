#include "constart.h"
#include "ProgressLayer.h"
#include "DengluScene.h"
#include"ui/CocosGUI.h"
#include "GameScene.h"
#include "GameHall.h"
#pragma execution_character_set("utf-8")

USING_NS_CC;
ProgressLayer * ProgressLayer::scene()
{
	return ProgressLayer::create();
}

bool ProgressLayer::init()
{
	if (!Scene::init()) {
		return false;
	}

	schedule(schedule_selector(ProgressLayer::updateReadyTimer), 1, kRepeatForever, 0);
	// 加载素材
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("lor.plist", "lor.png");
	Sprite	*tenxun = Sprite::create("fenkuang_bg1.png");
	float scaleW = VISIBLE_SIZE.width / tenxun->getBoundingBox().size.width;
	float scaleH = VISIBLE_SIZE.height / tenxun->getBoundingBox().size.width;
	tenxun->setScale(scaleW > scaleH ? scaleW : scaleH);
	tenxun->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	addChild(tenxun);
	Sprite	*tas = Sprite::create("loadifet.png");
	tas->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2 - 180));
	tas->setScale(0.8);
	addChild(tas);
	game = CardGame::getInstance();

	return true;
}



void ProgressLayer::updateReadyTimer(float data) {

	time += 1;
	 if (time==1) {

		//获取人物的全部精灵帧
		Vector<SpriteFrame *> vectors = getSpriteFrame("s_%d.png", 17);
		//获取人物精灵帧里的第一帧，做初始化显示
		Sprite *person = Sprite::createWithSpriteFrame(vectors.front());
		person->setPosition(Vec2(VISIBLE_SIZE.width/2, VISIBLE_SIZE.height/2));
		person->setScale(0.8);
		addChild(person);
		//创建动画（精灵帧动画）
		Animation* animation = Animation::createWithSpriteFrames(vectors, 1.f / 8);
		person->runAction(RepeatForever::create(Animate::create(animation)));
	}
	else if (time >4) {

		this->unschedule(schedule_selector(ProgressLayer::updateReadyTimer));
		doi();
	}
}

void ProgressLayer::doi()
{

	if (!game->is_denglu)
	{

		auto transition = TransitionMoveInR::create(0.5f, GameHall::create());
		Director::getInstance()->replaceScene(transition);//切换场景
	}
	else  if (game->is_denglu)
	{
		Director::getInstance()->replaceScene(GameScene::scene());//切换场景

	}



}


Vector<SpriteFrame *> ProgressLayer::getSpriteFrame(const char *format, int count)
{
	Vector<SpriteFrame *> vector;
	//循环每一个精灵帧，添加进Vector中
	for (int i = 1; i < count; i++)
	{
		SpriteFrame *sf = SpriteFrameCache::getInstance()
			->getSpriteFrameByName(StringUtils::format(format, i));
		vector.pushBack(sf);
	}
	return vector;
}
