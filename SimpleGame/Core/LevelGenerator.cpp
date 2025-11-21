#include "stdafx.h"
#include "fstream"
#include "iostream"
#include "Core/LevelGenerator.h"
#include <Core/ResourceManager.h>
#include <random>


extern ResourceManager& g_ResourceManager;

LevelGenerator& LevelGenerator::getInstance()
{
	static LevelGenerator instance;
	return instance;
}

LevelGenerator::LevelGenerator()
{
	matrix = std::vector<std::vector<int>>(rows, std::vector<int>(cols));
}

void LevelGenerator::GenerateMatrix()
{
	ReadObjectsInfo();
	srand(time(NULL));
	int startNode = rand() % 20 + 1;
	path = { startNode };
	std::vector<bool> visited(21, false);
	visited[startNode] = true;

	if (FindHamiltonianPath(path, visited)) {
		std::cout << "Hamiltonian Path found:\n";
		for (int n : path) std::cout << n << " ";
		std::cout << std::endl;
	}
	else {
		std::cout << "No Hamiltonian Path found starting from " << startNode << std::endl;
	}

	for (auto& [id, object] : objectsInfoMap)
	{
		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				if (CheckConditions(x, y, rows, cols, id))
				{
					matrix[y][x] = id;
				}
			}
		}
	}
}

void LevelGenerator::ReadObjectsInfo()
{
	Json::Value objectsInfo = g_ResourceManager.getJson("objectsInfo");

	for (const auto& key : objectsInfo.getMemberNames()) {

		int keyInt = std::stoi(key);
		const Json::Value& value = objectsInfo[key];

		std::ostringstream buffer;
		buffer << value.toStyledString();


		objectsInfoMap[keyInt] = buffer.str();
	}
}

bool LevelGenerator::CheckConditions(int x, int y, int rows, int cols, int id)
{
	if (matrix[y][x] != 0)
		return false;
	int spacing = 6;

	std::vector<int> rowPositions;
	int sectorsRowSize = (rows - 30) / 4;
	int currentY = 0;

	for (int i = 0; i < 5; ++i) {
		rowPositions.push_back(currentY);
		currentY += spacing + sectorsRowSize;
	}


	std::vector<int> colPositions;
	int sectorsColSize = (cols - 36) / 5;
	int currentX = 0;

	for (int i = 0; i < 6; ++i) {
		colPositions.push_back(currentX);
		currentX += spacing + sectorsColSize;
	}

	//===============================================

	for (int i = 0; i < path.size(); i++) {
		if (path[i] == path[i + 1] - 1 && i + 1 < path.size())
		{

		}
	}

	//===============================================
	switch (id) {
	case 1:
		for (int row : rowPositions) {
			for (int col : colPositions) {
				if (x == col && y == row)
				{
					for (int i = y; i < y + 6; i++)
					{
						for (int j = x; j < x + 6; j++)
						{
							matrix[i][j] = -1;
						}
					}
					return true;
				}
			}
		}
		return false;
	case 2:
		for (int col : colPositions) {
			if (x == col)
			{
				for (int i = y; i < y + 25; ++i)
				{
					for (int j = x; j < x + 6; ++j)
					{
						matrix[i][j] = -1;
					}
				}
				return true;
			}

		}
		return false;

	case 3:
		for (int row : rowPositions) {
			if (y == row)
			{
				for (int i = y; i < y + 6; ++i)
				{
					for (int j = x; j < x + 22; ++j)
					{
						matrix[i][j] = -1;
					}
				}
				return true;
			}
		}
		return false;
	default:
		return false;
	}
}

void LevelGenerator::CreateLevel()
{
	GenerateMatrix();


	Json::Value root = g_ResourceManager.getJson("terrain");

	Json::Value& levelData = root["level_3"]["3"];

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < cols; ++x)
		{
			int matrixValue = matrix[y][x];

			auto it = objectsInfoMap.find(matrixValue);
			if (it != objectsInfoMap.end())
			{
				const std::string& valueStr = it->second;

				Json::Value valueJson;
				Json::CharReaderBuilder readerBuilder;
				std::string errs;

				std::istringstream ss(valueStr);
				if (Json::parseFromStream(readerBuilder, ss, &valueJson, &errs))
				{
					valueJson["x"] = x * 10;
					valueJson["y"] = y * 10;

					std::string key =
						std::to_string(matrixValue) + "-" +
						std::to_string(x) + "-" +
						std::to_string(y);

					levelData[key] = valueJson;
				}
			}
		}
	}


	g_ResourceManager.setJson("terrain", root);


}


bool LevelGenerator::FindHamiltonianPath(std::vector<int>& path, std::vector<bool>& visited) {
	if (path.size() == graph.size()) {
		return true;
	}
	int current = path.back();
	std::vector<int> neighbors = graph[current];
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(neighbors.begin(), neighbors.end(), g);

	for (int neighbor : neighbors) {
		if (!visited[neighbor]) {
			visited[neighbor] = true;
			path.push_back(neighbor);
			if (FindHamiltonianPath(path, visited)) {
				return true;
			}
			path.pop_back();
			visited[neighbor] = false;
		}
	}
	return false;
}