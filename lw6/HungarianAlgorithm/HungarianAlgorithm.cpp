#include "HungarianAlgorithm.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

using Mark = std::vector<std::vector<bool>>;

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: task3.exe <file name>\n";
		return std::nullopt;
	}
	Args args;
	args.matrixFileName = argv[1];
	return args;
}

bool ReadFileStream(std::ifstream& input, Matrix& matrix)
{
	std::string line;
	while (std::getline(input, line))
	{
		int value;
		std::istringstream iss(line);
		std::vector<int> row;
		while (iss >> value)
		{
			if (value == 0)
			{
				row.push_back(INF);
			}
			else
			{
				row.push_back(value);
			}
		}
		matrix.push_back(row);
	}
	return input.eof();
}

bool ReadMatrixFromFile(const std::string& fileName, Matrix& matrix)
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

void ReduceRows(Matrix& matrix)
{
	for (auto& row : matrix)
	{
		auto minElement = *std::min_element(row.begin(), row.end());
		if (minElement == INF)
		{
			continue;
		}
		std::transform(row.begin(), row.end(), row.begin(),
			[minElement](int element) {
				return (element != INF) ? element - minElement : INF;
			});
	}
}

void ReduceColumns(Matrix& matrix)
{
	for (std::size_t j = 0; j < matrix[0].size(); ++j)
	{
		int minElement = INF;
		for (std::size_t i = 0; i < matrix.size(); ++i)
		{
			if (matrix[i][j] < minElement)
			{
				minElement = matrix[i][j];
			}
		}
		if (minElement == INF)
		{
			continue;
		}
		for (std::size_t i = 0; i < matrix.size(); ++i)
		{
			if (matrix[i][j] != INF)
			{
				matrix[i][j] -= minElement;
			}
		}
	}
}
// ищет нули в матрице, сохран€ет позиции пересечени€ элеметов по столбцам и строкам
void CoverZeros(const Matrix& matrix, std::vector<bool>& coveredRows, std::vector<bool>& coveredCols)
{
	Mark marked(matrix.size(), std::vector<bool>(matrix.size(), false));
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			if (matrix[i][j] == 0 && !coveredRows[i] && !coveredCols[j])
			{
				marked[i][j] = true;
				coveredRows[i] = true;
				coveredCols[j] = true;
			}
		}
	}
	std::fill(coveredRows.begin(), coveredRows.end(), false);
	std::fill(coveredCols.begin(), coveredCols.end(), false);
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			if (marked[i][j])
			{
				coveredCols[j] = true;
			}
		}
	}
}
// обновл€ет матрицу с учетом вычита мин элеметов строки и добавлени€ мин элемента столбца при пересечении столбцов и строк
void UpdateMatrix(Matrix& matrix, const std::vector<bool>& coveredRows, const std::vector<bool>& coveredCols)
{
	int minUncovered = INF;
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		if (!coveredRows[i])
		{
			for (size_t j = 0; j < matrix[i].size(); ++j)
			{
				if (!coveredCols[j])
				{
					minUncovered = std::min(minUncovered, matrix[i][j]);
				}
			}
		}
	}
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix[i].size(); ++j)
		{
			if (!coveredRows[i] && !coveredCols[j])
			{
				matrix[i][j] -= minUncovered;
			}
			else if (coveredRows[i] && coveredCols[j])
			{
				matrix[i][j] += minUncovered;
			}
		}
	}
}

// назначаем работников на работу с учетом текущего результата
void AssignJob(Matrix& matrix, std::vector<int>& assignment)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] == 0)
			{
				assignment.push_back(j);
				break;
			}
		}
	}
}
// провер€ю если есть совпадении назначени€ на работу 
bool CheckAssignJob(const std::vector<int>& assignment, std::pair <int, int>& pos)
{
	for (int i = 0; i < assignment.size(); ++i)
	{
		for (int j = i + 1; j < assignment.size(); ++j)
		{
			if (assignment[i] == assignment[j])
			{
				pos = std::make_pair(i, assignment[i]);
				return true;
			}
		}
	}
	return false;
}
// вычитаю минимальный элемент там где нашлось совпадение среди назначений
void ChangeMatrix(Matrix& matrix, std::pair<int, int> pos) {
	int row = pos.first;
	int col = pos.second;
	if (row >= matrix.size())
	{
		return;
	}
	auto& matrixRow = matrix[row];
	int minElement = INF;
	for (int j = 0; j < matrixRow.size(); ++j)
	{
		if (j != col && matrixRow[j] != INF)
		{
			minElement = std::min(minElement, matrixRow[j]);
		}
	}
	if (minElement == INF)
	{
		return;
	}
	for (int& element : matrixRow)
	{
		if (element != INF)
		{
			element -= minElement;
		}
	}
}
// измен€ем назначени€ работников
void ChangeAssign(const Matrix& matrix, std::vector<int>& assignment, std::pair<int, int> pos)
{
	assignment.clear();
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] == 0)
			{
				assignment.push_back(j);
				break;
			}
		}
	}
}

void FindAssignment(Matrix& matrix, std::vector<int>& assignment)
{
	ReduceRows(matrix);
	ReduceColumns(matrix);
	std::vector<bool> coveredRows(matrix.size(), false);
	std::vector<bool> coveredCols(matrix.size(), false);
	while (true)
	{
		CoverZeros(matrix, coveredRows, coveredCols);
		if (coveredCols.size() == matrix.size())
		{
			break;
		}
		UpdateMatrix(matrix, coveredRows, coveredCols);
	}
	AssignJob(matrix, assignment);
	std::pair <int, int> position;
	if (CheckAssignJob(assignment, position))
	{
		ChangeMatrix(matrix, position);
		ChangeAssign(matrix, assignment, position);
	}
}

void HungarianAlgorithm(Matrix& matrix)
{
	std::vector<int> assignment;
	Matrix copy = matrix;
	FindAssignment(matrix, assignment);
	int totalCost = 0;
	for (size_t i = 0; i < assignment.size(); ++i)
	{
		totalCost += copy[i][assignment[i]];
		std::cout << "Worker " << i + 1 << " assigned to job " << assignment[i] + 1 << " with cost "
			<< copy[i][assignment[i]] << "\n";
	}
	std::cout << "Total cost: " << totalCost << "\n";
}
