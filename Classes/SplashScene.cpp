#include "SplashScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
USING_NS_CC;
using namespace CocosDenshion;
Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto audio = SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("sounds/background.wav", true);
    this->scheduleOnce( CC_SCHEDULE_SELECTOR( SplashScene::GoToMainMenuScene ), DISPLAY_TIME_SPLASH_SCENE );

    auto backgroundSprite = Sprite::create( "images/Splash Screen.png" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );

    this->addChild( backgroundSprite );

    return true;
}

void SplashScene::GoToMainMenuScene( float dt )
{
    auto scene = MainMenuScene::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}



