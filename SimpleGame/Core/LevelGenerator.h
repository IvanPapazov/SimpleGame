#pragma once
#include <vector>
#include <unordered_map>
#include <string>

class LevelGenerator
{
public:
    static LevelGenerator& getInstance();
    void CreateLevel();
private:
    int m_Rows = 130;
    int m_Cols = 256;

    Json::Value root;
    Json::Value& levelData;

    std::unordered_map<int, std::string> objectsInfoMap;
    std::vector<std::vector<int>> matrix;
    std::vector<int> path;

    std::vector<int> pathDirections;

    std::vector<int> rowPos;
    std::vector<int> colPos;

    std::unordered_map<int, std::vector<int>> graph = {
        {0,  {1,5}},
        {1,  {0,2,6}},
        {2,  {1,3,7}},
        {3,  {2,4,8}},
        {4,  {3,9}},
        {5,  {0,6,10}},
        {6,  {1,5,7,11}},
        {7,  {2,6,8,12}},
        {8,  {3,7,9,13}},
        {9,  {4,8,14}},
        {10, {5,11,15}},
        {11, {6,10,12,16}},
        {12, {7,11,13,17}},
        {13, {8,12,14,18}},
        {14, {9,13,19}},
        {15, {10,16}},
        {16, {11,15,17}},
        {17, {12,16,18}},
        {18, {13,17,19}},
        {19, {14,18}}
    };

    LevelGenerator();
    LevelGenerator(const LevelGenerator&) = delete;
    LevelGenerator& operator=(const LevelGenerator&) = delete;

    void GenerateMatrix();
    void ReadObjectsInfo();
    void CalculateRowAndColPositions();
    bool CheckPathConditions(int& x, int y, int id);
    bool FindHamiltonianPath(std::vector<int>& path, std::vector<bool>& visited);
    bool FindPathDirections(int id);
    void MarkRect(std::vector<std::vector<int>>& m, int x, int y, int w, int h);
    bool BlocksPath(int x, int y, int p1, int p2, const std::vector<int>& rowPos, const std::vector<int>& colPos);
};
