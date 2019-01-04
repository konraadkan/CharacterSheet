#include "Druid.h"

Druid::Druid(ABILITIES& abs, unsigned long startingLevel) : JobClass(startingLevel)
{ 
	ClassID = CLASS::Druid; 
	ClassName = L"Druid"; 
	MulticlassPrerequisite.Wisdom.Value = 13;
	SetHitDice(8);
	PrimaryAbility = ABILITYSCORES::Wisdom;
	SecondaryAbility = ABILITYSCORES::Dexterity;
	DumpAbility = ABILITYSCORES::Intelligence;
	SetAbilityPointers(abs);
}