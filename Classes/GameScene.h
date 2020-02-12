#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__


#include "cocos2d.h"
USING_NS_CC;


class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);


private:
    cocos2d::Sprite* _player;
    cocos2d::Vector<cocos2d::Sprite*> _bombs;
    void initializationTouch();
    void addBombs(float dt);
    void initializationPhysicsPlayer(cocos2d::Sprite* sprite);
    void initializationPhysicsBomb(cocos2d::Sprite* sprite);
    void movePlayer(cocos2d::Touch* toque, cocos2d::Event* event);
    void GoToMainMenuScene( cocos2d::Ref *pSender );
    bool onContactBegin( cocos2d::PhysicsContact &contact );
    void SetPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };
    cocos2d::PhysicsWorld *sceneWorld;
    //void update( float dt );
    unsigned int score;
    bool isFalling;
    cocos2d::Label *scoreLabel;
   // void TimeMethod(float dt);
    cocos2d::Label *label;
    float laps[3];
    int lapIndex;
    float time;
};

#endif // __GAME_SCENE_H__
