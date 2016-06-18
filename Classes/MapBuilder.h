#ifndef _MAP_BUILDER_H_
#define _MAP_BUILDER_H_

#include "GameMap.h"

class MapBuilder
{
public:

    void buildMap(GameMap *map, int width, int height);

private:
    void buildTerrain(GameMap *map, int width, int height);
};

#endif

