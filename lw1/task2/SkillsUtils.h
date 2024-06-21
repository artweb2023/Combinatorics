#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using PeopleSkills = std::vector<std::set<int>>;
using Skills = std::set<int>;

enum class Type
{
	PeopleSkills,
	Skills,
};

struct SkillSet
{
	PeopleSkills peopleSkills;
	Skills skills;
};

struct Args
{
	std::string inputFileName1;
	std::string inputFileName2;
};

std::optional<Args> ParseArgc(int argc, char* argv[]);
bool ReadFileStream(std::ifstream& input, SkillSet& skills, Type type);
bool ReadSkillsFromFile(const std::string& fileName, SkillSet& skills, Type type);
bool containsAllSkills(const std::set<int>& personSkills, const Skills& requiredSkills);
int FindMinSubgroup(SkillSet& skills);
void PrintResult(int subgroup);