#pragma once
#include "ability.h"

enum class CLASS
{
	Barbarian,
	Bard,
	Cleric,
	Druid,
	Fighter,
	Monk,
	Paladin,
	Ranger,
	Rogue,
	Sorcerer,
	Warlock,
	Wizard,
	Other,
	All,
	Error
};

/*
enum class ABILITYSCORES
{
	Strength,
	Dexterity,
	Constitution,
	Intelligence,
	Wisdom,
	Charisma,
	AbilityError
};*/

enum class SkillID
{
	Athletics,
	Acrobatics,
	SleightOfHand,
	Stealth,
	Arcana,
	History,
	Investigation,
	Nature,
	Religion,
	AnimalHandling,
	Insight,
	Medicine,
	Perception,
	Survival,
	Deception,
	Initimidation,
	Performance,
	Persuasion,
	Undefined
};

enum class SizeCategory
{
	Fine,
	Diminutive,
	Tiny,
	Small,
	Medium,
	Large,
	Huge,
	Gargantuan,
	Colossal,
	SizeError
};

enum class VisionType
{
	Normal,
	Darkvision,
	Blindsight,
	Truesight,
	Tremorsense
};

struct Vision
{
	VisionType Types;
	unsigned long Distance;
	Vision(VisionType type = VisionType::Normal, unsigned long dist = 0)
	{
		Types = type;
		Distance = dist;
	}
};

struct Trait
{
	std::wstring Name;
	std::wstring Description;
	std::wstring Race;
};