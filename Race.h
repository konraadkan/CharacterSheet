#pragma once
#include <string>
#include <vector>
#include "enums_and_structs.h"
#include "wrapper.h"
#include "Subraces.h"

class Race : public Wrapper
{
protected:
	unsigned long Speed = 30;
	char* trim(char* buffer);
public:
	SizeCategory CharToSize(const char* entry)
	{
		if (!_stricmp(entry, "Diminutive"))
		{
			return SizeCategory::Diminutive;
		}
		if (!_stricmp(entry, "Fine"))
		{
			return SizeCategory::Fine;
		}
		if (!_stricmp(entry, "Tiny"))
		{
			return SizeCategory::Tiny;
		}
		if (!_stricmp(entry, "Small"))
		{
			return SizeCategory::Small;
		}
		if (!_stricmp(entry, "Medium"))
		{
			return SizeCategory::Medium;
		}
		if (!_stricmp(entry, "Large"))
		{
			return SizeCategory::Large;
		}
		if (!_stricmp(entry, "Huge"))
		{
			return SizeCategory::Huge;
		}
		if (!_stricmp(entry, "Gargantuan"))
		{
			return SizeCategory::Gargantuan;
		}
		if (!_stricmp(entry, "Colossal"))
		{
			return SizeCategory::Colossal;
		}
		return SizeCategory::SizeError;
	}
	ABILITYSCORES CharToAbi(const char* entry)
	{
		if (!_stricmp("Strength", entry) || !_stricmp("STR", entry))
		{
			return ABILITYSCORES::Strength;
		}
		if (!_stricmp("Dexterity", entry) || !_stricmp("DEX", entry))
		{
			return ABILITYSCORES::Dexterity;
		}
		if (!_stricmp("Constitution", entry) || !_stricmp("CON", entry))
		{
			return ABILITYSCORES::Constitution;
		}
		if (!_stricmp("Intelligence", entry) || !_stricmp("INT", entry))
		{
			return ABILITYSCORES::Intelligence;
		}
		if (!_stricmp("Wisdom", entry) || !_stricmp("WIS", entry))
		{
			return ABILITYSCORES::Wisdom;
		}
		if (!_stricmp("Charisma", entry) || !_stricmp("CHA", entry))
		{
			return ABILITYSCORES::Charisma;
		}
		return ABILITYSCORES::AbilityError;
	}
	Race(std::wstring name = L"") { Name = name; }
	ABILITIES AbilityScoreIncreases;
	unsigned long GetSpeed() { return Speed; }
	std::wstring m_GetClassName() { return Name; }
	std::wstring Name;
	std::wstring AgeDetails;
	std::wstring Height;
	std::wstring Languages;
	std::wstring Alignments;
	SizeCategory Size = SizeCategory::Medium;
	std::vector<Trait> Traits;
	std::vector<Vision> Perceptions;
	std::vector<Subrace> Subraces;
	Subrace* SelectedSubRace = NULL;
	void FillTraits(const wchar_t* Path);
	void FillTraits(const char* Buffer, size_t buffersize);
	bool FillTrait(const char* Buffer);
	void SetSpeed(unsigned long speed) { Speed = speed; }
	void SetSubRace(std::wstring name);
	unsigned long GetAbilityScore(const char* abi);
	unsigned long GetAbilityScore(ABILITYSCORES abi) override;
	void Interact() override { }
	std::wstring GetOutput() override { return m_GetClassName(); }
	long GetAbilityModifier(ABILITYSCORES Abi) override { return 0; }
};