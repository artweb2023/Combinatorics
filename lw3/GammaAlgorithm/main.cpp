#include "Faces.h"
#include "Graph.h"
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
		AdjMatrix adjMatrix;
		ReadMatrixFromFile(args->matrixFileName, adjMatrix);
		Graph gr(adjMatrix);
		std::cout << "Original graph: " << std::endl;
		std::cout << gr.toString() << std::endl;
		auto planar = gr.getPlanarLaying();
		if (planar)
		{
			std::cout << planar->toString() << std::endl;
			delete planar;
		}
		else
		{
			std::cout << "Graph is not planar" << std::endl;
		}
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
}