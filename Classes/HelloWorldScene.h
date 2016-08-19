#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "Player.h"
#include "Enemy.h"
#include "GameMap.h"

#include "cocos2d.h"

#include <algorithm>
#include <vector>

const cocos2d::EventKeyboard::KeyCode UP_ARROW = cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW;
const cocos2d::EventKeyboard::KeyCode DOWN_ARROW = cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW;
const cocos2d::EventKeyboard::KeyCode LEFT_ARROW = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW;
const cocos2d::EventKeyboard::KeyCode RIGHT_ARROW = cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
const cocos2d::EventKeyboard::KeyCode SHIFT_KEY = cocos2d::EventKeyboard::KeyCode::KEY_SHIFT;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    ~HelloWorld()
    {
        for (Enemy *enemy : enemies_)
        {
            delete enemy;
        }
        delete map_;
    }

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:

    void updateScene(float interval);

    void setPlayerPosition(cocos2d::Point position, Direction direction);

    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode) const
    {
        return std::find(downKeys_.begin(), downKeys_.end(), keyCode) != downKeys_.end();
    }

    Player player_;
    int fieldWidth_;
    int fieldHeight_;
    GameMap *map_;
    std::vector<Enemy*> enemies_;
    std::vector<cocos2d::EventKeyboard::KeyCode> downKeys_;
};

#endif // __HELLOWORLD_SCENE_H__
