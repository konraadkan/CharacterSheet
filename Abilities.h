#pragma once
#include "ability.h"

struct ABILITIES
{
	/*unsigned long Strength = 10;
	unsigned long Dexterity = 10;
	unsigned long Constitution = 10;
	unsigned long Intelligence = 10;
	unsigned long Wisdom = 10;
	unsigned long Charisma = 10;*/
	Ability Strength;
	AbilityModifier StrMod;
	Ability Dexterity;
	AbilityModifier DexMod;
	Ability Constitution;
	AbilityModifier ConMod;
	Ability Intelligence;
	AbilityModifier IntMod;
	Ability Wisdom;
	AbilityModifier WisMod;
	Ability Charisma; 
	AbilityModifier ChaMod;

	bool PrerequisiteAnd = false;
	ABILITIES(unsigned long str = 10, unsigned long dex = 10, unsigned long con = 10, unsigned long inte = 10, unsigned long wis = 10, unsigned long cha = 10)
	{
		/*	Strength = new Ability(str, ABILITYSCORES::Strength);
		Dexterity = new Ability(dex, ABILITYSCORES::Dexterity);
		Constitution = new Ability(con, ABILITYSCORES::Constitution);
		Intelligence = new Ability(inte, ABILITYSCORES::Intelligence);
		Wisdom = new Ability(wis, ABILITYSCORES::Wisdom);
		Charisma = new Ability(cha, ABILITYSCORES::Charisma);*/
		Strength.Value = str;
		StrMod.ValuePtr = &Strength.Value;
		StrMod.AbilityID = Strength.AbilityID = ABILITYSCORES::Strength;
		Dexterity.Value = dex;
		DexMod.ValuePtr = &Dexterity.Value;
		DexMod.AbilityID = Dexterity.AbilityID = ABILITYSCORES::Dexterity;
		Constitution.Value = con;
		ConMod.ValuePtr = &Constitution.Value;
		ConMod.AbilityID = Constitution.AbilityID = ABILITYSCORES::Constitution;
		Intelligence.Value = inte;
		IntMod.ValuePtr = &Intelligence.Value;
		IntMod.AbilityID = Intelligence.AbilityID = ABILITYSCORES::Intelligence;
		Wisdom.Value = wis;
		WisMod.ValuePtr = &Wisdom.Value;
		WisMod.AbilityID = Wisdom.AbilityID = ABILITYSCORES::Wisdom;
		Charisma.Value = cha;
		ChaMod.ValuePtr = &Charisma.Value;
		ChaMod.AbilityID = Charisma.AbilityID = ABILITYSCORES::Charisma;
	}
	~ABILITIES()
	{

	}
	void SetRace(Wrapper* w)
	{
		Strength.Race = w;
		StrMod.Race = w;
		Dexterity.Race = w;
		DexMod.Race = w;
		Constitution.Race = w;
		ConMod.Race = w;
		Intelligence.Race = w;
		IntMod.Race = w;
		Wisdom.Race = w;
		WisMod.Race = w;
		Charisma.Race = w;
		ChaMod.Race = w;
	}
	void SetSubRace(Wrapper* w)
	{
		Strength.SubRace = w;
		StrMod.SubRace = w;
		Dexterity.SubRace = w;
		DexMod.SubRace = w;
		Constitution.SubRace = w;
		ConMod.SubRace = w;
		Intelligence.SubRace = w;
		IntMod.SubRace = w;
		Wisdom.SubRace = w;
		WisMod.SubRace = w;
		Charisma.SubRace = w;
		ChaMod.SubRace = w;
	}
};