#include "SpatialGrid.hpp"

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

void SpatialGrid::Update(std::vector<Entity>& entities) 
{
    ResetGrid();
    for(auto& entity : entities) 
    {
        AssignEntityToGridCell(entity);
    }
}


void SpatialGrid::ResetGrid() 
{
    mMap->clear();
}

void SpatialGrid::AssignEntityToGridCell(Entity& entity) 
{
    const int cXcell = round((float)entity.transform.position.x / mGridWidth);
    const int cYcell = round((float)entity.transform.position.y / mGridHeight);

    const std::string cell = std::to_string(cXcell) + std::to_string(cYcell);


    if(mMap->count(cell)) 
    {
        mMap->operator[](cell).push_back(&entity);
    }
    else 
    {
        mMap->operator[](cell) = std::vector<Entity*>{&entity};
    }
}

}