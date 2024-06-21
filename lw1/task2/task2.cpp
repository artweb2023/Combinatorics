#include "SkillsUtils.h"


int main(int argc, char* argv[])
{
	auto args = ParseArgc(argc, argv);
	if (!args)
	{
		return 1;
	}
	SkillSet skills;
	if (!ReadSkillsFromFile(args->inputFileName1, skills, Type::PeopleSkills)
		|| !ReadSkillsFromFile(args->inputFileName2, skills, Type::Skills))
	{
		return 1;
	}
	PrintResult(FindMinSubgroup(skills));
	return 0;
}