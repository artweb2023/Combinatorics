#define CATCH_CONFIG_MAIN

#include "/combinatorics/lw1/task2/SkillsUtils.h"
#include "/OOP/catch2/catch.hpp"

SCENARIO("Finding the smallest subgroup of people with required skills")
{
	SkillSet skills;
	GIVEN("Empty skills and empty required skills")
	{
		WHEN("FindSubgroup is called")
		{
			int result = FindMinSubgroup(skills);
			THEN("result is zerro")
			{
				REQUIRE(result == 0);
			}
		}
	}
	GIVEN("Non-empty skills and empty required skills")
	{
		skills.peopleSkills = { {1, 2, 3}, {4, 5} };
		WHEN("FindSubgroup is called")
		{
			int result = FindMinSubgroup(skills);
			THEN("result is zerro")
			{
				REQUIRE(result == 0);
			}
		}
	}
	GIVEN("Empty skills and non-empty required skills")
	{
		skills.skills = { 1, 2, 3 };
		WHEN("FindSubgroup is called")
		{
			int result = FindMinSubgroup(skills);
			THEN("result is zerro")
			{
				REQUIRE(result == 0);
			}
		}
	}
	GIVEN("Non-empty skills, non-empty required skills, no match")
	{
		skills.peopleSkills = { {1, 2}, {3, 4, 5} };
		skills.skills = { 6, 7 };
		WHEN("FindSubgroup is called")
		{
			int result = FindMinSubgroup(skills);
			THEN("result is zerro")
			{
				REQUIRE(result == 0);
			}
		}
	}
	GIVEN("Non-empty skills, non-empty required skills, one match")
	{
		skills.peopleSkills = { {1, 2, 3}, {4, 5} };
		skills.skills = { 4, 5 };
		WHEN("FindSubgroup is called")
		{
			int result = FindMinSubgroup(skills);
			THEN("result is 1")
			{
				REQUIRE(result == 1);
			}
		}
	}
	GIVEN("Non-empty skills, non-empty required skills, one match")
	{
		skills.peopleSkills = { {1, 2, 3}, {4, 5} };
		skills.skills = { 1, 2, 4 };
		WHEN("FindSubgroup is called")
		{
			int result = FindMinSubgroup(skills);
			THEN("result is 2")
			{
				REQUIRE(result == 2);
			}
		}
	}
	GIVEN("Non-empty skills, non-empty required skills, multiple matches")
	{
		skills.peopleSkills = { {1, 2, 3}, {2, 3, 4}, {1, 4} , {5} };
		skills.skills = { 1, 2, 3, 4, 5 };
		WHEN("FindSubgroup is called")
		{
			int result = FindMinSubgroup(skills);
			THEN("result is 3")
			{
				REQUIRE(result == 3);
			}
		}
	}
	GIVEN("Multiple people with same skills")
	{
		skills.peopleSkills = { {1, 2, 3}, {1, 2, 3} };
		skills.skills = { 1, 2, 3 };
		WHEN("FindSubgroup is called")
		{
			int result = FindMinSubgroup(skills);
			THEN("Result is 1")
			{
				REQUIRE(result == 1);
			}
		}
	}
	GIVEN("people with same skills")
	{
		skills.peopleSkills = { {1, 2, 3, 4, 5, 6}, {7} , {8}, {9}, {10}, {1, 2, 3, 6, 7} , {4, 5, 8, 9, 10} };
		skills.skills = { 1, 2, 3, 4, 5, 6, 7, 8 , 9, 10 };
		WHEN("FindSubgroup is called")
		{
			int result = FindMinSubgroup(skills);
			THEN("Result is 2")
			{
				REQUIRE(result == 2);
			}
		}
	}
}