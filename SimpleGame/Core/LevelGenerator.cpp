#include "stdafx.h"
#include "Core/LevelGenerator.h"

std::vector<std::vector<int>> LevelGenerator::generateMap() 
{
    int rows = 130;
    int cols = 250;
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));

    for (int y = 0; y < rows; ++y) 
    {
        for (int x = 0; x < cols; ++x) 
        {
            matrix[y][x] = rand();
        }
    }

    return matrix;
}