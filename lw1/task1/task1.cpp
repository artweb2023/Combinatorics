#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

const int INF = std::numeric_limits<int>::max();

struct HamiltonianCycle
{
	std::vector<std::vector<int>> matrix;
	std::vector<int> path;
	std::vector<int> minCycle;
	int minCost = INF;
};

bool IsOpenFile(std::ifstream& inputFile, const std::string& file)
{
	inputFile.open(file);
	if (!inputFile.is_open())
	{
		return false;
	}
	return true;
}

bool FileStreamData(std::ifstream& input, HamiltonianCycle& graph)
{
	std::string line;
	std::vector<std::vector<int>> tempMatrix;
	while (std::getline(input, line)) {
		std::vector<int> row;
		std::istringstream iss(line);
		int num;
		while (iss >> num) {
			row.push_back(num);
		}

		if (!row.empty()) {
			tempMatrix.push_back(row);
		}
	}
	size_t n = tempMatrix.size();
	for (size_t i = 0; i < n; ++i) {
		if (tempMatrix[i].size() != n) {
			return false;
		}
	}
	if (input.bad())
	{
		return false;
	}
	graph.matrix = tempMatrix;
	return input.eof();
}

bool IsReadFile(char* argv[], HamiltonianCycle& craph)
{
	std::ifstream inputFile;
	std::string file = argv[1];
	if (!IsOpenFile(inputFile, file))
	{
		std::cout << "Failed to open '" << file << "' file\n";
		return false;
	}
	if (!FileStreamData(inputFile, craph))
	{
		std::cout << "Failed to read in the '" << file << "' file\n";
		return false;
	}
	return true;
}

bool isHamiltonianCycle(HamiltonianCycle& data, int n)
{
	std::vector<bool> visited(n, false);
	for (int i = 1; i < n; ++i)
	{
		if (!data.matrix[data.path[i - 1]][data.path[i]] || visited[data.path[i]])
		{
			return false;
		}
		visited[data.path[i]] = true;
	}
	return data.matrix[data.path[n - 1]][data.path[0]] && !visited[data.path[0]];
}

void InitializationPath(HamiltonianCycle& data, int n)
{
	data.path.resize(n);
	for (int i = 0; i < n; ++i)
	{
		data.path[i] = i;
	}
}

bool IsFindMinCycle(HamiltonianCycle& data)
{
	int lengthPath = static_cast<int> (data.matrix.size());
	InitializationPath(data, lengthPath);
	do
	{
		if (isHamiltonianCycle(data, lengthPath))
		{
			int cost = 0;
			for (int i = 1; i < lengthPath; ++i)
			{
				cost += data.matrix[data.path[i - 1]][data.path[i]];
			}
			cost += data.matrix[data.path[lengthPath - 1]][data.path[0]];
			if (cost < data.minCost)
			{
				data.minCost = cost;
				data.minCycle = data.path;
			}
			return true;
		}
	} while (std::next_permutation(data.path.begin(), data.path.end()));
	return false;
}

void PrintResult(HamiltonianCycle& data)
{
	std::cout << "Minimum cost of a Hamiltonian cycle: " << data.minCost << std::endl;
	std::cout << "Hamilton cycle: ";
	for (int vertex : data.minCycle)
	{
		std::cout << vertex + 1 << " ";
	}
	std::cout << data.minCycle[0] + 1 << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: Task1.exe <input file name>\n";
		return 1;
	}
	HamiltonianCycle data;
	if (!IsReadFile(argv, data))
	{
		return 1;
	}
	if (!IsFindMinCycle(data))
	{
		std::cout << "No found\n";
		return 1;
	}
	PrintResult(data);
	return 0;
}