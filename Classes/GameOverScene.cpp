#include <cocos/scripting/deprecated/CCDeprecated.h>
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
using namespace CocosDenshion;
USING_NS_CC;

//unsigned int score;

Scene* GameOverScene::createScene()
{
    //score = tempScore;

    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto director = Director::getInstance();
    auto size = director->getWinSize();
    auto spriteBackground = Sprite::create("images/background.png");
    spriteBackground->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    this->addChild( spriteBackground );
    auto retryItem = MenuItemImage::create( "images/Retry Button.png", "images/Retry Button Clicked.png", CC_CALLBACK_1( GameOverScene::GoToGameScene, this ) );
    retryItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height * 0.68 ) );
    auto mainMenuItem = MenuItemImage::create( "images/Menu Button.png", "images/Menu Button Clicked.png", CC_CALLBACK_1( GameOverScene::GoToMainMenuScene, this ) );
    mainMenuItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 ) );
    auto menu = Menu::create( retryItem, mainMenuItem, NULL );
    menu->setPosition( Point::ZERO );
    this->addChild( menu );
    auto label = Label::createWithTTF("GAME OVER","fonts/prstart.ttf",16);
    label->enableOutline(Color4B::BLACK, 1);

    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height*0.95 - label->getContentSize().height));

    this->addChild(label,1);

    auto currentScore = Label::createWithTTF( "0","fonts/prstart.ttf", 24);
    currentScore->enableOutline(Color4B::BLACK, 1);
    currentScore->setPosition( Point( visibleSize.width/2 + origin.x, visibleSize.height / 2 + origin.y ) );

    this->addChild( currentScore );
/*
    UserDefault *def = UserDefault::getInstance( );

    auto highScore = def->getIntegerForKey( "HIGHSCORE", 0 );

     if ( score > highScore )
     {
         highScore = score;

         def->setIntegerForKey( "HIGHSCORE", highScore );
     }

     def->flush( );

     __String *tempScore = __String::createWithFormat( "%i", score );

     auto currentScore = Label::createWithTTF( tempScore->getCString( ), "fonts/prstart.ttf", visibleSize.height * SCORE_FONT_SIZE );
     currentScore->setPosition( Point( visibleSize.width * 0.25 + origin.x, visibleSize.height / 2 + origin.y ) );

     this->addChild( currentScore );

     __String *tempHighScore = __String::createWithFormat( "%i", highScore );

     auto highScoreLabel = Label::createWithTTF( tempHighScore->getCString( ), "fonts/prstart.ttf", visibleSize.height * SCORE_FONT_SIZE );

     highScoreLabel->setColor( Color3B::YELLOW );
     highScoreLabel->setPosition( Point( visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y ) );

     this->addChild( highScoreLabel );
     */
    return true;
}

void GameOverScene::GoToMainMenuScene( cocos2d::Ref *pSender )
{
    SimpleAudioEngine::getInstance()->playEffect("sounds/button.wav");
    auto scene = MainMenuScene::createScene( );

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void GameOverScene::GoToGameScene( cocos2d::Ref *pSender )
{
    SimpleAudioEngine::getInstance()->playEffect("sounds/button.wav");
    auto scene = GameScene::createScene( );

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}







