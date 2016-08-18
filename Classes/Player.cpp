#include "Player.h"

USING_NS_CC;

Player::Player() : Entity("hero")
{
}

void Player::init(Node *parent)
{
    SpriteBatchNode* heroBatch = SpriteBatchNode::create("hero.png");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("hero.plist");

    sprite_ = Sprite::createWithSpriteFrameName("hero_walk_down_00");
    sprite_->setPosition(parent->getContentSize().width / 2, parent->getContentSize().height / 2);
    facing_ = Direction::down;

    heroBatch->addChild(sprite_);
    parent->addChild(heroBatch);

    walkDown_ = loadAnimation("walk_down", 4, cache);
    walkLeft_ = loadAnimation("walk_left", 4, cache);
    walkRight_ = loadAnimation("walk_right", 4, cache);
    walkUp_ = loadAnimation("walk_up", 4, cache);
}
