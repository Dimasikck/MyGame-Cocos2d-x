#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
using namespace CocosDenshion;
USING_NS_CC;


Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();


    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // 'layer' is an autorelease object

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()-> getVisibleOrigin();
    auto director = Director::getInstance();
    auto size = director->getWinSize();
    auto spriteBackground = Sprite::create("images/background.png");
    spriteBackground -> setPosition(Point((visibleSize.width/2)+origin.x, (visibleSize.height/2)+origin.y));
    addChild(spriteBackground,0);

    // create menu, it's an autorelease object

    auto playItem = MenuItemImage::create(
            "images/Play Button.png",
            "images/Play Button Clicked.png",
            CC_CALLBACK_1( MainMenuScene::GoToGameScene, this ));
    playItem->setPosition( Point( (visibleSize.width / 2 )+ origin.x, (visibleSize.height)*0.45+ origin.y ) );

    auto menu = Menu::create( playItem, NULL );
    menu->setPosition( Point::ZERO );


    this->addChild( menu );
    auto mygameSprite = Sprite::create( "images/My Game.png" );
    mygameSprite->setPosition(Vec2(origin.x + visibleSize.width/2,
                                   origin.y + visibleSize.height*0.85 - mygameSprite->getContentSize().height));

    this->addChild( mygameSprite );
    return true;
}

void MainMenuScene::GoToGameScene( cocos2d::Ref* pSender)
{
    auto scene = GameScene::createScene();
    SimpleAudioEngine::getInstance()->playEffect("sounds/button.wav");
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}




