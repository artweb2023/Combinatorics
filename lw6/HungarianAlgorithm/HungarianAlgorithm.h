#pragma once

#include <optional>
#include <string>
#include <vector>

const int INF = INT_MAX;

using Matrix = std::vector<std::vector<int>>;

struct Args
{
	std::string matrixFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[]);
bool ReadFileStream(std::ifstream& input, Matrix& matrix);
bool ReadMatrixFromFile(const std::string& fileName, Matrix& matrix);
void FindAssignment(Matrix& matrix, std::vector<int>& assignment);
void HungarianAlgorithm(Matrix& matrix);