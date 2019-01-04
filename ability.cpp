#include "ability.h"

/*
ABILITIES Ability::GetAbilityScores()
{
	ABILITIES t(AbilityScores.Strength.Value, AbilityScores.Dexterity.Value, AbilityScores.Constitution.Value, AbilityScores.Intelligence.Value, AbilityScores.Wisdom.Value, AbilityScores.Charisma.Value);
	if (CharacterRace)
	{
		t.Strength.Value += CharacterRace->GetAbilityScore(ABILITYSCORES::Strength);
		t.Dexterity.Value += CharacterRace->GetAbilityScore(ABILITYSCORES::Dexterity);
		t.Constitution.Value += CharacterRace->GetAbilityScore(ABILITYSCORES::Constitution);
		t.Intelligence.Value += CharacterRace->GetAbilityScore(ABILITYSCORES::Intelligence);
		t.Wisdom.Value += CharacterRace->GetAbilityScore(ABILITYSCORES::Wisdom);
		t.Charisma.Value += CharacterRace->GetAbilityScore(ABILITYSCORES::Charisma);
	}
	return t;
}*/

unsigned long Ability::GetAbilityScore(ABILITYSCORES Abi)
{
	if (Race)
	return Race->GetAbilityScore(Abi);
	return 0;
}

long Ability::GetAbilityModifier(ABILITYSCORES Abi)
{
	long score = Value;
	switch (Abi)
	{
	case ABILITYSCORES::Strength:
		score += GetAbilityScore(ABILITYSCORES::Strength);
		break;
	case ABILITYSCORES::Dexterity:
		score += GetAbilityScore(ABILITYSCORES::Dexterity);
		break;
	case ABILITYSCORES::Constitution:
		score += GetAbilityScore(ABILITYSCORES::Constitution);
		break;
	case ABILITYSCORES::Intelligence:
		score += GetAbilityScore(ABILITYSCORES::Intelligence);
		break;
	case ABILITYSCORES::Wisdom:
		score += GetAbilityScore(ABILITYSCORES::Wisdom);
		break;
	case ABILITYSCORES::Charisma:
		score += GetAbilityScore(ABILITYSCORES::Charisma);
		break;
	}

	return (score >= 10) ? (long)floor((score - 10) * 0.5) : (long)(-1 * ceil((10 - score) * 0.5));
}