
#include "GameMap.h"
#include "GrassBiome.h"
#include "SandBiome.h"
#include "SnowBiome.h"
#include "Utils.h"

#include <tinyxml2/tinyxml2.h>

#include <random>

GameMap::GameMap(cocos2d::TMXTiledMap *tmxMap, cocos2d::TMXLayer *terrain, cocos2d::TMXLayer *walkable,
    std::vector<TerrainType> terrains, std::unordered_map<std::string, int> terrainLookup, Biome *biome)
    : tmxMap_{tmxMap}, terrainLayer_{terrain}, walkableLayer_{walkable}, terrainTypes_(terrains), terrainLookup_(terrainLookup),
      biome_(biome)
{
    tmxMap_->retain();
}

GameMap::~GameMap()
{
    tmxMap_->release();
}

const TerrainType *GameMap::getTerrainType(const std::string &name) const
{
    auto iter = terrainLookup_.find(name);
    return iter != terrainLookup_.end() ? &terrainTypes_[iter->second] : nullptr;
}

void GameMap::setMapSize(int columns, int rows)
{
    cocos2d::Size mapSize(columns, rows);
    tmxMap_->setMapSize(mapSize);
    terrainLayer_->setLayerSize(mapSize);
    walkableLayer_->setLayerSize(mapSize);
}

bool GameMap::hasCollision(const cocos2d::Point &tile) const
{
    int tileGid = walkableLayer_->getTileGIDAt(tile);
    if (tileGid)
    {
        auto properties = tmxMap_->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty())
        {
            auto collision = properties["Collision"].asString();
            if (collision == "true")
            {
                return true;
            }
        }
    }

    return false;
}

cocos2d::Point GameMap::tileCoordForPosition(cocos2d::Point position)
{
    float scaleFactor = cocos2d::Director::getInstance()->getContentScaleFactor();
    float x = scaleFactor * position.x / tmxMap_->getTileSize().width;
    float y = ((tmxMap_->getMapSize().height * tmxMap_->getTileSize().height) - (scaleFactor * position.y)) / tmxMap_->getTileSize().height;
    return cocos2d::Vec2(x, y);
}

GameMap *GameMap::loadTmx(const std::string &tmxFile, const std::string &terrainName, const std::string &walkableName)
{
    cocos2d::TMXTiledMap *tmxMap = cocos2d::TMXTiledMap::create(tmxFile);
    tmxMap->setAnchorPoint({0, 0});
    tmxMap->setPosition({0, 0});

    cocos2d::TMXLayer *terrainLayer = tmxMap->getLayer(terrainName);
    cocos2d::TMXLayer *walkable = tmxMap->getLayer(walkableName);
    walkable->setVisible(false);

    std::random_device rd;
    std::default_random_engine randomBiome{rd()};
    int biomeNum = randomBiome() % 3;
    Biome *biome;
    switch (biomeNum)
    {
    case 1:
        biome = SandBiome::instance();
        break;
    case 2:
        biome = SnowBiome::instance();
        break;
    default:
        biome = GrassBiome::instance();
        break;
    }

    std::unordered_map<std::string, int> terrainLookup;
    std::vector<TerrainType> terrains;

    tinyxml2::XMLDocument tmxDocument;
    tmxDocument.LoadFile(tmxFile.c_str());
    tinyxml2::XMLElement *mapRoot = tmxDocument.RootElement();
    tinyxml2::XMLElement *tileset = mapRoot->FirstChildElement("tileset");
    tinyxml2::XMLElement *terrainTypes = tileset->FirstChildElement("terraintypes");
    if (terrainTypes != nullptr)
    {
        tinyxml2::XMLElement *terrain = terrainTypes->FirstChildElement("terrain");
        for (int id = 0; terrain != nullptr; ++id)
        {
            std::string terrainName = terrain->Attribute("name");
            int defaultTile = terrain->IntAttribute("tile");
            terrains.push_back({terrainName, defaultTile});
            terrainLookup[terrainName] = id;

            terrain = terrain->NextSiblingElement("terrain");
        }
    }

    tinyxml2::XMLElement *tile = tileset->FirstChildElement("tile");
    while (tile != nullptr)
    {
        int tileId = tile->IntAttribute("id");
        std::string terrainIds = tile->Attribute("terrain");
        std::vector<std::string> terrainPieces;
        tokenize(terrainIds, ",", [&](const std::string &terrainId)
        {
            terrainPieces.push_back(terrainId);
        });

        if (std::adjacent_find(terrainPieces.begin(), terrainPieces.end(), std::not_equal_to<std::string>()) == terrainPieces.end())
        {
            int terrainId = std::stoi(terrainPieces[0]);
            terrains[terrainId].addTile(tileId);
        }

        tile = tile->NextSiblingElement("tile");
    }

    return new GameMap{tmxMap, terrainLayer, walkable, terrains, terrainLookup, biome};
}

