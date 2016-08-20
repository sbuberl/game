#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

class Player : public Entity
{
public:

    Player(const EntityInfo *info);

    void init(cocos2d::Node *parent) override;

};

#endif
