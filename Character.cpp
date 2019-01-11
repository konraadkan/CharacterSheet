#include "Character.h"
#include <random>
#include <numeric>

Character::Character()
{
	Skills.push_back(Skill(SkillID::Athletics, ABILITYSCORES::Strength, L"Athletics"));
	Skills.push_back(Skill(SkillID::Acrobatics, ABILITYSCORES::Dexterity, L"Acrobatics"));
	Skills.push_back(Skill(SkillID::SleightOfHand, ABILITYSCORES::Dexterity, L"Sleight of Hand"));
	Skills.push_back(Skill(SkillID::Stealth, ABILITYSCORES::Dexterity, L"Stealth"));
	Skills.push_back(Skill(SkillID::Arcana, ABILITYSCORES::Intelligence, L"Arcana"));
	Skills.push_back(Skill(SkillID::History, ABILITYSCORES::Intelligence, L"History"));
	Skills.push_back(Skill(SkillID::Investigation, ABILITYSCORES::Intelligence, L"Investigation"));
	Skills.push_back(Skill(SkillID::Nature, ABILITYSCORES::Intelligence, L"Nature"));
	Skills.push_back(Skill(SkillID::Religion, ABILITYSCORES::Intelligence, L"Religion"));
	Skills.push_back(Skill(SkillID::AnimalHandling, ABILITYSCORES::Wisdom, L"Animal Handling"));
	Skills.push_back(Skill(SkillID::Insight, ABILITYSCORES::Wisdom, L"Insight"));
	Skills.push_back(Skill(SkillID::Medicine, ABILITYSCORES::Wisdom, L"Medicine"));
	Skills.push_back(Skill(SkillID::Perception, ABILITYSCORES::Wisdom, L"Perception"));
	Skills.push_back(Skill(SkillID::Survival, ABILITYSCORES::Wisdom, L"Survival"));
	Skills.push_back(Skill(SkillID::Deception, ABILITYSCORES::Charisma, L"Deception"));
	Skills.push_back(Skill(SkillID::Initimidation, ABILITYSCORES::Charisma, L"Intimidation"));
	Skills.push_back(Skill(SkillID::Performance, ABILITYSCORES::Charisma, L"Performance"));
	Skills.push_back(Skill(SkillID::Persuasion, ABILITYSCORES::Charisma, L"Persuasion"));

	BuildRaces(L"Barbarian_Trait_test.txt");
}

Character::~Character()
{
	if (Skills.size()) Skills.clear();
	while (Classes.size())
	{
		if (Classes.back()) delete Classes.back();
		Classes.pop_back();
	}
	while (Races.size())
	{
		if (Races.back()) delete Races.back();
		Races.pop_back();
	}
	while (Subraces.size())
	{
		if (Subraces.back()) delete Subraces.back();
		Subraces.pop_back();
	}
}

bool Character::BuildRaces(const wchar_t* path)
{
	FILE* file = NULL;
	errno_t err = _wfopen_s(&file, path, L"rb");
	if (err) return false;

	fseek(file, 0, SEEK_END);
	size_t BufferLen = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* Buffer = new char[BufferLen];
	fread(Buffer, BufferLen, 1, file);
	fclose(file);

	BuildRaces(Buffer, BufferLen);
	
	delete[] Buffer;
	return true;
}

void Character::SetRace(const wchar_t* TargetRaceName)
{
	for (auto& r : Races)
	{
		if (!_wcsicmp(TargetRaceName, r->Name.c_str()))
		{
			CharacterRace = r;
			break;
		}
	}
}

void Character::SetSubrace(const wchar_t* TargetSubrace)
{
	if (!CharacterRace) return;
	for (auto& sr : Subraces)
	{
		if (!_wcsicmp(TargetSubrace, sr->Name.c_str()))
		{
			CharacterRace->SelectedSubRace = sr;
			break;
		}
	}
}

bool Character::BuildRaces(const char* Buffer, size_t BufferLen)
{
	if (!Buffer) return false;

	const char* ptr = strchr(Buffer, ';');
	const char* optr = Buffer;
	while (ptr)
	{
		char* t = new char[ptr - optr + 1];
		t[ptr - optr] = '\0';
		memcpy(t, optr, ptr - optr);
		t = trim(t);
		FillRace(t);
		delete[] t;

		optr = ptr + 1;
		ptr = strchr(optr, ';');
	}

	return true;
}

void Character::FillRace(const char* buffer)
{
	const char* ptr = strchr(buffer, '=');
	if (ptr)
	{
		char* temp = new char[ptr - buffer + 1];
		temp[ptr - buffer] = '\0';
		memcpy(temp, buffer, ptr - buffer);
		temp = trim(temp);

		char* entry = new char[(buffer + strlen(buffer) - ptr)];
		entry[(buffer + strlen(buffer) - ptr) - 1] = '\0';
		memcpy(entry, ptr + 1, (buffer + strlen(buffer) - ptr) - 1);
		entry = trim(entry);

		if (!_stricmp(temp, "RaceName"))
		{
			Races.push_back(new Race(std::wstring(entry, entry + strlen(entry))));
		}
		else
		{
			if (Races.size())
			{
				if (!_stricmp(temp, "RaceAgeDetails"))
				{
					Races.back()->AgeDetails = std::wstring(entry, entry + strlen(entry));
				}
				else if (!_stricmp(temp, "RaceHeight"))
				{
					Races.back()->Height = std::wstring(entry, entry + strlen(entry));
				}
				else if (!_stricmp(temp, "RaceLanguages"))
				{
					Races.back()->Languages = std::wstring(entry, entry + strlen(entry));
					//add a vector for languages
				}
				else if (!_stricmp(temp, "RaceSizeCategory"))
				{
					Races.back()->Size = Races.back()->CharToSize(entry);
				}
				else if (!_stricmp(temp, "RaceSpeed"))
				{
					Races.back()->SetSpeed(atoi(entry));
				}
				else if (!_stricmp(temp, "RaceAlignments"))
				{
					Races.back()->Alignments = std::wstring(entry, entry + strlen(entry));
				}
				else if (!_stricmp(temp, "RaceAbilityScores"))
				{
					size_t counter = 0;
					unsigned long* abinum = &Races.back()->AbilityScoreIncreases.Strength.Value;
					const char* tp = strchr(entry, ',');
					if (!tp) tp = strchr(entry, '\0');
					const char* otp = entry;
					while (tp)
					{
						char* tempnum = new char[tp - otp + 1];
						tempnum[tp - otp] = '\0';
						memcpy(tempnum, otp, tp - otp);
						*abinum = atoi(tempnum);
						delete[] tempnum;
						switch (counter)
						{
						case 0:
							abinum = &Races.back()->AbilityScoreIncreases.Dexterity.Value;
							break;
						case 1:
							abinum = &Races.back()->AbilityScoreIncreases.Constitution.Value;
							break;
						case 2:
							abinum = &Races.back()->AbilityScoreIncreases.Intelligence.Value;
							break;
						case 3:
							abinum = &Races.back()->AbilityScoreIncreases.Wisdom.Value;
							break;
						case 4:
							abinum = &Races.back()->AbilityScoreIncreases.Charisma.Value;
							break;
						}
						counter++;

						otp = tp + 1;
						tp = strchr(otp, ',');
						if (!tp)
						{
							const char* end = strchr(otp, '\0');
							char* tempnum = new char[end - otp + 1];
							tempnum[end - otp + 1];
							tempnum[end - otp] = '\0';
							memcpy(tempnum, otp, end - otp);
							*abinum = atoi(tempnum);
							delete[] tempnum;
						}
					}
				}
				else
				{
					if (!Races.back()->FillTrait(buffer))
					{
						FillSubrace(buffer);
					}
				}
			}
		}
	}
}

bool Character::FillSubrace(const char* buffer)
{
	bool foundit = false;
	const char* ptr = strchr(buffer, '=');
	if (ptr)
	{
		char* temp = new char[ptr - buffer + 1];
		temp[ptr - buffer] = '\0';
		memcpy(temp, buffer, ptr - buffer);
		temp = trim(temp);

		char* entry = new char[(buffer + strlen(buffer) - ptr)];
		entry[(buffer + strlen(buffer) - ptr) - 1] = '\0';
		memcpy(entry, ptr + 1, (buffer + strlen(buffer) - ptr) - 1);
		entry = trim(entry);

		if (!_stricmp(temp, "SubraceName"))
		{
			Subraces.push_back(new Subrace(std::wstring(entry, entry + strlen(entry))));
			foundit = true;
		}
		else
		{
			if (Subraces.size())
			{
				if (!_stricmp(temp, "SubraceAbilities"))
				{
					size_t counter = 0;
					unsigned long* abinum = &Subraces.back()->AbilityScoreIncreases.Strength.Value;
					const char* tp = strchr(entry, ',');
					if (!tp) tp = strchr(entry, '\0');
					const char* otp = entry;
					while (tp)
					{
						char* tempnum = new char[tp - otp + 1];
						tempnum[tp - otp] = '\0';
						memcpy(tempnum, otp, tp - otp);
						*abinum = atoi(tempnum);
						delete[] tempnum;
						switch (counter)
						{
						case 0:
							abinum = &Subraces.back()->AbilityScoreIncreases.Dexterity.Value;
							break;
						case 1:
							abinum = &Subraces.back()->AbilityScoreIncreases.Constitution.Value;
							break;
						case 2:
							abinum = &Subraces.back()->AbilityScoreIncreases.Intelligence.Value;
							break;
						case 3:
							abinum = &Subraces.back()->AbilityScoreIncreases.Wisdom.Value;
							break;
						case 4:
							abinum = &Subraces.back()->AbilityScoreIncreases.Charisma.Value;
							break;
						}
						counter++;

						otp = tp + 1;
						tp = strchr(otp, ',');
						if (!tp)
						{
							const char* end = strchr(otp, '\0');
							char* tempnum = new char[end - otp + 1];
							tempnum[end - otp + 1];
							tempnum[end - otp] = '\0';
							memcpy(tempnum, otp, end - otp);
							*abinum = atoi(tempnum);
							delete[] tempnum;
						}
					}
					foundit = true;
				}
				else if (!_stricmp(temp, "SubraceDescription"))
				{
					Subraces.back()->Description = std::wstring(entry, entry + strlen(entry));
				}
				else if (!_stricmp(temp, "SubraceBaseRace"))
				{
					Subraces.back()->BaseRace = std::wstring(entry, entry + strlen(entry));
				}
				else
				{
					Subraces.back()->FillTrait(buffer);
				}
			}
		}
	}
	return foundit;
}

char* Character::trim(const char* buffer)
{
	if (!buffer) return NULL;
	size_t startpoint = 0;
	size_t endpoint = strlen(buffer);
	for (size_t i = 0; i < strlen(buffer); i++)
	{
		if (buffer[i] == '\n' || buffer[i] == '\r' || buffer[i] == '\0' || buffer[i] == ' ')
		{
			startpoint = i + 1;
		}
		else
			break;
	}
	for (size_t i = strlen(buffer); i > 0; i--)
	{
		if (buffer[i] == '\n' || buffer[i] == '\r' || buffer[i] == '\0' || buffer[i] == ' ')
		{
			endpoint = i;
		}
		else
			break;
	}
	char* newbuffer = new char[endpoint - startpoint + 1];
	newbuffer[endpoint - startpoint] = '\0';
	memcpy(newbuffer, buffer + startpoint, endpoint - startpoint);
	delete[] buffer;
	return newbuffer;
}

void Character::DecreaseLevel(CLASS jobclass, unsigned long Amount)
{
	if (Classes.empty()) return;

	for (size_t i = 0; i < Classes.size(); i++)
	{
		if (Classes[i]->GetClassID() == jobclass)
			Classes.erase(Classes.begin() + i);
	}
}

void Character::IncreaseLevel(CLASS jobclass, unsigned long Amount)
{
	bool newcharacter = Classes.empty();
	for (auto& a : Classes)
	{
		if (a->GetClassID() == jobclass)
		{
			a->IncreaseLevel(Amount);
			for (unsigned long i = 0; i < Amount; i++)
				MaximumHP += a->RollHitDice() + GetAbilityModifier(ABILITYSCORES::Constitution);
			return;
		}
	}
	switch (jobclass)
	{
	case CLASS::Barbarian:
		Classes.push_back(new Barbarian(AbilityScores, Amount));
		break;
	case CLASS::Bard:
		Classes.push_back(new Bard(AbilityScores, Amount));
		break;
	case CLASS::Cleric:
		Classes.push_back(new Cleric(AbilityScores, Amount));
		break;
	case CLASS::Druid:
		Classes.push_back(new Druid(AbilityScores, Amount));
		break;
	case CLASS::Fighter:
		Classes.push_back(new Fighter(AbilityScores, Amount));
		break;
	case CLASS::Monk:
		Classes.push_back(new Monk(AbilityScores, Amount));
		break;
	case CLASS::Paladin:
		Classes.push_back(new Paladin(AbilityScores, Amount));
		break;
	case CLASS::Ranger:
		Classes.push_back(new Ranger(AbilityScores, Amount));
		break;
	case CLASS::Sorcerer:
		Classes.push_back(new Sorcerer(AbilityScores, Amount));
		break;
	case CLASS::Warlock:
		Classes.push_back(new Warlock(AbilityScores, Amount));
		break;
	case CLASS::Wizard:
		Classes.push_back(new Wizard(AbilityScores, Amount));
		break;
	case CLASS::Other:
		//possibly make a placeholder class and give it this id
	default:
		Classes.push_back(new ErrorClass(Amount));
	}
	for (unsigned long i = 0; i < Amount; i++)
	{
		if (newcharacter)
		{
			MaximumHP = CurrentHP = Classes[0]->GetHitDice() + GetAbilityModifier(ABILITYSCORES::Constitution);
			newcharacter = false;
		}
		else
			MaximumHP += Classes.back()->RollHitDice() + GetAbilityModifier(ABILITYSCORES::Constitution);
	}
}

unsigned long Character::GetLevel(CLASS jobclass)
{
	for (auto j : Classes)
	{
		if (j->GetClassID() == jobclass)
			return j->GetLevel();
	}
	return 0;
}

unsigned long Character::GetLevels()
{
	unsigned long total = 0;
	for (auto j : Classes)
		total += j->GetLevel();
	return total;
}

struct Descending
{
	template<class T>
	bool operator()(T const &a, T const &b) const { return a > b; }
};

void Character::GenerateAbilityScores(CLASS primaryclass)
{
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

	AbilityScores.Strength.Value = abilityscores[0];
	AbilityScores.Dexterity.Value = abilityscores[1];
	AbilityScores.Constitution.Value = abilityscores[2];
	AbilityScores.Intelligence.Value = abilityscores[3];
	AbilityScores.Wisdom.Value = abilityscores[4];
	AbilityScores.Charisma.Value = abilityscores[5];

	abilityscores.clear();
}

long Character::GetAbilityModifier(ABILITYSCORES Abi)
{
	long score = 0;
	switch (Abi)
	{
	case ABILITYSCORES::Strength:
		score = GetAbilityScores().Strength.Value;
		break;
	case ABILITYSCORES::Dexterity:
		score = GetAbilityScores().Dexterity.Value;
		break;
	case ABILITYSCORES::Constitution:
		score = GetAbilityScores().Constitution.Value;
		break;
	case ABILITYSCORES::Intelligence:
		score = GetAbilityScores().Intelligence.Value;
		break;
	case ABILITYSCORES::Wisdom:
		score = GetAbilityScores().Wisdom.Value;
		break;
	case ABILITYSCORES::Charisma:
		score = GetAbilityScores().Charisma.Value;
		break;
	}

	return (score >= 10) ? (long)floor((score - 10) * 0.5) : (long)(-1 * ceil((10 - score) * 0.5));
}

long Character::GetSkillModifier(SkillID skillid)
{
	for (auto s : Skills)
	{
		if (s.ID == skillid)
		{
			if (s.Proficient)
			{
				return (s.Expertise) ? GetAbilityModifier(s.Ability) + 2 * GetProficiencyModifier() : GetAbilityModifier(s.Ability) + GetProficiencyModifier();
			}
			return GetAbilityModifier(s.Ability);
		}
	}
	return 0;
}

long Character::GetProficiencyModifier()
{
	unsigned long levels = GetLevels();
	if (levels < 5) return 2;
	if (levels < 9) return 3;
	if (levels < 13) return 4;
	if (levels < 17) return 5;
	return 6;
}

unsigned long Character::GetSpeed()
{
	return 30;
}

ABILITIES Character::GetAbilityScores()
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
}

std::wstring Character::GetSpeedW()
{
	std::wstring o = std::to_wstring(GetSpeed());
	o.append(L" ft");
	return o;
}

std::wstring Character::GetAbilityScoreW(ABILITYSCORES Abi)
{
	std::wstring o;
	switch (Abi)
	{
	case ABILITYSCORES::Strength:
		o = std::to_wstring(GetAbilityScores().Strength.Value);
		break;
	case ABILITYSCORES::Dexterity:
		o = std::to_wstring(GetAbilityScores().Dexterity.Value);
		break;
	case ABILITYSCORES::Constitution:
		o = std::to_wstring(GetAbilityScores().Constitution.Value);
		break;
	case ABILITYSCORES::Intelligence:
		o = std::to_wstring(GetAbilityScores().Intelligence.Value);
		break;
	case ABILITYSCORES::Wisdom:
		o = std::to_wstring(GetAbilityScores().Wisdom.Value);
		break;
	case ABILITYSCORES::Charisma:
		o = std::to_wstring(GetAbilityScores().Charisma.Value);
		break;
	default:
		o = L"Error";
	}
	return o;
}

std::wstring Character::GetAbilityModifierW(ABILITYSCORES Abi)
{
	std::wstring o = GetAbilityModifier(Abi) >= 0 ? L"+" : L"";
	o.append(std::to_wstring(GetAbilityModifier(Abi)));
	return o;
}