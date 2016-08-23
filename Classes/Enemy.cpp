
#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(const EntityInfo *info)
    : Entity(info)
{
}

void Enemy::init(Node *parent)
{
    Entity::init(parent);

    std::random_device rd;
    std::default_random_engine randomDir{rd()};
    int dirNum = randomDir() % 4;
    facing_ = (Direction) dirNum;

    walk(facing_);
}

void Enemy::update(float delta, int fieldWidth, int fieldHeight, GameMap *map)
{
    int speed = 1;
    Size playerSize = sprite_->getTextureRect().size;
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
        facing_ = newDirection();
        walk(facing_);
        return;
    }

    if (!setPosition(playerPosition, map))
    {
        facing_ = newDirection();
        walk(facing_);
    }

}

Direction Enemy::newDirection()
{
    Direction direction;
    do
    {
        direction = (Direction)(rand() % 4);
    } while (direction == facing_);
    return direction;
}
