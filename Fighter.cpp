#include "Fighter.h"

Fighter::Fighter(ABILITIES& abs, unsigned long startingLevel) : JobClass(startingLevel)
{
	ClassID = CLASS::Fighter; ClassName = L"Fighter";
	MulticlassPrerequisite.Strength.Value = 13;
	MulticlassPrerequisite.Dexterity.Value = 13;
	SetHitDice(10);
	PrimaryAbility = ABILITYSCORES::Strength;
	SecondaryAbility = ABILITYSCORES::Dexterity;
	DumpAbility = ABILITYSCORES::Wisdom;
	SetAbilityPointers(abs);
}