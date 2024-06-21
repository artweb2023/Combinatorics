#include "ReadFromFile.h"

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: GammaAlgorithm.exe <file name>\n";
		return std::nullopt;
	}
	Args args;
	args.matrixFileName = argv[1];
	return args;
}

bool ReadFileStream(std::ifstream& input, AdjMatrix& matrix)
{
	std::string line;
	while (std::getline(input, line))
	{
		int value;
		std::istringstream iss(line);
		std::vector<int> row;
		while (iss >> value)
		{
			row.push_back(value);
		}
		matrix.push_back(row);
	}
	return input.eof();
}

bool ReadMatrixFromFile(const std::string& fileName, AdjMatrix& matrix)
{
	std::ifstream inputFile;
	inputFile.open(fileName);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open '" + fileName + "' file");
	}
	if (!ReadFileStream(inputFile, matrix))
	{
		throw std::runtime_error("Failed to read from '" + fileName + "' file");
	}
	return true;
}