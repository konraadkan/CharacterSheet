#include "Wizard.h"

Wizard::Wizard(ABILITIES& abs, unsigned long startingLevel) : JobClass(startingLevel)
{
	ClassID = CLASS::Wizard; 
	ClassName = L"Wizard"; 
	MulticlassPrerequisite.Intelligence.Value = 13;
	SetHitDice(6);
	PrimaryAbility = ABILITYSCORES::Intelligence;
	SecondaryAbility = ABILITYSCORES::Constitution;
	DumpAbility = ABILITYSCORES::Strength;
	SetAbilityPointers(abs);
}