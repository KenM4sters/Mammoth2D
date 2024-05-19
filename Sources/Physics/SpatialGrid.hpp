#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <unordered_map>
#include "Scene/Entity.hpp"

typedef struct cell 
{
    glm::vec2 position; // bottom left point for the cell.
    glm::vec2 size;
} Cell;

namespace Super
{
class SpatialGrid 
{
public:
    SpatialGrid(uint32_t gridWidth, uint32_t gridHeight, uint32_t numCellsX, uint32_t numCellsY);
    ~SpatialGrid();

    // Public Getter for the vector of entities at a given grid cell.
    inline std::vector<Entity*>& GetEntitiesInCell(std::string cell) { return mMap->operator[](cell); }

    // Public Getter for the entire map.
    inline std::unordered_map<std::string, std::vector<Entity*>>& GetMap() { return *mMap; }

    void Update(std::vector<Entity>& entities);

private:
    void ResetGrid();
    void AssignEntityToGridCell(Entity& entity);
    
    std::unique_ptr<std::unordered_map<std::string, std::vector<Entity*>>> mMap = nullptr;
    std::unique_ptr<std::vector<Cell>> mGrid = nullptr;

    uint32_t mGridWidth{0};
    uint32_t mGridHeight{0};
};
}