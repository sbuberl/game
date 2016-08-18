
#include "Entity.h"

USING_NS_CC;

Entity::Entity(const std::string &framePrefix)
    : framePrefix_{framePrefix + "_"}, sprite_{}, walkDown_{}, walkLeft_{}, walkRight_{}, walkUp_{}
{
}

Entity::~Entity()
{
    if (walkDown_)
        walkDown_->release();
    if (walkLeft_)
        walkLeft_->release();
    if (walkRight_)
        walkRight_->release();
    if (walkUp_)
        walkUp_->release();
}

void Entity::walk(Direction direction)
{
    sprite_->stopAllActions();
    Animate *animate;
    switch (direction)
    {
    case Direction::down:
        animate = walkDown_;
        break;
    case Direction::left:
        animate = walkLeft_;
        break;
    case Direction::right:
        animate = walkRight_;
        break;
    case Direction::up:
        animate = walkUp_;
        break;
    }

    facing_ = direction;
    sprite_->runAction(RepeatForever::create(animate));
}

void Entity::stop()
{
    sprite_->stopAllActions();
    std::string newFrameName = framePrefix_ + "walk_";
    switch (facing_)
    {
    case Direction::down:
        newFrameName += "down_00";
        break;
    case Direction::left:
        newFrameName += "left_00";
        break;
    case Direction::right:
        newFrameName += "right_00";
        break;
    case Direction::up:
        newFrameName += "up_00";
        break;
    }

    sprite_->setSpriteFrame(newFrameName);
}

Animate *Entity::loadAnimation(const std::string &name, unsigned int count, SpriteFrameCache* cache)
{
    Vector<SpriteFrame*> frames(count);

    std::string prefix = framePrefix_ + name + "_";
    for (unsigned int i = 0; i < count; ++i)
    {
        char buffer[5];
        std::sprintf(buffer, "%02d", i);
        std::string frameName = prefix + buffer;
        SpriteFrame* frame = cache->getSpriteFrameByName(frameName);
        frames.pushBack(frame);
    }

    Animation *animation = Animation::createWithSpriteFrames(frames, 0.2f);
    Animate *animate = Animate::create(animation);
    animate->retain();
    return animate;
}
