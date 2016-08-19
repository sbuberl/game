
#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(const std::string &name, const std::string &prefix, const std::string &sheetFile, const std::string &plistFile)
    : Entity(prefix), name_(name), sheetFile_(sheetFile), plistFile_(plistFile)
{
}

void Enemy::init(Node *parent)
{
    SpriteBatchNode* heroBatch = SpriteBatchNode::create(sheetFile_);
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile(plistFile_);

    sprite_ = Sprite::createWithSpriteFrameName(framePrefix_ + "walk_down_00");
    std::random_device rd;
    std::default_random_engine randomDir{rd()};
    int dirNum = randomDir() % 4;
    facing_ = (Direction) dirNum;

    heroBatch->addChild(sprite_);
    parent->addChild(heroBatch);

    walkDown_ = loadAnimation("walk_down", 4, cache);
    walkLeft_ = loadAnimation("walk_left", 4, cache);
    walkRight_ = loadAnimation("walk_right", 4, cache);
    walkUp_ = loadAnimation("walk_up", 4, cache);

    walk(facing_);
}

void Enemy::update(float delta, int fieldWidth, int fieldHeight)
{
    int speed = 1;
    Size playerSize = sprite_->getContentSize();
    float playerHalfWidth = playerSize.width / 2;
    float playerHalfHeight = playerSize.height / 2;
    Vec2 playerPosition = sprite_->getPosition();
    float playerX = sprite_->getPositionX();
    float playerY = sprite_->getPositionY();

    if (facing_ == Direction::right && playerX < fieldWidth - playerHalfWidth)
    {
        playerPosition.x += speed;
    }
    else if (facing_ == Direction::left && playerX > playerHalfWidth)
    {
        playerPosition.x -= speed;
    }
    else if (facing_ == Direction::up && playerY < fieldHeight - playerHalfHeight)
    {
        playerPosition.y += speed;
    }
    else if (facing_ == Direction::down && playerY > playerHalfHeight)
    {
        playerPosition.y -= speed;
    }
    else
    {
        stop();
        facing_ = (Direction)(rand() % 4);
        walk(facing_);
        return;
    }

    sprite_->setPosition(playerPosition);
}
