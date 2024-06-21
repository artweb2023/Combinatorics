#include "Network.h"
#include <iostream>


int main()
{
	int numberOfVertices, numberOfEdges, start, finish;
	std::cin >> numberOfVertices >> numberOfEdges >> start >> finish;
	NetworkFlow network(numberOfVertices);
	for (int i = 0; i < numberOfEdges; ++i)
	{
		int u, v, capacity;
		std::cin >> u >> v >> capacity;
		network.addEdge(u, v, capacity);
	}
	int maxFlow = network.maxFlow(start, finish);
	std::cout << "Max flow = " << maxFlow << std::endl;
	auto flow = network.getFlow();
	network.PrintNetwork(flow);
	return 0;
}