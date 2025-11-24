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
	matrix = std::vector<std::vector<int>>(m_Rows, std::vector<int>(m_Cols));
}

void LevelGenerator::MarkRect(std::vector<std::vector<int>>& m, int x, int y, int w, int h)
{
	int m_Rows = m.size();
	int m_Cols = m[0].size();

	for (int i = y; i < y + h && i < m_Rows; ++i)
	{
		for (int j = x; j < x + w && j < m_Cols; ++j)
		{
			m[i][j] = -1;
		}
	}
}

int LevelGenerator::BlocksPath(int x, int y, int p1, int p2, const std::vector<int>& rowPos, const std::vector<int>& colPos)
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
		if (y > rowPos[r1] && y < rowPos[r1 + 1] && x == colPos[c1])
		{
			return 1;
		}
	}
	// move right
	if (p2 == p1 + 1)
	{
		if (y > rowPos[r1] && y < rowPos[r1 + 1] && x == colPos[c2])
		{
			return 2;
		}
	}
	// move up
	if (p2 == p1 - 5)
	{
		if (x > colPos[c1] && x < colPos[c1 + 1] && y == rowPos[r1])
		{
			return 3;
		}
	}
	// move down
	if (p2 == p1 + 5)
	{
		if (x > colPos[c1] && x < colPos[c1 + 1] && y == rowPos[r2])
		{
			return 4;
		}
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

	/*for (auto& [id, object] : objectsInfoMap)
	{
		for (int y = 0; y < m_Rows; y++)
		{
			for (int x = 0; x < m_Cols; x++)
			{
				if (CheckExtraConditions(x, y, id))
				{
					matrix[y][x] = id;
				}
			}
		}
	}*/
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

bool LevelGenerator::CheckPathConditions(int x, int y, int id)
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
				if (BlocksPath(x, y, path[i], path[i + 1], rowPos, colPos) == 1 || BlocksPath(x, y, path[i], path[i + 1], rowPos, colPos) == 2)
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
			{
				continue;
			}
			for (int i = 0; i + 1 < path.size(); i++)
			{
				if (BlocksPath(x, y, path[i], path[i + 1], rowPos, colPos) == 3 || BlocksPath(x, y, path[i], path[i + 1], rowPos, colPos) == 4)
				{
					return false;
				}
			}

			MarkRect(matrix, x, y, 22, 6);
			return true;
		}
		return false;

	case 7:
		if (BlocksPath(x  , y  , path[0], path[1], rowPos, colPos) == 1)
		{
			MarkRect(matrix, x, y, 12, 12);
			return true;
		}
		return false;

	default:
		return false;
	}
}

int LevelGenerator::GetMovementType(int p1, int p2, int p3)
{
	int d1 = p2 - p1;
	int d2 = p3 - p2;
	if (d1 == -5)
	{
		if (d2 == 1) return 0;
		if (d2 == -1) return 1;
		if (d2 == -5) return 2;
		if (d2 == 5) return 12;
	}
	if (d1 == 5)
	{
		if (d2 == 1) return 3;
		if (d2 == -1) return 4;
		if (d2 == 5) return 5;
		if (d2 == -5) return 13;
	}
	if (d1 == 1)
	{
		if (d2 == 1) return 6;
		if (d2 == 5) return 9;
		if (d2 == -5) return 11;
	}
	if (d1 == -1)
	{
		if (d2 == -1) return 7;
		if (d2 == 5) return 8;
		if (d2 == -5) return 10;
	}
	return -1;
}


//bool LevelGenerator::CheckExtraConditions(int x, int y, int id)
//{
//	if (matrix[y][x] != 0)
//	{
//		return false;
//	}
//
//
//	for (int i = 1; i + 1 < path.size(); i++)
//	{
//		int r1 = path[i] / 5;
//		int r2 = path[i + 1] / 5;
//
//		int c1 = path[i] % 5;
//		int c2 = path[i + 1] % 5;
//		int midX = (colPos[c1] + colPos[c1 + 1]) / 2;
//		switch (GetMovementType(path[i - 1], path[i], path[i + 1]))
//		{
//		case 1:
//
//			return false;
//
//		case 2:
//
//			return false;
//
//		case 3:
//
//			return false;
//		case 4:
//
//			return false;
//
//		case 5:
//
//			return false;
//
//		case 6:
//
//			return false;
//		case 7:
//
//			return false;
//
//		case 8:		
//			if (x > midX && x < colPos[c1 + 1] && id==3)
//			{
//				MarkRect(matrix, x, y, 22, 6);
//				return true;
//			}
//
//			//x > colPos[c1] && x < colPos[c1 + 1] && y == rowPos[r1]
//			return false;
//
//
//		case 9:
//
//			return false;
//		case 10:
//
//			return false;
//
//		case 11:
//
//			return false;
//
//		case 12:
//
//			return false;
//
//		case 13:
//
//			return false;
//
//		default:
//			return false;
//		}
//	}
//
//}


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

void LevelGenerator::CreateLevel()
{
	GenerateMatrix();

	Json::Value root = g_ResourceManager.getJson("terrain");
	Json::Value& levelData = root["level_3"]["3"];

	for (int y = 0; y < m_Rows; ++y)
	{
		for (int x = 0; x < m_Cols; ++x)
		{
			int val = matrix[y][x];
			auto it = objectsInfoMap.find(val);
			if (it == objectsInfoMap.end())
				continue;

			Json::Value valueJson;
			Json::CharReaderBuilder builder;
			std::string errs;

			std::istringstream ss(it->second);
			if (Json::parseFromStream(builder, ss, &valueJson, &errs))
			{
				valueJson["x"] = x * 10;
				valueJson["y"] = y * 10;

				std::string key = std::to_string(val) + "-" +
					std::to_string(x) + "-" +
					std::to_string(y);

				levelData[key] = valueJson;
			}
		}
	}

	g_ResourceManager.setJson("terrain", root);
}
