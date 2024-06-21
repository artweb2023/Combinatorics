#pragma once

#include "stdafx.h"

using Matrix = std::vector<std::vector<double>>;

struct Args
{
	std::string matrixFileName;
};


std::optional<Args> ParseArgs(int argc, char* argv[]);
bool ReadFileStream(std::ifstream& input, Matrix& matrix);
bool ReadMatrixFromFile(const std::string& fileName, Matrix& matrix);


