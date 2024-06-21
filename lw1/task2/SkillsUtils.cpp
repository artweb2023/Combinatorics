#include "SkillsUtils.h"

std::optional<Args> ParseArgc(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: task2.exe <input People skills> <skills>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName1 = argv[1];
	args.inputFileName2 = argv[2];
	return args;
}

bool ReadFileStream(std::ifstream& input, SkillSet& skills, Type type)
{
	std::string line;
	while (std::getline(input, line))
	{
		if (type == Type::PeopleSkills)
		{
			std::set<int> row;
			int value;
			std::istringstream iss(line);
			while (iss >> value)
			{
				row.insert(value);
			}
			skills.peopleSkills.push_back(row);
		}
		else if (type == Type::Skills)
		{
			int value;
			std::istringstream iss(line);
			while (iss >> value)
			{
				skills.skills.insert(value);
			}
		}
	}
	return input.eof();
}

bool ReadSkillsFromFile(const std::string& fileName, SkillSet& skills, Type type)
{
	std::ifstream input;
	input.open(fileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" + fileName + "' file" << std::endl;
		return false;
	}
	if (!ReadFileStream(input, skills, type))
	{
		std::cout << "Failed to read from '" + fileName + "' file" << std::endl;
		return false;
	}
	return true;

}

bool containsAllSkills(const std::set<int>& personSkills, const Skills& requiredSkills)
{
	return includes(personSkills.begin(), personSkills.end(), requiredSkills.begin(), requiredSkills.end());
}

int FindMinSubgroup(SkillSet& skills)
{
	if (skills.skills.empty() || skills.peopleSkills.empty())
	{
		return 0;
	}
	int len = static_cast<int>(skills.peopleSkills.size());
	std::set<int> minGroup;
	for (int k = 1; k <= len; ++k)
	{
		std::vector<int> groupMask(k, 1);
		groupMask.resize(len, 0);
		do
		{
			std::set<int> currentGroup;
			for (int i = 0; i < len; ++i)
			{
				if (groupMask[i])
				{
					currentGroup.insert(i);
				}
			}
			std::set<int> mergedSkills;
			for (int person : currentGroup)
			{
				set_union(mergedSkills.begin(), mergedSkills.end(),
					skills.peopleSkills[person].begin(), skills.peopleSkills[person].end(),
					inserter(mergedSkills, mergedSkills.begin()));
			}
			if (containsAllSkills(mergedSkills, skills.skills))
			{
				if (minGroup.empty() || currentGroup.size() < minGroup.size()) {
					minGroup = currentGroup;
				}
			}

		} while (prev_permutation(groupMask.begin(), groupMask.end()));
	}
	return static_cast<int>(minGroup.size());
}

void PrintResult(int subgroup)
{
	std::cout << "Smallest subgroup is " << subgroup << std::endl;
}