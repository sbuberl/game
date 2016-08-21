
#include "Entity.h"

USING_NS_CC;

Entity::Entity(const EntityInfo *info)
    : info_{info}, sprite_{}, walkDown_{}, walkLeft_{}, walkRight_{}, walkUp_{}
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

void Entity::init(Node *parent)
{
    SpriteBatchNode* batch = SpriteBatchNode::create(info_->sheetFile);
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile(info_->framesPlist);

    sprite_ = Sprite::createWithSpriteFrameName(info_->prefix + "walk_down_00");

    batch->addChild(sprite_);
    parent->addChild(batch);

    AnimationCache *animations = AnimationCache::getInstance();
    if (animations->getAnimation(info_->prefix + "walk_down") == nullptr)
    {
        animations->addAnimationsWithFile(info_->animationsPlist);
    }

    walkDown_ = loadAnimation("walk_down", animations);
    walkLeft_ = loadAnimation("walk_left", animations);
    walkRight_ = loadAnimation("walk_right", animations);
    walkUp_ = loadAnimation("walk_up", animations);
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
    std::string newFrameName = info_->prefix + "walk_";
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

Animate *Entity::loadAnimation(const std::string &name, AnimationCache *cache)
{
    std::string fullName = info_->prefix + name;
    Animation *animation = cache->getAnimation(fullName);
    Animate *animate = Animate::create(animation);
    animate->retain();
    return animate;
}
