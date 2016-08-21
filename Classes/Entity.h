#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <cocos2d.h>
#include <json/document.h>

#include <string>

enum class Direction
{
    down,
    left,
    right,
    up
};

struct EntityInfo
{
    virtual ~EntityInfo() = default;

    std::string name;
    std::string prefix;
    std::string sheetFile;
    std::string framesPlist;
    std::string animationsPlist;

    void read(rapidjson::Value &value)
    {
        name = value["name"].GetString();
        prefix = value["prefix"].GetString() + std::string("_");
        sheetFile = value["sheetFile"].GetString();
        framesPlist = value["frames"].GetString();
        animationsPlist = value["animations"].GetString();
    }
};

class Entity
{
public:
    virtual ~Entity();

    cocos2d::Sprite *sprite()
    {
        return sprite_;
    }

    virtual void init(cocos2d::Node *parent);

    void walk(Direction direction);

    void stop();

protected:

    Entity(const EntityInfo *info);

    cocos2d::Animate *loadAnimation(const std::string &name, cocos2d::AnimationCache *cache);

    const EntityInfo * const info_;
    Direction facing_;
    cocos2d::Sprite *sprite_;
    cocos2d::Animate *walkDown_;
    cocos2d::Animate *walkLeft_;
    cocos2d::Animate *walkRight_;
    cocos2d::Animate *walkUp_;

private:

    Entity(const Entity &) = delete;
};

#endif

