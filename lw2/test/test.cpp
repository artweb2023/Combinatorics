#define CATCH_CONFIG_MAIN
#include "/combinatorics/catch2/catch.hpp"
#include "/combinatorics/lw2/task3/BranchAndBoundMethod.h"

SCENARIO("FindMinCycle works correctly with different graphs")
{
	GIVEN("Simple 3x3 graph")
	{
		Matrix matrix =
		{
			{ INF, 10, 15 },
			{ 10, INF, 20 },
			{ 15, 20, INF }
		};
		std::vector<int> expectedPath = { 1, 2, 3, 1 };
		int expectedMinCost = 45;
		std::ostringstream oss;
		std::streambuf* pbuf = std::cout.rdbuf();
		std::cout.rdbuf(oss.rdbuf());
		WHEN("FindMinCycle call")
		{
			FindMinCycle(matrix);
			std::cout.rdbuf(pbuf);
			std::string output = oss.str();
			THEN("Check if the path and min cost are correct")
			{
				for (int node : expectedPath)
				{
					REQUIRE(output.find(std::to_string(node)) != std::string::npos);
				}
				REQUIRE(output.find("Min cost: " + std::to_string(expectedMinCost)) != std::string::npos);
			}
		}
	}
	GIVEN("Graph with no Hamiltonian cycle")
	{
		Matrix matrix =
		{
			{ INF, 10, INF, 10 },
			{ 10, INF, 20, INF },
			{ INF, 20, INF, 30 },
			{ 10, INF, 30, INF }
		};
		std::ostringstream oss;
		std::streambuf* pbuf = std::cout.rdbuf();
		std::cout.rdbuf(oss.rdbuf());
		WHEN("FindMinCycle call")
		{
			FindMinCycle(matrix);
			std::cout.rdbuf(pbuf);
			std::string output = oss.str();
			THEN("Check if the output indicates no path exists")
			{
				REQUIRE(output.find("No path") != std::string::npos);
			}
		}
	}
	GIVEN("Larger 5x5 graph")
	{
		Matrix matrix =
		{
			{ INF, 20, 18, 12, 8 },
			{ 5, INF, 14, 7, 11 },
			{ 12, 18, INF, 6, 11 },
			{ 11, 17, 11, INF, 12 },
			{ 5, 5, 5, 5, INF }
		};
		std::vector<int> expectedPath = { 1, 5, 3, 4, 2, 1 };
		int expectedMinCost = 41;
		std::ostringstream oss;
		std::streambuf* pbuf = std::cout.rdbuf();
		std::cout.rdbuf(oss.rdbuf());
		WHEN("FindMinCycle call")
		{
			FindMinCycle(matrix);
			std::cout.rdbuf(pbuf);
			std::string output = oss.str();
			THEN("Check if the path and min cost are correct")
			{
				for (int node : expectedPath)
				{
					REQUIRE(output.find(std::to_string(node)) != std::string::npos);
				}
				REQUIRE(output.find("Min cost: " + std::to_string(expectedMinCost)) != std::string::npos);
			}
		}
	}
	GIVEN("Larger 6x6 graph")
	{
		Matrix matrix =
		{
			{ INF, 8, 1, INF, 3, INF },
			{ 8, INF, 6, 5, INF, INF },
			{ 1, 6, INF, 4, 5, INF },
			{ INF, 5, 4, INF, 6, 4 },
			{ 3, INF, 5, 6, INF, 7},
			{ INF, INF, INF, 4, 7, INF}
		};
		std::vector<int> expectedPath = { 1, 5, 6, 4, 2, 3, 1 };
		int expectedMinCost = 26;
		std::ostringstream oss;
		std::streambuf* pbuf = std::cout.rdbuf();
		std::cout.rdbuf(oss.rdbuf());
		WHEN("FindMinCycle call")
		{
			FindMinCycle(matrix);
			std::cout.rdbuf(pbuf);
			std::string output = oss.str();
			THEN("Check if the path and min cost are correct")
			{
				for (int node : expectedPath)
				{
					REQUIRE(output.find(std::to_string(node)) != std::string::npos);
				}
				REQUIRE(output.find("Min cost: " + std::to_string(expectedMinCost)) != std::string::npos);
			}
		}
	}
}