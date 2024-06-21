#include "BranchAndBoundMethod.h"

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		if (!args)
		{
			return 1;
		}
		Matrix matrix;
		ReadMatrixFromFile(args->matrixFileName, matrix);
		FindMinCycle(matrix);
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
}