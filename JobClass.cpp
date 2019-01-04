#include "JobClass.h"
#include<vector>
#include<algorithm>
#include<random>

void setabil(unsigned long*& pAbility, ABILITIES& abscores, ABILITYSCORES abtarget)
{
	switch (abtarget)
	{
	case ABILITYSCORES::Strength:
		pAbility = &abscores.Strength.Value;
		break;
	case ABILITYSCORES::Dexterity:
		pAbility = &abscores.Dexterity.Value;
		break;
	case ABILITYSCORES::Constitution:
		pAbility = &abscores.Constitution.Value;
		break;
	case ABILITYSCORES::Intelligence:
		pAbility = &abscores.Intelligence.Value;
		break;
	case ABILITYSCORES::Wisdom:
		pAbility = &abscores.Wisdom.Value;
		break;
	case ABILITYSCORES::Charisma:
		pAbility = &abscores.Charisma.Value;
		break;
	}
}

unsigned long* GetHighestAbilityScore(ABILITIES& abscores)
{
	unsigned long* ptemp = &abscores.Strength.Value;
	unsigned long temp = abscores.Strength.Value;
	if (temp < abscores.Dexterity.Value)
	{
		ptemp = &abscores.Dexterity.Value;
		temp = abscores.Dexterity.Value;
	}
	if (temp < abscores.Constitution.Value)
	{
		ptemp = &abscores.Constitution.Value;
		temp = abscores.Constitution.Value;
	}
	if (temp < abscores.Intelligence.Value)
	{
		ptemp = &abscores.Intelligence.Value;
		temp = abscores.Intelligence.Value;
	}
	if (temp < abscores.Wisdom.Value)
	{
		ptemp = &abscores.Wisdom.Value;
		temp = abscores.Wisdom.Value;
	}
	if (temp < abscores.Charisma.Value)
	{
		ptemp = &abscores.Charisma.Value;
		temp = abscores.Charisma.Value;
	}
	return ptemp;
}

unsigned long* GetSecondaryScore(ABILITIES& abscores)
{
	std::vector<unsigned long> list;
	list.push_back(abscores.Strength.Value);
	list.push_back(abscores.Dexterity.Value);
	list.push_back(abscores.Constitution.Value);
	list.push_back(abscores.Intelligence.Value);
	list.push_back(abscores.Wisdom.Value);
	list.push_back(abscores.Charisma.Value);
	std::sort(list.begin(), list.end());

	if (abscores.Strength.Value == list[4])
		return &abscores.Strength.Value;
	if (abscores.Dexterity.Value == list[4])
		return &abscores.Dexterity.Value;
	if (abscores.Constitution.Value == list[4])
		return &abscores.Constitution.Value;
	if (abscores.Intelligence.Value == list[4])
		return &abscores.Intelligence.Value;
	if (abscores.Wisdom.Value == list[4])
		return &abscores.Wisdom.Value;
	if (abscores.Charisma.Value == list[4])
		return &abscores.Charisma.Value;
	return NULL;
}

unsigned long* GetDumpScore(ABILITIES& abscores)
{
	std::vector<unsigned long> list;
	list.push_back(abscores.Strength.Value);
	list.push_back(abscores.Dexterity.Value);
	list.push_back(abscores.Constitution.Value);
	list.push_back(abscores.Intelligence.Value);
	list.push_back(abscores.Wisdom.Value);
	list.push_back(abscores.Charisma.Value);
	std::sort(list.begin(), list.end());

	if (abscores.Strength.Value == list[0])
		return &abscores.Strength.Value;
	if (abscores.Dexterity.Value == list[0])
		return &abscores.Dexterity.Value;
	if (abscores.Constitution.Value == list[0])
		return &abscores.Constitution.Value;
	if (abscores.Intelligence.Value == list[0])
		return &abscores.Intelligence.Value;
	if (abscores.Wisdom.Value == list[0])
		return &abscores.Wisdom.Value;
	if (abscores.Charisma.Value == list[0])
		return &abscores.Charisma.Value;
	return NULL;
}

void JobClass::UpdateAbilityScores(ABILITIES& abscores)
{
	if (!p_PrimaryAbility || !p_SecondaryAbility || !p_DumpAbility) return;

	unsigned long* ptemp = GetHighestAbilityScore(abscores);
	if (p_PrimaryAbility != ptemp)
	{
		unsigned long temp = *p_PrimaryAbility;
		*p_PrimaryAbility = *ptemp;
		*ptemp = temp;
	}
	ptemp = GetSecondaryScore(abscores);
	if (ptemp)
	{
		if (p_SecondaryAbility != ptemp)
		{
			unsigned long temp = *p_SecondaryAbility;
			*p_SecondaryAbility = *ptemp;
			*ptemp = temp;
		}
	}
	ptemp = GetDumpScore(abscores);
	if (ptemp)
	{
		if (p_DumpAbility != ptemp)
		{
			unsigned long temp = *p_DumpAbility;
			*p_DumpAbility = *ptemp;
			*ptemp = temp;
		}
	}
}

void JobClass::SetAbilityPointers(ABILITIES& abscores)
{
	setabil(p_PrimaryAbility, abscores, PrimaryAbility);
	setabil(p_SecondaryAbility, abscores, SecondaryAbility);
	setabil(p_DumpAbility, abscores, DumpAbility);
	UpdateAbilityScores(abscores);
}

void JobClass::ShowStuff()
{
	std::wcout << ClassName.c_str() << " (ID" << (long)GetClassID() << "): " << Level << " Level(s), d" << GetHitDice() << " Hit Die\n"; 
}

unsigned long JobClass::RollHitDice()
{
	std::random_device rd;
	std::mt19937_64 mt(rd());
	std::uniform_int_distribution<long> dist(1, HitDice);

	return dist(mt);
}

char* JobClass::trim(char* buffer)
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

void JobClass::FillFeatures(const wchar_t* Path)
{
	FILE* file = NULL;
	errno_t err = _wfopen_s(&file, Path, L"rb");
	if (err) return;

	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* buffer = new char[size];
	fread(buffer, size, 1, file);
	fclose(file);
	char* ptr = strchr(buffer, ';');
	char* optr = buffer;
	while (ptr)
	{
		char* t = new char[ptr - optr + 1];
		t[ptr - optr] = '\0';
		memcpy(t, optr, ptr - optr);
		t = trim(t);
		FillFeature(t);
		delete[]t;
		
		optr = ptr + 1;
		ptr = strchr(optr, ';');
	}

	if (Features.back().ClassID != GetClassID() && Features.back().ClassID != CLASS::All)
		Features.pop_back();
	delete[] buffer;
}

void JobClass::FillFeature(const char* Buffer)
{
	char* buffer = new char[strlen(Buffer) + 1];
	buffer[strlen(Buffer)] = '\0';
	memcpy(buffer, Buffer, strlen(Buffer));

	char* ptr = strchr(buffer, '=');
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

		if (!_stricmp(temp, "FeatureName"))
		{
			if (Features.size())
			{
				if (Features.back().ClassID != GetClassID() && Features.back().ClassID != CLASS::All)
					Features.pop_back();
			}
			Feature f;
			f.Name = std::wstring(&ptr[1], &ptr[strlen(ptr)]);
			Features.push_back(f);
		}
		else
		{
			if (Features.size())
			{
				if (!_stricmp(temp, "FeatureClass"))
				{
					Features.back().Class = std::wstring(entry, entry + strlen(entry));
					Features.back().ClassID = stringToClassID(entry);
				}
				if (!_stricmp(temp, "FeatureAction"))
				{
					Features.back().Action = std::wstring(entry, entry + strlen(entry));
				}
				if (!_stricmp(temp, "FeatureDuration"))
				{
					Features.back().Duration = std::wstring(entry, entry + strlen(entry));
				}
				if (!_stricmp(temp, "FeatureDurationI"))
				{
					Features.back().iDurationTurns = atoi(entry);
				}
				if (!_stricmp(temp, "FeatureMinimumLevel"))
				{
					Features.back().MinimumLevel = atoi(entry);
				}
				if (!_stricmp(temp, "FeatureUpgradeLevels"))
				{
					Features.back().UpgradeLevels.push_back(atoi(entry));
					char* t = strchr(entry, ',');
					while (t)
					{
						Features.back().UpgradeLevels.push_back(atoi(t + 1));
						t = strchr(t + 1, ',');
					}
					std::sort(Features.back().UpgradeLevels.begin(), Features.back().UpgradeLevels.end());
				}
				if (!_stricmp(temp, "FeatureNumberUses"))
				{
					Features.back().NumberUses = atoi(entry);
				}
				if (!_stricmp(temp, "UpgradeOverride"))
				{
					Features.back().Overrides = std::wstring(entry, entry + strlen(entry));
				}
				if (!_stricmp(temp, "FeatureDescription"))
				{
					Features.back().Description = std::wstring(entry, entry + strlen(entry));
				}
			}
		}
		delete[] entry;
		delete[] temp;
	}
	delete[] buffer;
}

CLASS JobClass::stringToClassID(const char* buffer)
{
	if (!_stricmp(buffer, "Barbarian"))
		return CLASS::Barbarian;
	if (!_stricmp(buffer, "Bard"))
		return CLASS::Bard;
	if (!_stricmp(buffer, "Cleric"))
		return CLASS::Cleric;
	if (!_stricmp(buffer, "Druid"))
		return CLASS::Druid;
	if (!_stricmp(buffer, "Fighter"))
		return CLASS::Fighter;
	if (!_stricmp(buffer, "Monk"))
		return CLASS::Monk;
	if (!_stricmp(buffer, "Paladin"))
		return CLASS::Paladin;
	if (!_stricmp(buffer, "Ranger"))
		return CLASS::Ranger;
	if (!_stricmp(buffer, "Rogue"))
		return CLASS::Rogue;
	if (!_stricmp(buffer, "Sorcerer"))
		return CLASS::Sorcerer;
	if (!_stricmp(buffer, "Warlock"))
		return CLASS::Warlock;
	if (!_stricmp(buffer, "Wizard"))
		return CLASS::Wizard;
	if (!_stricmp(buffer, "Other"))
		return CLASS::Other;
	if (!_stricmp(buffer, "ALL"))
		return CLASS::All;
	return CLASS::Error;
}