#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include "Level.h"
#include "enums_and_structs.h"
#include "Features.h"
#include "wrapper.h"
#include "Abilities.h"

class JobClass : public Wrapper
{
protected:
	CLASS ClassID = CLASS::Other;
	unsigned long Level = 1;
	unsigned long HitDice = 1;
	std::wstring ClassName;
	ABILITYSCORES PrimaryAbility;
	ABILITYSCORES SecondaryAbility;
	ABILITYSCORES DumpAbility;
	char* trim(char* buffer);
public:
	unsigned long* p_PrimaryAbility = NULL;
	unsigned long* p_SecondaryAbility = NULL;
	unsigned long* p_DumpAbility = NULL;
	ABILITIES MulticlassPrerequisite = {};
	std::vector<Feature> Features;
public:
	JobClass(unsigned long startingLevel = 0) { Level = startingLevel; }
	~JobClass() { p_PrimaryAbility = NULL; p_SecondaryAbility = NULL; p_DumpAbility = NULL; }
	CLASS GetClassID() { return ClassID; }
	std::wstring m_GetClassName() { return ClassName; }
	CLASS stringToClassID(const char* buffer);
	unsigned long GetLevel() { return Level; }
	unsigned long GetHitDice() { return HitDice; }
	unsigned long RollHitDice();
	void SetHitDice(unsigned long hd) { HitDice = hd; }
	void SetAbilityPointers(ABILITIES& abscores);
	void UpdateAbilityScores(ABILITIES& abscores);
	void FillFeatures(const wchar_t* Path);
	void FillFeature(const char* Buffer);
	void Interact() override { bSelected = true; }
	std::wstring GetOutput() override { return std::to_wstring(GetLevel()) + L" " + m_GetClassName(); }
	unsigned long GetAbilityScore(ABILITYSCORES Abi) override { return 0; }
	long GetAbilityModifier(ABILITYSCORES Abi) override { return 0; }
public:
	virtual void IncreaseLevel(unsigned long numberLevels = 1) = 0;
	virtual void DecreaseLevel(unsigned long numberLevels = 1) = 0;

	//ShowStuff() function is used for verifying data.
	void ShowStuff();
};

class ErrorClass : public JobClass
{
public:
	ErrorClass(unsigned long startingLevel = 1) : JobClass(startingLevel) { ClassName = L"ErrorClassID"; ClassID = CLASS::Error; }
	~ErrorClass() {}
	void IncreaseLevel(unsigned long numberLevels = 1) override { Level += numberLevels; }
	void DecreaseLevel(unsigned long numberLevels = 1) override { Level -= numberLevels; }	
};