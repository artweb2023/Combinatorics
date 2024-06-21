#include "BranchAndBoundMethod.h"

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

void FindMinElemRow(Matrix& matrix, std::vector<int>& minElemRow)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		auto minElementIter = std::min_element(matrix[i].begin(), matrix[i].end(), [](int a, int b) {
			return a != INF && (b == INF || a < b);
			});
		int minElement = (minElementIter != matrix[i].end()) ? *minElementIter : INF;
		if (minElement == INF)
		{
			minElemRow.push_back(0);
			continue;
		}
		minElemRow.push_back(minElement);
	}
}

int ReduceRows(Matrix& matrix, std::vector<int>& minElemRow)
{
	int minCostRow = 0;
	for (int i = 0; i < matrix.size(); ++i)
	{
		int minElement = minElemRow[i];
		if (minElement == INF) continue;
		std::transform(matrix[i].begin(), matrix[i].end(), matrix[i].begin(),
			[minElement](int element) {
				return (element != INF) ? element - minElement : INF;
			});
		minCostRow += minElement;
	}
	return minCostRow;
}

void FindMinElemColumns(Matrix& matrix, std::vector<int>& minElemCol)
{
	for (int j = 0; j < matrix[0].size(); ++j)
	{
		int minElement = INF;
		for (int i = 0; i < matrix.size(); ++i)
		{
			if (matrix[i][j] != INF && matrix[i][j] < minElement)
			{
				minElement = matrix[i][j];
			}
		}
		if (minElement == INF)
		{
			minElemCol.push_back(0);
			continue;
		}
		minElemCol.push_back(minElement);
	}
}

int ReduceColumns(Matrix& matrix, std::vector<int>& minElemCol)
{
	int minCostCol = 0;
	for (int j = 0; j < matrix[0].size(); ++j)
	{
		int minElement = minElemCol[j];
		if (minElement == INF) continue;
		for (int i = 0; i < matrix.size(); ++i)
		{
			if (matrix[i][j] != INF)
				matrix[i][j] = (matrix[i][j] != INF) ? matrix[i][j] - minElement : INF;
		}
		minCostCol += minElement;
	}
	return minCostCol;
}

int FindMinElem(std::vector<int>& elements)
{
	return *std::min_element(elements.begin(), elements.end());
}

int FindMinElemForFines(const Matrix& matrix, int rowIdx, int colIdx, std::vector<int>& minElemRow,
	std::vector<int>& minElemCol)
{
	std::vector<int> minElemRowTemp;
	std::vector<int> minElemColTemp;
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] != INF && i == rowIdx && j != colIdx)
			{
				minElemRowTemp.push_back(matrix[i][j]);
			}
			if (matrix[i][j] != INF && i != rowIdx && j == colIdx)
			{
				minElemColTemp.push_back(matrix[i][j]);
			}
		}
	}
	int cost = 0;
	if (!minElemRowTemp.empty() && !minElemColTemp.empty())
	{
		cost = FindMinElem(minElemRowTemp) + FindMinElem(minElemColTemp);
	}
	minElemRowTemp.clear();
	minElemColTemp.clear();
	return cost;
}

void FindFines(const Matrix& matrix, Matrix& fines)
{
	fines.resize(matrix.size(), std::vector<int>(matrix[0].size(), 0));
	std::vector<int> minElemRow(matrix.size(), INF);
	std::vector<int> minElemCol(matrix[0].size(), INF);
	for (int row = 0; row < matrix.size(); ++row)
	{
		for (int col = 0; col < matrix[row].size(); ++col)
		{
			if (matrix[row][col] == 0)
			{
				fines[row][col] = FindMinElemForFines(matrix, row, col, minElemRow, minElemCol);
			}
			else
			{
				fines[row][col] = 0;
			}
		}
	}
	minElemRow.clear();
	minElemCol.clear();
}

std::pair<int, int> FindMaxPosition(const Matrix& fines)
{
	int maxRow = 0;
	int maxCol = 0;
	int maxValue = fines[maxRow][maxCol];

	for (int row = 0; row < fines.size(); ++row)
	{
		for (int col = 0; col < fines[row].size(); ++col)
		{
			if (fines[row][col] > maxValue && row != col)
			{
				maxRow = row;
				maxCol = col;
				maxValue = fines[row][col];
			}
		}
	}

	return std::make_pair(maxRow, maxCol);
}

void SelectEdge(Matrix& matrix, std::pair<int, int> maxPosition)
{
	for (int col = 0; col < matrix[maxPosition.first].size(); ++col)
	{
		matrix[maxPosition.first][col] = INF;
	}
	for (int row = 0; row < matrix.size(); ++row)
	{
		matrix[row][maxPosition.second] = INF;
	}
	matrix[maxPosition.second][maxPosition.first] = INF;
}

bool CheckMatrix(const Matrix& matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] != INF && matrix[i][j] != 0)
			{
				return false;
			}
		}
	}
	return true;
}

void SelectRemainder(const Matrix& matrix, const Distance& distance, std::vector<Distance>& path)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] == 0 && i != j)
			{
				Distance newDistance = distance;
				newDistance.dist = std::make_pair(i, j);
				newDistance.cost = distance.cost;
				path.push_back(newDistance);
			}
		}
	}
}

int FindLowerBound(Matrix& matrix)
{
	std::vector<int> minElemRow;
	std::vector<int> minElemCol;
	int minCostRow;
	FindMinElemRow(matrix, minElemRow);
	minCostRow = ReduceRows(matrix, minElemRow);
	int minCostCol;
	FindMinElemColumns(matrix, minElemCol);
	minCostCol = ReduceColumns(matrix, minElemCol);
	return minCostRow + minCostCol;
}

void FindBranchAndBound(Matrix& matrix, std::vector<Distance>& path, std::vector<Distance>& noSelectDistance, int minCost)
{
	std::vector<int> minElemRow;
	std::vector<int> minElemCol;
	Matrix fines;
	Distance distPath;
	Distance noSelectDist;
	std::pair<int, int> maxPos;
	int minCostRow;
	int minCostCol;
	FindFines(matrix, fines);
	maxPos = FindMaxPosition(fines);
	noSelectDist.cost = minCost + fines[maxPos.first][maxPos.second];
	noSelectDist.dist = std::make_pair(maxPos.second, maxPos.first);
	noSelectDist.matrix = matrix;
	noSelectDistance.push_back(noSelectDist);
	if (minCost <= noSelectDist.cost)
	{
		distPath.matrix = matrix;
		SelectEdge(matrix, maxPos);
		FindMinElemRow(matrix, minElemRow);
		minCostRow = ReduceRows(matrix, minElemRow);
		FindMinElemColumns(matrix, minElemCol);
		minCostCol = ReduceColumns(matrix, minElemCol);
		distPath.cost = minCost + minCostRow + minCostCol;
		distPath.dist = maxPos;
		path.push_back(distPath);
	}
	if (!CheckMatrix(matrix) && maxPos.first != maxPos.second)
	{
		FindBranchAndBound(matrix, path, noSelectDistance, distPath.cost);
	}
	else
	{
		SelectRemainder(matrix, distPath, path);
	}
}

void PrintPath(const std::vector<int>& paths, int minCost)
{
	for (auto path : paths)
	{
		std::cout << path + 1;
	}
	std::cout << std::endl;
	std::cout << "Min cost: " << minCost << std::endl;
}

bool CheckNoSelectDistance(const std::vector<Distance>& distance, const std::vector<Distance>& noSelectDistance, std::pair<int, int>& position)
{
	for (int i = 0; i < distance.size(); ++i)
	{
		for (int j = 0; j < noSelectDistance.size(); ++j)
		{
			if (distance[i].cost < noSelectDistance[j].cost)
			{
				position = distance[i].dist;
				return true;
			}
		}
	}
	return false;
}

Matrix FindMatrix(const std::vector<std::vector<Distance>>& allPaths, std::pair<int, int>& position)
{
	Matrix matrix;
	for (const auto& path : allPaths)
	{
		for (const auto& p : path)
		{
			if (p.dist == position)
			{
				matrix = p.matrix;
			}
		}
	}
	return matrix;
}

void FindPath(Matrix& matrix, int minCostBound, std::vector<std::vector<Distance>>& allPaths)
{
	std::vector<Distance> paths;
	std::vector<Distance> noSelectDistance;
	FindBranchAndBound(matrix, paths, noSelectDistance, minCostBound);
	allPaths.push_back(paths);
	std::pair<int, int> position = std::make_pair(0, 0);
	if (CheckNoSelectDistance(paths, noSelectDistance, position) && !paths.empty() && position.first != position.second)
	{
		matrix = FindMatrix(allPaths, position);
		matrix[position.first][position.second] = INF;
		paths.clear();
		noSelectDistance.clear();
		FindPath(matrix, minCostBound, allPaths);
	}
}

bool FindCycle(const std::vector<Distance>& paths, std::vector<int>& path)
{
	std::vector<bool> visited(paths.size(), false);
	int start = 0;
	path.push_back(start);
	while (path.size() <= paths.size())
	{
		bool found = false;
		for (int i = 0; i < paths.size(); ++i)
		{
			if (!visited[i] && paths[i].dist.first == start)
			{
				path.push_back(paths[i].dist.second);
				visited[i] = true;
				start = paths[i].dist.second;
				found = true;
				break;
			}
		}
		if (!found)
		{
			break;
		}
	}
	if (path.front() == path.back())
	{
		return true;
	}
	return false;
}

bool FindMinCostCycle(const std::vector<std::vector<Distance>>& allPaths,
	const Matrix& matrix, std::vector<int>& path, int& minCost)
{
	for (int i = 0; i < allPaths.size(); ++i)
	{
		if (allPaths[i].size() == matrix[0].size() && FindCycle(allPaths[i], path))
		{
			minCost = allPaths[i][i].cost;
			return true;
		}
	}
	return false;
}

void FindMinCycle(Matrix& matrix)
{
	Matrix duplicate = matrix;
	std::vector<std::vector<Distance>> allPaths;
	std::vector<int> path;
	int minCost = 0;
	int minCostBound = FindLowerBound(matrix);
	FindPath(matrix, minCostBound, allPaths);
	if (FindMinCostCycle(allPaths, duplicate, path, minCost))
	{
		PrintPath(path, minCost);
	}
	else
	{
		std::cout << "No path";
	}
}
