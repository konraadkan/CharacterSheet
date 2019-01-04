#include "Cleric.h"

Cleric::Cleric(ABILITIES& abs, unsigned long startingLevel) : JobClass(startingLevel)
{ 
	ClassID = CLASS::Cleric; ClassName = L"Cleric"; 
	MulticlassPrerequisite.Wisdom.Value = 13; 
	SetHitDice(8);
	PrimaryAbility = ABILITYSCORES::Wisdom;
	SecondaryAbility = ABILITYSCORES::Constitution;
	DumpAbility = ABILITYSCORES::Dexterity;
	SetAbilityPointers(abs);
}