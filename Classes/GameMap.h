#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include "TerrainType.h"
#include <cocos2d.h>

#include <string>
#include <unordered_map>
#include <vector>

class GameMap
{
public:

    ~GameMap();

    cocos2d::TMXTiledMap *getTmxMap()
    {
        return tmxMap_;
    }

    const TerrainType *getTerrainType(const std::string &name) const;

    void setMapSize(int columns, int rows);

    bool hasCollision(const cocos2d::Point &tile) const;

    void setCollision(int column, int row)
    {
        setCollision(cocos2d::Vec2(column, row));
    }

    void setCollision(const cocos2d::Point &tile)
    {
        int firstGid = walkableLayer_->getTileSet()->_firstGid;
        walkableLayer_->setTileGID(firstGid, tile);
    }

    void setTile(uint32_t gid, int column, int row)
    {
        setTile(gid, cocos2d::Vec2(column, row));
    }

    void setTile(uint32_t gid, const cocos2d::Point &tile)
    {
        terrainLayer_->setTileGID(gid + 1, tile);
    }

    cocos2d::Point tileCoordForPosition(cocos2d::Point position);

    static GameMap *loadTmx(const std::string &tmxFile, const std::string &terrainLayer, const std::string &walkableLayer);

private:
    GameMap(cocos2d::TMXTiledMap * tmxMap, cocos2d::TMXLayer * terrain, cocos2d::TMXLayer * walkable, std::vector<TerrainType> terrains,
        std::unordered_map<std::string, int> terrainLookup);

    cocos2d::TMXTiledMap *tmxMap_;
    cocos2d::TMXLayer *terrainLayer_;
    cocos2d::TMXLayer *walkableLayer_;
    std::vector<TerrainType> terrainTypes_;
    std::unordered_map<std::string, int> terrainLookup_;
};

#endif
