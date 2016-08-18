#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <cocos2d.h>

#include <string>

enum class Direction
{
    down,
    left,
    right,
    up
};

class Entity
{
public:

    cocos2d::Sprite *sprite()
    {
        return sprite_;
    }

    virtual void init(cocos2d::Node *parent) = 0;

    void walk(Direction direction);

    void stop();

protected:

    Entity(const std::string &framePrefix);

    virtual ~Entity();

    cocos2d::Animate *loadAnimation(const std::string & prefix, unsigned int count, cocos2d::SpriteFrameCache* cache);

    const std::string framePrefix_;
    Direction facing_;
    cocos2d::Sprite *sprite_;
    cocos2d::Animate *walkDown_;
    cocos2d::Animate *walkLeft_;
    cocos2d::Animate *walkRight_;
    cocos2d::Animate *walkUp_;

private:

    Entity(const Entity &) = delete;
};

#endif

