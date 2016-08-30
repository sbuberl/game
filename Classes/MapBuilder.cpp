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
    auto scale = cocos2d::Director::getInstance()->getContentScaleFactor();
    auto tileSize = map->getTmxMap()->getTileSize();
    int rows = height / (tileSize.height / scale);
    int columns = width / (tileSize.width / scale);

    Biome *biome = map->biome();

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
            cocos2d::Vec2 tile(column, row);
            const float cellValue = *rowValues;
            rowValues += 5;

            const TerrainType *terrainType = biome->selectTerrain(map, cellValue);
            std::string terrainName = terrainType->name();
            if (terrainName == "Water" || terrainName == "Ice")
            {
                map->setCollision(tile);
            }

            uint32_t gid = terrainType->randomTile();
            map->setTile(gid, tile);
        }
    }
}

