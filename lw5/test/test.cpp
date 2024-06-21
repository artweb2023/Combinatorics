#define CATCH_CONFIG_MAIN

#include "../MaxFlow/Network.h"
#include "/combinatorics/catch2/catch.hpp"


SCENARIO("Test MaxFlow")
{
	int numberOfVertices = 11;
	int numberOfEdges = 18;
	int start = 0;
	int finish = 10;
	GIVEN("Greate NetworkFlow object")
	{
		NetworkFlow network(numberOfVertices);
		WHEN("network add Edge")
		{
			network.addEdge(0, 3, 25);
			network.addEdge(0, 5, 45);
			network.addEdge(0, 8, 30);
			network.addEdge(3, 1, 15);
			network.addEdge(3, 4, 35);
			network.addEdge(5, 3, 10);
			network.addEdge(5, 4, 20);
			network.addEdge(5, 6, 15);
			network.addEdge(8, 6, 35);
			network.addEdge(8, 9, 45);
			network.addEdge(1, 2, 45);
			network.addEdge(4, 2, 10);
			network.addEdge(4, 10, 35);
			network.addEdge(6, 10, 25);
			network.addEdge(6, 7, 20);
			network.addEdge(9, 7, 25);
			network.addEdge(2, 10, 25);
			network.addEdge(7, 10, 15);
			int maxFlow = network.maxFlow(start, finish);
			THEN("Check Max Flow")
			{
				REQUIRE(maxFlow == 95);
			}
		}

	}
}