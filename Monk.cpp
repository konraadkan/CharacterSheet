#include "Monk.h"

Monk::Monk(ABILITIES& abs, unsigned long startingLevel) : JobClass(startingLevel)
{
	ClassID = CLASS::Monk;
	ClassName = L"Monk";
	MulticlassPrerequisite.Strength.Value = 13;
	MulticlassPrerequisite.Dexterity.Value = 13;
	MulticlassPrerequisite.PrerequisiteAnd = true; 
	SetHitDice(8);
	PrimaryAbility = ABILITYSCORES::Dexterity;
	SecondaryAbility = ABILITYSCORES::Wisdom;
	DumpAbility = ABILITYSCORES::Intelligence;
	SetAbilityPointers(abs);
}