#ifndef _TERRAIN_TYPE_H_
#define _TERRAIN_TYPE_H_

#include <string>
#include <vector>

class TerrainType
{
public:

    TerrainType(const std::string &name, int defaultTile)
        : name_(name)
    {
        addTile(defaultTile);
    }

    std::string name() const
    {
        return name_;
    }

    void addTile(int tile)
    {
        fullTiles_.push_back(tile);
    }

    int randomTile() const
    {
        int index = std::rand() % fullTiles_.size();
        return fullTiles_[index];
    }

private:

    const std::string name_;
    std::vector<int> fullTiles_;
};

#endif
