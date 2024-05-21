#include "SpatialGrid.hpp"
#include <set>

namespace Super
{
SpatialGrid::SpatialGrid(uint32_t gridWidth, uint32_t gridHeight, uint32_t numCellsX, uint32_t numCellsY)
    : mGridWidth{gridWidth}, mGridHeight{gridHeight}
{
    // Initialize grid and map pointers.
    mMap = std::make_unique<std::unordered_map<std::string, std::vector<Entity*>>>();
    mGrid = std::make_unique<std::vector<Cell>>();

    // algorithm to fill mGrid with cells.
    //
    for(int i = 0; i < numCellsY; i++) 
    {
        for(int j = 0; j < numCellsX; j++) 
        {
            Cell cell{};
            cell.position = glm::vec2(gridWidth * (j/numCellsX), gridHeight * (i/numCellsY));
            cell.size = glm::vec2(gridWidth / numCellsX, gridHeight / numCellsY);

            mGrid->push_back(cell);
        }
    }

    // (Entities will be assigned to cells every frame (before any collisions are checked), 
    // so there's no need to initally set the grid here).
}

SpatialGrid::~SpatialGrid() 
{

}

void SpatialGrid::Update(std::vector<Entity>& entities, std::vector<std::vector<CollisionPair>>* pairs) 
{
    ResetGrid();
    for(auto& entity : entities) 
    {
        AssignEntityToGridCell(entity);
    }

    pairs->clear();

    for(auto& cell : *mMap.get()) 
    {
        pairs->push_back(GetPairsPerCell(cell.second));
    }
}

std::vector<CollisionPair> SpatialGrid::GetPairsPerCell(std::vector<Entity*>& entities) const 
{
    std::vector<CollisionPair> pairs{};

    for(int i = 0; i < entities.size(); i++) 
    {
        for(int j = 0; j < entities.size(); j++) 
        {
            if(i == j) continue;
            pairs.push_back({entities[i], entities[j]});
        }
    }

    std::vector<CollisionPair> sortedPairs = RemoveDuplicates(pairs);

    return sortedPairs;
}

std::vector<CollisionPair> SpatialGrid::RemoveDuplicates(std::vector<CollisionPair>& pairs) const 
{
    // Function to remove duplicates from vector of structs
    std::set<CollisionPair> uniqueSet(pairs.begin(), pairs.end());
    return std::vector<CollisionPair>(uniqueSet.begin(), uniqueSet.end());
}


void SpatialGrid::ResetGrid() 
{
    mMap->clear();
}

void SpatialGrid::AssignEntityToGridCell(Entity& entity) 
{
    // Checks which cell the most left vertex is in.
    //
    const int xCellLeft = round((float)entity.bounds.min.x / mGridWidth);
    const int yCellLeft = round((float)entity.bounds.min.y / mGridHeight);
    const std::string leftCell = std::to_string(xCellLeft) + std::to_string(yCellLeft);

    // Pushes the entity into the appropriate cell.
    //
    if(mMap->count(leftCell)) 
    {
        mMap->operator[](leftCell).push_back(&entity);
    }
    else 
    {
        mMap->operator[](leftCell) = std::vector<Entity*>{&entity};
    }

    // Checks which cell the most right vetex is in.
    //
    const int xCellRight = round((float)(entity.bounds.max.x) / mGridWidth);
    const int yCellRight = round((float)(entity.bounds.max.y) / mGridHeight);
    const std::string rightCell = std::to_string(xCellRight) + std::to_string(yCellRight);

    // Only pushes the entity into the appropriate cell if its different
    // from the other cell (we don't want duplicates in the same cell).
    //
    if(rightCell != leftCell) 
    {
        if(mMap->count(rightCell)) 
        {
            mMap->operator[](rightCell).push_back(&entity);
        }
        else 
        {
            mMap->operator[](rightCell) = std::vector<Entity*>{&entity};
        }
    }
}

}