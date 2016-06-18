#include "MapBuilder.h"

#include "noiseutils.h"

#include <noise/noise.h>

#include <random>

using namespace noise;

void MapBuilder::buildMap(GameMap *map, int width, int height)
{
    buildTerrain(map, width, height);
}

void MapBuilder::buildTerrain(GameMap *map, int width, int height)
{
    constexpr int tileWidth = 32;

    int rows = height / tileWidth;
    int columns = width / tileWidth;

    std::random_device rd;
    std::default_random_engine random{rd()};

    module::Perlin perlin;
    perlin.SetSeed(random());

    utils::NoiseMap terrainNoise;
    utils::NoiseMapBuilderPlane terrainMapBuilder;
    terrainMapBuilder.SetSourceModule(perlin);
    terrainMapBuilder.SetDestNoiseMap(terrainNoise);
    terrainMapBuilder.SetDestSize(columns * 10, rows * 10);
    terrainMapBuilder.SetBounds(6, 10, 1, 5);
    terrainMapBuilder.Build();

    map->setMapSize(columns, rows);

    for (int row = 0; row < rows; ++row)
    {
        const float *rowValues = terrainNoise.GetConstSlabPtr(row);

        for (int column = 0; column < columns; ++column)
        {
            std::string terrainName;
            cocos2d::Vec2 tile(column, row);
            const float cellValue = *rowValues;
            rowValues += 5;

            if (cellValue < -0.3333)
            {
                terrainName = "Water";
                map->setCollision(tile);
            }
            else if (cellValue < -0.20)
            {
                terrainName = "Sand";  // desert
            }
            else if (cellValue < 0.5333)
            {
                terrainName = "Grass";	// grass
            }
            else if (cellValue < 0.70)
            {
                terrainName = "Clean Dirt";  // dirt
            }
            else
            {
                terrainName = "Snow";
            }

            const TerrainType *terrainType = map->getTerrainType(terrainName);
            uint32_t gid = terrainType->randomTile();
            map->setTile(gid, tile);
        }
    }
}

