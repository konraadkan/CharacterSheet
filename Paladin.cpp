#include "Paladin.h"

Paladin::Paladin(ABILITIES& abs, unsigned long startingLevel) : JobClass(startingLevel)
{
	ClassID = CLASS::Paladin; 
	ClassName = L"Paladin";
	MulticlassPrerequisite.Strength.Value = 13;
	MulticlassPrerequisite.Charisma.Value = 13;
	MulticlassPrerequisite.PrerequisiteAnd = true; 
	SetHitDice(10);
	PrimaryAbility = ABILITYSCORES::Strength;
	SecondaryAbility = ABILITYSCORES::Charisma;
	DumpAbility = ABILITYSCORES::Intelligence;
	SetAbilityPointers(abs);
}