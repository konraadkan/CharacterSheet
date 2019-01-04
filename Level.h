#pragma once

class CLevel
{
public:
	unsigned long MinimumExperience = 0;
	unsigned long NextTier = 0;
	unsigned long ProficiencyBonus = 2;
	CLevel(unsigned long level = 1)
	{
		switch (level)
		{
		case 1:
			MinimumExperience = 0;
			NextTier = 300;
			ProficiencyBonus = 2;
			break;
		case 2:
			MinimumExperience = 300;
			NextTier = 900;
			ProficiencyBonus = 2;
			break;
		case 3:
			MinimumExperience = 900;
			NextTier = 2700;
			ProficiencyBonus = 2;
			break;
		case 4:
			MinimumExperience = 2700;
			NextTier = 6500;
			ProficiencyBonus = 2;
			break;
		case 5:
			MinimumExperience = 6500;
			NextTier = 14000;
			ProficiencyBonus = 3;
			break;
		case 6:
			MinimumExperience = 14000;
			NextTier = 23000;
			ProficiencyBonus = 3;
			break;
		case 7:
			MinimumExperience = 23000;
			NextTier = 34000;
			ProficiencyBonus = 3;
			break;
		case 8:
			MinimumExperience = 34000;
			NextTier = 48000;
			ProficiencyBonus = 3;
			break;
		case 9:
			MinimumExperience = 48000;
			NextTier = 64000;
			ProficiencyBonus = 4;
			break;
		case 10:
			MinimumExperience = 64000;
			NextTier = 85000;
			ProficiencyBonus = 4;
			break;
		case 11:
			MinimumExperience = 85000;
			NextTier = 100000;
			ProficiencyBonus = 4;
			break;
		case 12:
			MinimumExperience = 100000;
			NextTier = 120000;
			ProficiencyBonus = 5;
			break;
		case 13:
			MinimumExperience = 120000;
			NextTier = 140000;
			ProficiencyBonus = 5;
			break;
		case 14:
			MinimumExperience = 140000;
			NextTier = 165000;
			ProficiencyBonus = 5;
			break;
		case 15:
			MinimumExperience = 165000;
			NextTier = 195000;
			ProficiencyBonus = 5;
			break;
		case 16:
			MinimumExperience = 195000;
			NextTier = 225000;
			ProficiencyBonus = 5;
			break;
		case 17:
			MinimumExperience = 225000;
			NextTier = 265000;
			ProficiencyBonus = 6;
			break;
		case 18:
			MinimumExperience = 265000;
			NextTier = 305000;
			ProficiencyBonus = 6;
			break;
		case 19:
			MinimumExperience = 305000;
			NextTier = 355000;
			ProficiencyBonus = 6;
			break;
		case 20:
			MinimumExperience = 355000;
			NextTier = -1;
			ProficiencyBonus = 6;
			break;
		}
	}
	~CLevel() {}
};