#define CATCH_CONFIG_MAIN
#include "/combinatorics/catch2/catch.hpp"

#include "/combinatorics/lw4/NumberOfTrees/NumberOfTrees.h"
#include "/combinatorics/lw4/NumberOfTrees/ReadFromFile.h"

SCENARIO("Find Number of tree in Adjacency Matrix 4x4")
{
	Matrix adjacencyMatrix = {
		{0, 1, 1, 1},
		{1, 0, 1, 1},
		{1, 1, 0, 1},
		{1, 1, 1, 0}
	};
	GIVEN("adjacency Matrix")
	{
		Matrix kirgofMatrix;
		SetKirgofMatrix(adjacencyMatrix, kirgofMatrix);
		Matrix minor = GetMinor(kirgofMatrix);
		WHEN("GetCountTree call")
		{
			double count = CalculateDeterminant(minor);
			THEN("Check count of tree")
			{
				REQUIRE(count == 16);
			}
		}
	}
}

SCENARIO("Find Number of tree in Adjacency Matrix 5x5")
{
	Matrix adjacencyMatrix = {
		{0, 1, 1, 1, 1},
		{1, 0, 0, 0, 0},
		{1, 0, 0, 1, 0},
		{1, 0, 1, 0, 1},
		{1, 0, 0, 1, 0}
	};
	GIVEN("adjacency Matrix")
	{
		Matrix kirgofMatrix;
		SetKirgofMatrix(adjacencyMatrix, kirgofMatrix);
		WHEN("GetCountTree call")
		{
			double count = GetCountTree(kirgofMatrix);
			THEN("Check count of tree")
			{
				REQUIRE(count == 8.0);
			}
		}
	}
}
