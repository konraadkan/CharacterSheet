#include "Warlock.h"

Warlock::Warlock(ABILITIES& abs, unsigned long startingLevel) : JobClass(startingLevel)
{
	ClassID = CLASS::Warlock;
	ClassName = L"Warlock";
	MulticlassPrerequisite.Charisma.Value = 13;
	SetHitDice(8);
	PrimaryAbility = ABILITYSCORES::Charisma;
	SecondaryAbility = ABILITYSCORES::Constitution;
	DumpAbility = ABILITYSCORES::Strength;
	SetAbilityPointers(abs);
}