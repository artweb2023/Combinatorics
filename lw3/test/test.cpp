#define CATCH_CONFIG_MAIN
#include "../GammaAlgorithm/Faces.h"
#include "../GammaAlgorithm/Graph.h"
#include "../GammaAlgorithm/ReadFromFile.h"
#include "/combinatorics/catch2/catch.hpp"


SCENARIO("Test Gamma Algorithm")
{
	GIVEN("adjacency Matrix for K5 Graph")
	{
		AdjMatrix adjMatrix =
		{
			{0, 1, 1, 1, 1},
			{1, 0, 1, 1, 1},
			{1, 1, 0, 1, 1},
			{1, 1, 1, 0, 1},
			{1, 1, 1, 1, 0}
		};
		WHEN("getGraph call")
		{
			Graph gr(adjMatrix);
			THEN("call Gamma Algorithm")
			{
				auto planar = gr.getPlanarLaying();
				REQUIRE(planar == nullptr);
			}
		}
	}
	GIVEN("adjacency Matrix for Peterson Graph")
	{
		AdjMatrix adjMatrix =
		{
			{0, 1, 0, 0, 1, 1, 0, 0, 0, 0},
			{1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
			{0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
			{0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
			{1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 1, 1, 0},
			{0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
			{0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
			{0, 0, 0, 0, 1, 0, 0, 0, 0, 0}
		};
		WHEN("getGraph call")
		{
			Graph gr(adjMatrix);
			THEN("call Gamma Algorithm")
			{
				auto planar = gr.getPlanarLaying();
				REQUIRE(planar == nullptr);
			}
		}
	}

	GIVEN("adjacency Matrix K3 Graph")
	{
		AdjMatrix adjMatrix =
		{
			{0, 0, 0, 1, 1, 1},
			{0, 0, 0, 1, 1, 1},
			{0, 0, 0, 1, 1, 1},
			{1, 1, 1, 0, 0, 0},
			{1, 1, 1, 0, 0, 0},
			{1, 1, 1, 0, 0, 0}
		};
		WHEN("getGraph call")
		{
			Graph gr(adjMatrix);
			THEN("call Gamma Algorithm")
			{
				auto planar = gr.getPlanarLaying();
				REQUIRE(planar == nullptr);
			}
		}
	}

	GIVEN("adjacency Matrix K4 Graph")
	{
		AdjMatrix adjMatrix =
		{
			{0, 1, 1, 1},
			{1, 0, 1, 1},
			{1, 1, 0, 1},
			{1, 1, 1, 0},
		};
		WHEN("getGraph call")
		{
			Graph gr(adjMatrix);
			THEN("call Gamma Algorithm")
			{
				auto planar = gr.getPlanarLaying();
				REQUIRE(planar);
				THEN("Check External and Interior Faces")
				{
					const auto& externalFace = planar->getExternal();
					const auto& interiorFaces = planar->getInterior();

					std::vector<int> expectedExternalFace = { 3, 2, 0 };
					std::vector<std::vector<int>> expectedInteriorFaces = {
						{0, 1, 2},
						{0, 3, 1},
						{3, 2, 0},
						{3, 2, 1}
					};

					CHECK(externalFace == expectedExternalFace);
					REQUIRE(interiorFaces.size() == expectedInteriorFaces.size());
					for (size_t i = 0; i < interiorFaces.size(); ++i)
					{
						CHECK(interiorFaces[i] == expectedInteriorFaces[i]);
					}
				}
				delete planar;
			}
		}
	}
}