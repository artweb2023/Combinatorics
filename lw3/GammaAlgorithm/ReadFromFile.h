#pragma once

#include "stdafx.h"

using AdjMatrix = std::vector<std::vector<int>>;

struct Args
{
	std::string matrixFileName;
};


std::optional<Args> ParseArgs(int argc, char* argv[]);
bool ReadFileStream(std::ifstream& input, AdjMatrix& matrix);
bool ReadMatrixFromFile(const std::string& fileName, AdjMatrix& matrix);


