#include "Bard.h"

Bard::Bard(ABILITIES& abs, unsigned long StartingLevel) : JobClass(StartingLevel)
{
	ClassID = CLASS::Bard; 
	ClassName = L"Bard"; 
	MulticlassPrerequisite.Charisma.Value = 13;
	SetHitDice(8);
	PrimaryAbility = ABILITYSCORES::Charisma;
	SecondaryAbility = ABILITYSCORES::Dexterity;
	DumpAbility = ABILITYSCORES::Wisdom;
	SetAbilityPointers(abs);
}