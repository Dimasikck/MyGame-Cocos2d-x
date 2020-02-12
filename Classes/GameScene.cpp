#include <cocos/scripting/deprecated/CCString.h>
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
#include "GameScene.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"
using namespace CocosDenshion;
USING_NS_CC;
Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics( );
    scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    scene->getPhysicsWorld( )->setGravity( Vect( 0, 0 ) );

    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld( ) );

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;

}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldSceneScene.cpp\n");
}


void GameScene::movePlayer(Touch* touch, Event* event)
{
    auto positionTouch = touch -> getLocation();
    if(_player->getBoundingBox().containsPoint(positionTouch)){
        _player -> setPositionX(positionTouch.x);
    }

}
void GameScene::initializationPhysicsPlayer(cocos2d::Sprite* sprite)
{
    auto bodyPlayer = PhysicsBody::createCircle(sprite -> getContentSize().width / 2);
    bodyPlayer -> setContactTestBitmask(true);
    bodyPlayer -> setDynamic(true);
    bodyPlayer->setCollisionBitmask( PLAYER_COLLISION_BITMASK );

    bodyPlayer->setContactTestBitmask( true );
    sprite->setPhysicsBody( bodyPlayer );
    isFalling = true;

}
void GameScene::initializationPhysicsBomb(cocos2d::Sprite* sprite)
{
    auto bodyBomb = PhysicsBody::createCircle(sprite -> getContentSize().width / 2);
    bodyBomb -> setContactTestBitmask(true);
    bodyBomb -> setDynamic(true);
    bodyBomb->setCollisionBitmask( BOMB_COLLISION_BITMASK);

    bodyBomb->setContactTestBitmask( true );
    sprite->setPhysicsBody( bodyBomb );
    isFalling = true;

}

void GameScene::addBombs(float dt)
{
    auto director = Director::getInstance();
    auto size = director->getWinSize();

    Sprite* bomb = nullptr;

    for(int i = 0 ; i < 5 ; i++)
    {
        bomb = Sprite::create("images/bomb.png");
        bomb -> setAnchorPoint(Vec2::ZERO);
        bomb -> setPosition(CCRANDOM_0_1() * size.width , size.height);
        initializationPhysicsBomb(bomb);
        bomb ->getPhysicsBody()->setVelocity(Vect(0, ( (CCRANDOM_0_1() + 0.5f) * -250) ));
        _bombs.pushBack(bomb);
        this -> addChild(bomb, 2);

    }
}
void GameScene::initializationTouch()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener -> onTouchBegan = [] (Touch* touch, Event* event) { return true;};
    listener -> onTouchMoved = CC_CALLBACK_2(GameScene::movePlayer, this);
    listener -> onTouchEnded = [=] (Touch* touch, Event* event) {};
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
}
// on "init" you need to initialize your instance
bool GameScene::init()
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
    _player = Sprite::create("images/player.png");
    _player -> setPosition(size.width / 2 , size.height * 0.165);
    initializationPhysicsPlayer(_player);
    addChild(_player,1);
    initializationTouch();
    schedule(CC_SCHEDULE_SELECTOR(GameScene::addBombs),6.0f);

    auto contactListener = EventListenerPhysicsContact::create( );
    contactListener->onContactBegin = CC_CALLBACK_1( GameScene::onContactBegin, this );
    Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( contactListener, this );

  /*score = 0;
__String  *tempScore = __String::createWithFormat( "%i", score );


    scoreLabel = Label::createWithTTF( tempScore->getCString( ), "fonts/prstart.ttf", visibleSize.height * SCORE_FONT_SIZE );
    scoreLabel->setColor( Color3B::WHITE );
    scoreLabel->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y ) );
    this->addChild( scoreLabel, 10000 );
*/

    this->scheduleUpdate( );


    auto label = Label::createWithTTF("0","fonts/prstart.ttf",24);
    label->enableOutline(Color4B::BLACK, 1);

    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                        origin.y + visibleSize.height*0.95 - label->getContentSize().height));

    this->addChild(label,1);
    time = 0;
    lapIndex=0;
   // this->schedule(CC_SCHEDULE_SELECTOR(GameScene::TimeMethod), 0.01);

    auto mainMenuItem = MenuItemImage::create(
            "images/Pause Button.png",
            "images/Pause Button Clicked.png",
            CC_CALLBACK_1(GameScene::GoToMainMenuScene, this));

    if (mainMenuItem == nullptr ||
            mainMenuItem->getContentSize().width <= 0 ||
            mainMenuItem->getContentSize().height <= 0)
    {
        problemLoading("'Pause Button.png' and 'Pause Button Clicked.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - mainMenuItem->getContentSize().width/2;
        float y = origin.y + mainMenuItem->getContentSize().height/2;

        mainMenuItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(mainMenuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}
/*void GameScene::TimeMethod(float dt)
{
    time +=dt;
    __String *timeToDisplay = __String::createWithFormat("%.2f",time);
    label->setString(timeToDisplay->getCString());

}*/
bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact ) {
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if ( ( PLAYER_COLLISION_BITMASK == a->getCollisionBitmask( ) && BOMB_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( PLAYER_COLLISION_BITMASK == b->getCollisionBitmask( ) && BOMB_COLLISION_BITMASK == a->getCollisionBitmask() ) )
   {
       SimpleAudioEngine::getInstance()->playEffect("sounds/Hit.mp3");
      auto scene = GameOverScene::createScene();

       Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    }
    /* else if ( ( PLAYER_COLLISION_BITMASK == a->getCollisionBitmask( ) && BOMB_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( PLAYER_COLLISION_BITMASK == b->getCollisionBitmask( ) && BOMB_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {

   score++;

         __String *tempScore = __String::createWithFormat( "%i", score );

         scoreLabel->setString( tempScore->getCString( ) );

   }*/
           return true;
}


void GameScene::GoToMainMenuScene( cocos2d::Ref *pSender )
{
    SimpleAudioEngine::getInstance()->playEffect("sounds/button.wav");
    auto scene = MainMenuScene::createScene( );

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}






