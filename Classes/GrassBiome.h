#ifndef  _GRASS_BIOME_H_
#define  _GRASS_BIOME_H_

#include "GameMap.h"

class GrassBiome : public Biome
{
public:
    virtual const TerrainType *selectTerrain(GameMap *map, float noiseValue)
    {
        std::string terrainName;
        if (noiseValue < -0.3333)
        {
            terrainName = "Water";
        }
        else if (noiseValue < -0.20)
        {
            terrainName = "Sand";  // sand
        }
        else if (noiseValue < 0.8)
        {
            terrainName = "Grass";	// grass
        }
        else
        {
            terrainName = "Clean Dirt";
        }

        return map->getTerrainType(terrainName);
    }

    static GrassBiome* instance()
    {
        static GrassBiome biome;
        return &biome;
    }
};

#endif
