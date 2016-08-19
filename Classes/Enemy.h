#ifndef  _ENEMY_H_
#define  _ENEMY_H_

#include "Entity.h"

class Enemy : public Entity
{
public:

    Enemy(const std::string &name, const std::string &prefix, const std::string &sheetFile, const std::string &plistFile);

    std::string name() const
    {
        return name_;
    }

    void init(cocos2d::Node *parent) override;

    void update(float delta, int fieldWidth, int fieldHeight);

private:
    const std::string name_;
    const std::string sheetFile_;
    const std::string plistFile_;
};

#endif
