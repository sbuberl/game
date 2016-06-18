#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <cocos2d.h>

#include <string>

enum class Direction
{
    down,
    left,
    right,
    up
};

class Player
{
public:

    Player();

    ~Player();

    cocos2d::Sprite *sprite()
    {
        return sprite_;
    }

    void init(cocos2d::Node *parent);

    void walk(Direction direction);

    void stop();

private:

    Player(const Player &) = delete;

    cocos2d::Animate *loadAnimation(const std::string & prefix, unsigned int count, cocos2d::SpriteFrameCache* cache);

    Direction facing_;
    cocos2d::Sprite *sprite_;
    cocos2d::Animate *walkDown_;
    cocos2d::Animate *walkLeft_;
    cocos2d::Animate *walkRight_;
    cocos2d::Animate *walkUp_;
};

#endif
