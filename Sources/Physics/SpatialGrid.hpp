#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <unordered_map>
#include "Scene/Entity.hpp"


namespace Super
{
typedef struct cell 
{
    glm::vec2 position; // bottom left point for the cell.
    glm::vec2 size;
} Cell;

typedef struct collisionpair 
{
    Entity* A;
    Entity* B;

    // Comparison operator that compares the labels of each entity.
    // Used for removing duplicates from the map of collision pairs, since we don't
    // want to register collisions more than once for any entitiy in a single frame.
    bool operator<(const collisionpair& other) const 
    {
        return (A->label < other.A->label) ||
            (A->label == other.A->label && B->label < other.B->label) ||
            (A->label == other.B->label && B->label < other.A->label);
    }

} CollisionPair;

class SpatialGrid 
{
public:
    SpatialGrid(uint32_t gridWidth, uint32_t gridHeight, uint32_t numCellsX, uint32_t numCellsY);
    ~SpatialGrid();

    // Public Getter for the vector of entities at a given grid cell.
    inline std::vector<Entity*>& GetEntitiesInCell(std::string cell) { return mMap->operator[](cell); }

    // Public Getter for the entire map.
    inline std::unordered_map<std::string, std::vector<Entity*>>& GetMap() { return *mMap; }

    inline uint32_t GetGridWidth() const { return mGridWidth; }
    inline uint32_t GetGridHeight() const { return mGridHeight; }


    void Update(std::vector<Entity>& entities, std::vector<std::vector<CollisionPair>>* pairs);

private:
    std::vector<CollisionPair> GetPairsPerCell(std::vector<Entity*>& entities) const;
    std::vector<CollisionPair> RemoveDuplicates(std::vector<CollisionPair>& pairs) const;
    void ResetGrid();
    void AssignEntityToGridCell(Entity& entity);
    
    std::unique_ptr<std::unordered_map<std::string, std::vector<Entity*>>> mMap = nullptr;
    std::unique_ptr<std::vector<Cell>> mGrid = nullptr;

    uint32_t mGridWidth{0};
    uint32_t mGridHeight{0};
};
}