#pragma once
#include <cmath>
#include <string>
#include "enums_and_structs.h"

struct Skill
{
	std::wstring Name = L"Unnamed";
	bool Expertise = false;
	bool Proficient = false;
	ABILITYSCORES Ability = ABILITYSCORES::Strength;
	SkillID ID = SkillID::Undefined;
	Skill(SkillID skillid, ABILITYSCORES abscores, const wchar_t* name, bool prof = false, bool exp = false)
	{
		ID = skillid;
		Name.clear();
		Name = name;
		Ability = abscores;
		Expertise = exp;
		Proficient = prof;
	}
};