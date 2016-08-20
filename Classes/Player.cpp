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

    walkDown_ = loadAnimation("walk_down", 9, cache);
    walkLeft_ = loadAnimation("walk_left", 9, cache);
    walkRight_ = loadAnimation("walk_right", 9, cache);
    walkUp_ = loadAnimation("walk_up", 9, cache);
}
