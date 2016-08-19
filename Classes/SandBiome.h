#ifndef  _SAND_BIOME_H_
#define  _SAND_BIOME_H_

#include "GameMap.h"

class SandBiome : public Biome
{
public:
    virtual const TerrainType *selectTerrain(GameMap *map, float noiseValue)
    {
        std::string terrainName;
        if (noiseValue < -0.333)
        {
            terrainName = "Water";
        }
        else
        {
            terrainName = "Sand";
        }

        return map->getTerrainType(terrainName);
    }

    static SandBiome* instance()
    {
        static SandBiome biome;
        return &biome;
    }
};

#endif
