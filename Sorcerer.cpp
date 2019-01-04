#include "Sorcerer.h"

Sorcerer::Sorcerer(ABILITIES& abs, unsigned long startingLevel) : JobClass(startingLevel)
{
	ClassID = CLASS::Sorcerer; 
	ClassName = L"Sorcerer";
	MulticlassPrerequisite.Charisma.Value = 13;
	SetHitDice(6);
	PrimaryAbility = ABILITYSCORES::Charisma;
	SecondaryAbility = ABILITYSCORES::Constitution;
	DumpAbility = ABILITYSCORES::Strength;
	SetAbilityPointers(abs);
}