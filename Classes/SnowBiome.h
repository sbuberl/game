#ifndef  _ICE_BIOME_H_
#define  _ICE_BIOME_H_

#include "GameMap.h"

class SnowBiome : public Biome
{
public:
    virtual const TerrainType *selectTerrain(GameMap *map, float noiseValue)
    {
        std::string terrainName;
        if (noiseValue < -0.333)
        {
            terrainName = "Ice";
        }
        else
        {
            terrainName = "Snow";
        }

        return map->getTerrainType(terrainName);
    }

    static SnowBiome* instance()
    {
        static SnowBiome biome;
        return &biome;
    }
};

#endif
