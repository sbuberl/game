#include "Player.h"

USING_NS_CC;

Player::Player(const EntityInfo *info) : Entity(info)
{
}

void Player::init(Node *parent)
{
    Entity::init(parent);

    sprite_->setPosition(parent->getContentSize().width / 2, parent->getContentSize().height / 2);
    facing_ = Direction::down;
}
