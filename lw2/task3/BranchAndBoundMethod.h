#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

const int INF = INT_MAX;

using Matrix = std::vector<std::vector<int>>;

struct Args
{
	std::string matrixFileName;
};

struct Distance
{
	int cost = 0;
	std::pair<int, int> dist;
	Matrix matrix;
};

std::optional<Args> ParseArgs(int argc, char* argv[]);
bool ReadFileStream(std::ifstream& input, Matrix& matrix);
bool ReadMatrixFromFile(const std::string& fileName, Matrix& matrix);
void FindMinCycle(Matrix& matrix);
void PrintPath(const std::vector<int>& paths, int minCost);