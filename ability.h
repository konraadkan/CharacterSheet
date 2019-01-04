#pragma once
#include <string>
#include "wrapper.h"
#include "enums_and_structs.h"

class Ability : public Wrapper
{
public:
	unsigned long Value = 0;
	ABILITYSCORES AbilityID = ABILITYSCORES::AbilityError;
public:
	void Interact() override {}
	std::wstring GetOutput() override
	{
		if (Race)
		{
			return std::to_wstring(Value + GetAbilityScore(AbilityID));
		}
		return std::to_wstring(Value);
	}
	unsigned long GetAbilityScore(ABILITYSCORES Abi) override;
	long GetAbilityModifier(ABILITYSCORES Abi) override;

	Wrapper* Race = NULL;
	Wrapper* SubRace = NULL;

	Ability(unsigned long value = 0, ABILITYSCORES id = ABILITYSCORES::AbilityError, Wrapper* wr = NULL, Wrapper* sr = NULL)
	{
		AbilityID = id;
		Value = value;
		Race = wr;
		SubRace = sr;
	}
};

class AbilityModifier : public Ability
{
public:
	unsigned long* ValuePtr = NULL;
	std::wstring GetOutput() override
	{
		if (ValuePtr) Value = *ValuePtr;
		long mod = GetAbilityModifier(AbilityID);
		return mod >= 0 ? (L"+" + std::to_wstring(mod)) : (std::to_wstring(mod));
	}
};