#ifndef  _ENEMY_H_
#define  _ENEMY_H_

#include "Entity.h"

class Enemy : public Entity
{
public:

    Enemy(const EntityInfo *info);

    void init(cocos2d::Node *parent) override;

    void update(float delta, int fieldWidth, int fieldHeight, GameMap *map);

private:

    Direction newDirection();

};

#endif
