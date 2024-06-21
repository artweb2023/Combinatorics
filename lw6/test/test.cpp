#define CATCH_CONFIG_MAIN
#include "../HungarianAlgorithm/HungarianAlgorithm.h"
#include "/combinatorics/catch2/catch.hpp"

SCENARIO("Test Hungarian Algorithm with matrix 7x7")
{
	Matrix matrix = {
		{50, INF, INF, 10, INF, 20, INF},
		{INF, 30, 45, INF, 30, INF, 25},
		{INF, 5, INF, INF, 10, 15, INF},
		{15, INF, INF, 20, INF, INF, INF},
		{INF, INF, 20, INF, INF, 5, INF},
		{INF, INF, INF, INF, 40, INF, 5},
		{INF, INF, INF, 15, INF, INF, INF}
	};
	GIVEN("adjacency Matrix")
	{
		WHEN("Check Hungarian Algorithm")
		{
			std::vector<int> expectedAssignment = { 5, 4, 1, 0, 2, 6, 3 };
			THEN("Check minCost")
			{
				std::vector<int> actualAssignment;
				Matrix copy = matrix;
				FindAssignment(copy, actualAssignment);
				REQUIRE(actualAssignment == expectedAssignment);
				int expectedTotalCost = 110;
				int actualTotalCost = 0;
				for (size_t i = 0; i < actualAssignment.size(); ++i)
				{
					actualTotalCost += matrix[i][actualAssignment[i]];
				}
				REQUIRE(actualTotalCost == expectedTotalCost);
			}
		}
	}
}

SCENARIO("Test Hungarian Algorithm with matrix 4x4")
{
	Matrix matrix = {
		{INF, 7, 1, 3},
		{1, 6, 4, 6},
		{17, 1, 5, 1},
		{INF, 6, 10, 4}
	};
	GIVEN("adjacency Matrix")
	{
		WHEN("Check Hungarian Algorithm")
		{
			std::vector<int> expectedAssignment = { 2, 0, 1, 3 };
			THEN("Check minCost")
			{
				std::vector<int> actualAssignment;
				Matrix copy = matrix;
				FindAssignment(copy, actualAssignment);
				REQUIRE(actualAssignment == expectedAssignment);
				int expectedTotalCost = 7;
				int actualTotalCost = 0;
				for (size_t i = 0; i < actualAssignment.size(); ++i)
				{
					actualTotalCost += matrix[i][actualAssignment[i]];
				}
				REQUIRE(actualTotalCost == expectedTotalCost);
			}
		}
	}
}

SCENARIO("Test Hungarian Algorithm with matrix 5x5")
{
	Matrix matrix = {
		{9, 2, 7, 8, 6},
		{6, 4, 3, 7, 5},
		{5, 8, 1, 8, 3},
		{7, INF, 9, 4, 2},
		{INF, 8, 4, 3, 7}
	};
	GIVEN("adjacency Matrix")
	{
		WHEN("Check Hungarian Algorithm")
		{
			std::vector<int> expectedAssignment = { 1, 0, 2, 4, 3 };
			THEN("Check minCost")
			{
				std::vector<int> actualAssignment;
				Matrix copy = matrix;
				FindAssignment(copy, actualAssignment);
				REQUIRE(actualAssignment == expectedAssignment);
				int expectedTotalCost = 14;
				int actualTotalCost = 0;
				for (size_t i = 0; i < actualAssignment.size(); ++i)
				{
					actualTotalCost += matrix[i][actualAssignment[i]];
				}
				REQUIRE(actualTotalCost == expectedTotalCost);
			}
		}
	}
}