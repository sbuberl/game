#ifndef  _BIOME_H_
#define  _BIOME_H_

#include "TerrainType.h"

class GameMap;

class Biome
{
public:
    virtual ~Biome() = default;

    virtual const TerrainType *selectTerrain(GameMap *map, float noiseValue) = 0;
};

#endif
