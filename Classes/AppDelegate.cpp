#include "AppDelegate.h"
#include "DengluScene.h"
#include "GameHall.h"
#include "BeginScene.h"
#include "GameScene.h"
USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1334, 750);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}
static int register_all_packages()
{
	return 0; //flag for packages manager
}
bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::createWithRect("zha", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
		director->setOpenGLView(glview);
    }





	// 获取可视区的尺寸
	Size visibleSize = director->getVisibleSize();
	log("😄：%f, %f", visibleSize.width, visibleSize.height);

	// 计算缩放因子
	float scale = designResolutionSize.height / visibleSize.height;

	// 设置设计分辨率
	director->getOpenGLView()->setDesignResolutionSize(visibleSize.width*scale, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);

	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);




    FileUtils::getInstance()->addSearchPath("res");


	register_all_packages();
    // create a scene. it's an autorelease object
    auto scene = BeginScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
