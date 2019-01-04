#include "Rogue.h"

Rogue::Rogue(ABILITIES& abs, unsigned long startingLevel) : JobClass(startingLevel)
{
	ClassID = CLASS::Rogue; 
	ClassName = L"Rogue"; 
	MulticlassPrerequisite.Dexterity.Value = 13;
	SetHitDice(8);
	PrimaryAbility = ABILITYSCORES::Dexterity;
	SecondaryAbility = ABILITYSCORES::Intelligence;
	DumpAbility = ABILITYSCORES::Wisdom;
	SetAbilityPointers(abs);
}