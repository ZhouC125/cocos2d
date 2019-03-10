#include "CommonAudio.h"
#include"audio\include\SimpleAudioEngine.h"
#include<string.h>
#include "cocos2d.h"
#include "CardGame.h"
using namespace std;
using namespace CocosDenshion;

USING_NS_CC;
//²¥·ÅÄ³¸öÒôÐ§
void  CommonAudio::playAudio(int gender) {

	auto game = CardGame::getInstance();

	if (game->is_yinxiao)
	{

	
	switch (gender)
	{
	case 0:
		SimpleAudioEngine::getInstance()->playEffect("sound/a00-l-0.mp3");
		break;
	
	case 1://¸ú×¢
		SimpleAudioEngine::getInstance()->playEffect("sound/a01-l-0.mp3");
		break;
	case 2://¼Ó×¢
		SimpleAudioEngine::getInstance()->playEffect("sound/a02-l-0.mp3");
		break;
	case 3://ÆúÅÆ
		SimpleAudioEngine::getInstance()->playEffect("sound/a04-l-0.mp3");
		break;
	case 4://±ÈÅÆ
		SimpleAudioEngine::getInstance()->playEffect("sound/a05-l-0.mp3");
		SimpleAudioEngine::getInstance()->playEffect("sound/bipai.mp3");

		break;
	case 5://¶ª¹É±È
		SimpleAudioEngine::getInstance()->playEffect("sound/add_gold.mp3");
		break;
	case 6://±ÈÅÆÊä
		SimpleAudioEngine::getInstance()->playEffect("sound/game_lost.mp3");
		
		break;
	case 7://±ÈÅÆÓ®
		SimpleAudioEngine::getInstance()->playEffect("sound/pkwin.mp3");
		break;
		
	case 8: //°´Å¥ÉùÒô
		SimpleAudioEngine::getInstance()->playEffect("sound/common_botton.mp3");
		break;

	case 9:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/bgMain.mp3", true);
		break;
	case 10:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/bgFight.mp3", true);
		break;
	default:
		break;
	}
	}
	
}

