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

LevelGenerator::LevelGenerator() : levelData(root)
{
	matrix = std::vector<std::vector<int>>(m_Rows, std::vector<int>(m_Cols));
}

void LevelGenerator::MarkRect(std::vector<std::vector<int>>& m, int x, int y, int w, int h)
{
	int m_Rows = m.size();
	if (m_Rows == 0) return;
	int m_Cols = m[0].size();

	if (x < 0) x = 0;
	if (y < 0) y = 0;

	int maxW = std::min(w, m_Cols - x);
	int maxH = std::min(h, m_Rows - y);

	for (int i = y; i < y + maxH; ++i)
	{
		for (int j = x; j < x + maxW; ++j)
		{
			m[i][j] = -1;
		}
	}
}

bool LevelGenerator::BlocksPath(int x, int y, int p1, int p2, const std::vector<int>& rowPos, const std::vector<int>& colPos)
{
	int r1 = p1 / 5;
	int r2 = p2 / 5;

	int c1 = p1 % 5;
	int c2 = p2 % 5;

	if (r1 + 1 >= rowPos.size()) return 0;
	if (c1 + 1 >= colPos.size()) return 0;

	// move left
	if (p2 == p1 - 1)
	{
		return (y > rowPos[r1] && y < rowPos[r1 + 1] && x == colPos[c1]);
	}
	// move right
	if (p2 == p1 + 1)
	{
		return (y > rowPos[r1] && y < rowPos[r1 + 1] && x == colPos[c2]);
	}
	// move up
	if (p2 == p1 - 5)
	{
		return (x > colPos[c1] && x < colPos[c1 + 1] && y == rowPos[r1]);
	}
	// move down
	if (p2 == p1 + 5)
	{
		return (x > colPos[c1] && x < colPos[c1 + 1] && y == rowPos[r2]);
	}
	return false;
}



void LevelGenerator::GenerateMatrix()
{
	ReadObjectsInfo();
	CalculateRowAndColPositions();
	srand(time(NULL));

	int startNode = rand() % 20;
	path = { startNode };

	std::vector<bool> visited(20, false);
	visited[startNode] = true;

	if (FindHamiltonianPath(path, visited))
	{
		std::cout << "Hamiltonian Path found:\n";
		for (int n : path) std::cout << n << " ";
		std::cout << "\n";
	}
	else
	{
		std::cout << "No Hamiltonian Path found starting from " << startNode << "\n";
	}

	FindPathDirections(0);


	for (auto& [id, object] : objectsInfoMap)
	{
		for (int y = 0; y < m_Rows; y++)
		{
			for (int x = 0; x < m_Cols; x++)
			{
				if (CheckPathConditions(x, y, id))
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

	for (const auto& key : objectsInfo.getMemberNames())
	{
		int keyInt = std::stoi(key);
		objectsInfoMap[keyInt] = objectsInfo[key].toStyledString();
	}
}

void LevelGenerator::CalculateRowAndColPositions()
{
	const int spacing = 6;

	int rowSize = (m_Rows - 30) / 4;
	for (int r = 0, cy = 0; r < 5; r++, cy += spacing + rowSize)
	{
		rowPos.push_back(cy);
	}


	int colSize = (m_Cols - 36) / 5;
	for (int c = 0, cx = 0; c < 6; c++, cx += spacing + colSize)
	{
		colPos.push_back(cx);
	}
}

bool LevelGenerator::CheckPathConditions(int& x, int y, int id)
{

	if (matrix[y][x] != 0)
	{
		return false;
	}

	switch (id)
	{
	case 1:
		for (int ry : rowPos)
		{
			for (int cx : colPos)
			{
				if (x == cx && y == ry)
				{
					MarkRect(matrix, x, y, 6, 6);
					return true;
				}
			}
		}
		return false;

	case 2:
		for (int k = 0; k < colPos.size(); k++)
		{
			if (x != colPos[k])
			{
				continue;
			}
			for (int i = 0; i + 1 < path.size(); i++)
			{
				if (BlocksPath(x, y, path[i], path[i + 1], rowPos, colPos))
				{
					return false;
				}
			}
			MarkRect(matrix, x, y, 6, 25);
			return true;
		}
		return false;

	case 3:
		for (int k = 0; k < rowPos.size(); k++)
		{
			if (y != rowPos[k])
				continue;

			for (int i = 0; i < path.size() - 1; i++)
			{
				if (BlocksPath(x, y, path[i], path[i + 1], rowPos, colPos))
				{
					bool nextIsVert = (i + 1 < pathDirections.size() &&
						(pathDirections[i + 1] == 4 || pathDirections[i + 1] == 2));

					bool prevIsVert = (i - 1 >= 0 &&
						(pathDirections[i - 1] == 4 || pathDirections[i - 1] == 2));

					switch (pathDirections[i])
					{
					case 6: case 9: case 7: case 3:
					{
						MarkRect(matrix, x, y, 44, 6);
						matrix[y][x + 29] = 4;
						matrix[y][x + 22] = 1;

						if (nextIsVert || prevIsVert)
							matrix[y - 6][x + 22] = 1;

						return true;
					}
					case 5: case 8: case 1: case 10:
					{
						MarkRect(matrix, x, y, 44, 6);
						matrix[y][x + 16] = 1;
						matrix[y][x + 1] = 4;

						if (nextIsVert || prevIsVert)
							matrix[y - 6][x + 16] = 1;

						x += 22;
						return true;
					}

					default:
						break;
					}
				}
			}
			MarkRect(matrix, x, y, 22, 6);
			return true;
		}

		return false;


	case 7: {
		//satrt
		int startIndex = 0;
		int startTile = path[startIndex];
		int startRow = startTile / 5;
		int startCol = startTile % 5;

		if (startRow + 1 >= rowPos.size()) return false;
		if (startCol + 1 >= colPos.size()) return false;

		int startDir = pathDirections[startIndex];

		int temp_y1 = rowPos[startRow + 1] - 12;
		int temp_x1 = 0;

		if (startDir == 5 || startDir == 8 || startDir == 10 || startDir == 4 || startDir == 1) {
			temp_x1 = colPos[startCol + 1] - 12;
		}
		else if (startDir == 6 || startDir == 7 || startDir == 9 || startDir == 2 || startDir == 3) {

			temp_x1 = colPos[startCol] + 6;
		}

		//end
		int endIndex = path.size() - 1;
		int endTile = path[endIndex];
		int endRow = endTile / 5;
		int endCol = endTile % 5;

		if (endRow + 1 >= rowPos.size()) return false;
		if (endCol + 1 >= colPos.size()) return false;

		int endDir = pathDirections[endIndex - 1];

		int temp_y2 = rowPos[endRow + 1] - 12;
		int temp_x2 = 0;

		if (endDir == 5 || endDir == 8 || endDir == 10 || endDir == 2 || endDir == 1) {
			temp_x2 = colPos[endCol + 1] - 12;
		}
		else if (endDir == 6 || endDir == 7 || endDir == 9 || endDir == 4 || endDir == 3) {
			temp_x2 = colPos[endCol] + 6;
		}

		if ((x == temp_x1 && y == temp_y1) ||
			(x == temp_x2 && y == temp_y2))
		{
			MarkRect(matrix, x, y, 12, 12);
			return true;
		}

		return false;
	}




	default:
		return false;
	}
}








bool LevelGenerator::FindHamiltonianPath(std::vector<int>& path, std::vector<bool>& visited)
{
	if (path.size() == graph.size())
	{
		return true;
	}

	int current = path.back();
	auto neighbors = graph[current];

	std::mt19937 g(std::random_device{}());
	std::shuffle(neighbors.begin(), neighbors.end(), g);

	for (int next : neighbors)
	{
		if (!visited[next])
		{
			visited[next] = true;
			path.push_back(next);

			if (FindHamiltonianPath(path, visited))
				return true;

			path.pop_back();
			visited[next] = false;
		}
	}
	return false;
}

bool LevelGenerator::FindPathDirections(int id)
{
	if (id >= path.size() - 1)
		return true;

	int current = path[id];
	int next = path[id + 1];

	int diff = next - current;

	int direction = -1;

	if (diff == 1)        direction = 2;
	else if (diff == -1)  direction = 4;

	else if (diff == 5)   direction = 3;
	else if (diff == -5)  direction = 1;

	if (direction == -1)
		return false;

	if (!pathDirections.empty())
	{
		int last = pathDirections.back();

		if (direction == 3)
		{
			if (last == 4) direction = 5;
			else if (last == 2) direction = 6;
			else if (last == 3 || last == 7) direction = 7;
		}
		if (direction == 1)
		{
			if (last == 4) direction = 8;
			else if (last == 2) direction = 9;
			else if (last == 1 || last == 10) direction = 10;
		}
	}

	pathDirections.push_back(direction);

	return FindPathDirections(id + 1);
}

void LevelGenerator::CreateLevel()
{
	GenerateMatrix();

	Json::Value terrainRoot = g_ResourceManager.getJson("terrain");
	Json::Value doorsRoot = g_ResourceManager.getJson("doors");
	Json::Value pathwaysRoot = g_ResourceManager.getJson("pathways");

	for (int y = 0; y < m_Rows; ++y)
	{
		for (int x = 0; x < m_Cols; ++x)
		{
			int val = matrix[y][x];
			auto it = objectsInfoMap.find(val);
			if (it == objectsInfoMap.end())
				continue;

			Json::Value* levelPtr = nullptr;

			if (val == 1 || val == 2 || val == 3)
			{
				levelPtr = &terrainRoot["level_3"]["3"];
			}
			else if (val == 4)
			{
				levelPtr = &pathwaysRoot["level_3"];
			}
			else if (val == 7)
			{
				levelPtr = &doorsRoot["level_3"];
			}

			if (!levelPtr) continue;

			Json::Value valueJson;
			Json::CharReaderBuilder builder;
			std::string errs;

			std::istringstream ss(it->second);
			if (Json::parseFromStream(builder, ss, &valueJson, &errs))
			{
				valueJson["x"] = x * 10;
				valueJson["y"] = y * 10;
				if (val == 7)
				{
					valueJson["nextLevel"] = "level_2";
					valueJson["currentLevel"] = "level_3";
				}

				std::string key = std::to_string(val) + "-" +
					std::to_string(x) + "-" +
					std::to_string(y);

				(*levelPtr)[key] = valueJson;
			}
		}
	}
	g_ResourceManager.setJson("terrain", terrainRoot);
	g_ResourceManager.setJson("doors", doorsRoot);
	g_ResourceManager.setJson("pathways", pathwaysRoot);
}

