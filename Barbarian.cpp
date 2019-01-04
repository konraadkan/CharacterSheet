#include "Barbarian.h"

Barbarian::Barbarian(ABILITIES& abs, unsigned long StartingLevel) : JobClass(StartingLevel)
{
	ClassID = CLASS::Barbarian; 
	ClassName = L"Barbarian"; 
	MulticlassPrerequisite.Strength.Value = 13;
	SetHitDice(12);
	PrimaryAbility = ABILITYSCORES::Strength;
	SecondaryAbility = ABILITYSCORES::Constitution;
	DumpAbility = ABILITYSCORES::Charisma;
	SetAbilityPointers(abs);
	FillFeatures(L"barbarian_feature_test.txt");
}