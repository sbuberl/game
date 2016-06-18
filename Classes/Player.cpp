#include "Player.h"

USING_NS_CC;

Player::Player()
    : sprite_{}, walkDown_{}, walkLeft_{}, walkRight_{}, walkUp_{}
{
}

Player::~Player()
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

void Player::init(Node *parent)
{
    SpriteBatchNode* heroBatch = SpriteBatchNode::create("hero.png");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("hero.plist");

    sprite_ = Sprite::createWithSpriteFrameName("down1");
    sprite_->setPosition(parent->getContentSize().width / 2, parent->getContentSize().height / 2);
    facing_ = Direction::down;

    heroBatch->addChild(sprite_);
    parent->addChild(heroBatch);

    walkDown_ = loadAnimation("down", 4, cache);
    walkLeft_ = loadAnimation("left", 4, cache);
    walkRight_ = loadAnimation("right", 4, cache);
    walkUp_ = loadAnimation("up", 4, cache);
}

void Player::walk(Direction direction)
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

void Player::stop()
{
    sprite_->stopAllActions();
    std::string newFrameName;
    switch (facing_)
    {
    case Direction::down:
        newFrameName = "down1";
        break;
    case Direction::left:
        newFrameName = "left1";
        break;
    case Direction::right:
        newFrameName = "right1";
        break;
    case Direction::up:
        newFrameName = "up1";
        break;
    }

    sprite_->setSpriteFrame(newFrameName);
}

Animate *Player::loadAnimation(const std::string &prefix, unsigned int count, SpriteFrameCache* cache)
{
    Vector<SpriteFrame*> frames(count);

    for (unsigned int i = 1; i <= count; ++i)
    {
        std::string frameName = prefix + std::to_string(i);
        SpriteFrame* frame = cache->getSpriteFrameByName(frameName);
        frames.pushBack(frame);
    }

    Animation *animation = Animation::createWithSpriteFrames(frames, 0.2f);
    Animate *animate = Animate::create(animation);
    animate->retain();
    return animate;
}
