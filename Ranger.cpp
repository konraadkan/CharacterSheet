#include "Ranger.h"

Ranger::Ranger(ABILITIES& abs, unsigned long startingLevel) : JobClass(startingLevel)
{
	ClassID = CLASS::Ranger;
	ClassName = L"Ranger"; 
	MulticlassPrerequisite.Dexterity.Value = 13;
	MulticlassPrerequisite.Wisdom.Value = 13;
	MulticlassPrerequisite.PrerequisiteAnd = true; 
	SetHitDice(10);
	PrimaryAbility = ABILITYSCORES::Dexterity;
	SecondaryAbility = ABILITYSCORES::Wisdom;
	DumpAbility = ABILITYSCORES::Intelligence;
	SetAbilityPointers(abs);
}