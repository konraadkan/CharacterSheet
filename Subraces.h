#pragma once
#include <vector>
#include <string>
#include "enums_and_structs.h"
#include "wrapper.h"
#include "Abilities.h"

class Subrace : public Wrapper
{
protected:
	char* trim(char* buffer);
public:
	std::wstring Name;
	std::wstring Description;
	std::wstring BaseRace;
	ABILITIES AbilityScoreIncreases;
	std::vector<Trait> Traits;
	std::vector<Vision> Perceptions;
	std::wstring m_GetClassName() { return Name; }
public:
	Subrace(std::wstring name = L"", std::wstring race = L"");	
	~Subrace() {}
	bool FillTrait(const char* Buffer);
	void Interact() override {}
	std::wstring GetOutput() override { return m_GetClassName(); }
	unsigned long GetAbilityScore(ABILITYSCORES Abi) override { return 0; }
	long GetAbilityModifier(ABILITYSCORES Abi) override { return 0; }
};