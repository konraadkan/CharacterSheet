#include "RerollInteraction.h"
#include <random>
#include <numeric>

void RerollInteraction::Interact()
{
	GenerateAbilities();
}

std::wstring RerollInteraction::GetOutput()
{
	return L"Reroll";
}

long RerollInteraction::GetAbilityModifier(ABILITYSCORES Abi)
{
	//should not be called
	return 0;
}

unsigned long RerollInteraction::GetAbilityScore(ABILITYSCORES Abi)
{
	//should not be called
	return 0;
}

void RerollInteraction::GenerateAbilities()
{
	if (!AbiPtr) return;

	std::random_device rd;
	std::mt19937_64 mt(rd());
	std::uniform_int_distribution<long> dist(1, 6);

	std::vector<long> rolls;
	std::vector<long> abilityscores;
	for (long i = 0; i < 6; i++)
	{
		if (rolls.size()) rolls.clear();
		for (long j = 0; j < 4; j++)
		{
			rolls.push_back(dist(mt));
		}
		std::sort(rolls.begin(), rolls.end(), Descending());
		rolls.pop_back();
		abilityscores.push_back(std::accumulate(rolls.begin(), rolls.end(), 0));	//the 0 specifies integers, 0.0f would be floats
	}
	if (rolls.size()) rolls.clear();

	AbiPtr->Strength.Value = abilityscores[0];
	AbiPtr->Dexterity.Value = abilityscores[1];
	AbiPtr->Constitution.Value = abilityscores[2];
	AbiPtr->Intelligence.Value = abilityscores[3];
	AbiPtr->Wisdom.Value = abilityscores[4];
	AbiPtr->Charisma.Value = abilityscores[5];

	abilityscores.clear();
	ScoresGenerated = true;
}