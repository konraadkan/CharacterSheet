#pragma once
#include <string>

enum class ABILITYSCORES
{
	Strength,
	Dexterity,
	Constitution,
	Intelligence,
	Wisdom,
	Charisma,
	AbilityError
};

class Wrapper
{
public:
	virtual void Interact() = 0;
	virtual std::wstring GetOutput() = 0;
	virtual long GetAbilityModifier(ABILITYSCORES Abi) = 0;
	virtual unsigned long GetAbilityScore(ABILITYSCORES Abi) = 0;
};