#pragma once
#include <vector>
#include <string>
#include "JobClass.h"
#include "classlist.h"
#include "skills.h"
#include "Race.h"

class Character
{
protected:
	unsigned long Exp = 0;
	unsigned long MaximumHP = 0;
	long CurrentHP = 0;	
	char* trim(const char* buffer);
public:
	std::vector<Skill> Skills;
	std::vector<JobClass*> Classes;
	ABILITIES AbilityScores;
	long GetCurrentHP() { return CurrentHP; }
	unsigned long GetMaximumHP() { return MaximumHP; }
	long GetProficiencyModifier();
	unsigned long GetSpeed();
public:
	unsigned long GetExp() { return Exp; }
	unsigned long GetLevels();
	unsigned long GetLevel(CLASS jobclass);
	void IncreaseLevel(CLASS jobclass, unsigned long Amount = 1);
	Race* CharacterRace = NULL;
	std::vector<Race*> Races;
	std::vector<Subrace*> Subraces;
	std::wstring Name;
	Character();
	~Character();
public:
	void IncreaseExperience(unsigned long Amount = 0) { Exp += Amount; }
	void DecreaseExperience(unsigned long Amount = 0) { Exp = (Exp - Amount) < 0 ? 0 : Exp - Amount; }
	void GenerateAbilityScores(CLASS primaryclass = CLASS::Other);
	bool BuildRaces(const wchar_t* Path);
	bool BuildRaces(const char* Buffer, size_t BufferLen);
	bool FillSubrace(const char* Buffer);
	void FillRace(const char* Buffer);
	long GetAbilityModifier(ABILITYSCORES Abi);
	long GetSkillModifier(SkillID skillid);
	void SetRace(const wchar_t* TargetRaceName);
	void SetSubrace(const wchar_t* TargetSubrace);
	ABILITIES GetAbilityScores();
	std::wstring GetAbilityScoreW(ABILITYSCORES Abi);
	std::wstring GetAbilityModifierW(ABILITYSCORES Abi);
	std::wstring GetSpeedW();
};