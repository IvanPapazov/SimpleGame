#pragma once
#include <vector>
#include <unordered_map>
#include <string>

class LevelGenerator
{
public:
    static LevelGenerator& getInstance();

    void GenerateMatrix();
    void ReadObjectsInfo();
    void CreateLevel();
    bool CheckConditions(int x, int y, int rows, int cols, int id);

    bool FindHamiltonianPath(std::vector<int>& path, std::vector<bool>& visited);

private:
    int rows = 130;
    int cols = 256;
    std::unordered_map<int, std::string> objectsInfoMap;
    std::vector<std::vector<int>> matrix;
    std::vector<int> path;

    std::unordered_map<int, std::vector<int>> graph = {
    {1, {2,6}}, {2, {1,3,7}}, {3, {2,4,8}}, {4, {3,5,9}}, {5, {4,10}},
    {6, {1,7,11}}, {7, {2,6,8,12}}, {8, {3,7,9,13}}, {9, {4,8,10,14}}, {10, {5,9,15}},
    {11, {6,12,16}}, {12, {7,11,13,17}}, {13, {8,12,14,18}}, {14, {9,13,15,19}}, {15, {10,14,20}},
    {16, {11,17}}, {17, {12,16,18}}, {18, {13,17,19}}, {19, {14,18,20}}, {20, {15,19}}
    };


    LevelGenerator();
    LevelGenerator(const LevelGenerator&) = delete;
    LevelGenerator& operator=(const LevelGenerator&) = delete;
};
