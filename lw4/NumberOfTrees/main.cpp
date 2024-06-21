#include "NumberOfTrees.h"
#include "ReadFromFile.h"

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		if (!args)
		{
			return 1;
		}
		Matrix adjacencyMatrix;
		ReadMatrixFromFile(args->matrixFileName, adjacencyMatrix);
		Matrix kirgofMatrix;
		SetKirgofMatrix(adjacencyMatrix, kirgofMatrix);
		double count = GetCountTree(kirgofMatrix);
		std::cout << "Number of spanning trees: " << count << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}