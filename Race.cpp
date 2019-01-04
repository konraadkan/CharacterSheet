#include "Race.h"
#include <algorithm>

void Race::FillTraits(const wchar_t* FilePath)
{
	FILE* file = NULL;
	errno_t err = _wfopen_s(&file, FilePath, L"rb");
	if (err) return;

	fseek(file, 0, SEEK_END);
	size_t bufferlen = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* Buffer = new char[bufferlen];
	fread(Buffer, bufferlen, 1, file);
	fclose(file);

	FillTraits(Buffer, bufferlen);

	delete[] Buffer;
}

void Race::FillTraits(const char* Buffer, size_t buffersize)
{
	const char* ptr = strchr(Buffer, ';');
	const char* optr = Buffer;
	while (ptr)
	{
		char* t = new char[ptr - optr + 1];
		t[ptr - optr] = '\0';
		memcpy(t, optr, ptr - optr);
		t = trim(t);
		FillTrait(t);
		delete[] t;

		optr = ptr + 1;
		ptr = strchr(optr, ';');
	}

	std::vector<size_t> delpos;
	for (size_t i =0; i < Traits.size(); i++)
	{
		if (_wcsicmp(Traits[i].Race.c_str(), Name.c_str()) || Traits[i].Race.empty())
		{
			delpos.push_back(i);
		}
	}
	std::sort(delpos.begin(), delpos.end());
	while (delpos.size())
	{
		Traits.erase(Traits.begin() + delpos.back());
		delpos.pop_back();
	}
}

void Race::SetSubRace(std::wstring name)
{
	for (auto& sr : Subraces)
	{
		if (!_wcsicmp(sr.Name.c_str(), name.c_str()))
		{
			SelectedSubRace = &sr;
			break;
		}
	}
}

bool Race::FillTrait(const char* Buffer)
{
	char* buffer = new char[strlen(Buffer) + 1];
	buffer[strlen(Buffer)] = '\0';
	memcpy(buffer, Buffer, strlen(Buffer));

	bool foundit = false;

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

		if (!_stricmp(temp, "TraitName"))
		{
			Trait t;
			t.Name = std::wstring(entry, entry + strlen(entry));
			Traits.push_back(t);
			foundit = true;
		}
		else
		{
			if (Traits.size())
			{
				if (!_stricmp(temp, "TraitRace"))
				{
					Traits.back().Race = std::wstring(entry, entry + strlen(entry));
					foundit = true;
				}
				if (!_stricmp(temp, "TraitDescription"))
				{
					Traits.back().Description = std::wstring(entry, entry + strlen(entry));
					foundit = true;
				}
				if (!_stricmp(temp, "VisionType"))
				{
					Vision v;
					if (!_stricmp(entry, "Normal"))
					{
						v.Types = VisionType::Normal;
						foundit = true;
					}
					if (!_stricmp(entry, "Darkvision"))
					{
						v.Types = VisionType::Darkvision;
						foundit = true;
					}
					if (!_stricmp(entry, "Truesight"))
					{
						v.Types = VisionType::Truesight;
						foundit = true;
					}
					if (!_stricmp(entry, "Blindsight"))
					{
						v.Types = VisionType::Blindsight;
						foundit = true;
					}
					if (!_stricmp(entry, "Tremorsense"))
					{
						v.Types = VisionType::Tremorsense;
						foundit = true;
					}
					Perceptions.push_back(v);
				}
				if (!_stricmp(temp, "VisionDistance"))
				{
					if (Perceptions.size())
					{
						Perceptions.back().Distance = atoi(entry);
						foundit = true;
					}
				}
			}
		}
		if (!_stricmp(temp, "RaceName"))
		{
			Name = std::wstring(entry, entry + strlen(entry));
			foundit = true;
		}
		if (!_stricmp(temp, "RaceAgeDetails"))
		{
			AgeDetails = std::wstring(entry, entry + strlen(entry));
			foundit = true;
		}
		if (!_stricmp(temp, "RaceHeight"))
		{
			Height = std::wstring(entry, entry + strlen(entry));
			foundit = true;
		}
		if (!_stricmp(temp, "RaceLanguages"))
		{
			Languages = std::wstring(entry, entry + strlen(entry));
			foundit = true;
			//add a vector for languages
		}
		if (!_stricmp(temp, "RaceSizeCategory"))
		{
			Size = CharToSize(entry);
			foundit = true;
		}
		if (!_stricmp(temp, "RaceSpeed"))
		{
			Speed = atoi(entry);
			foundit = true;
		}
		if (!_stricmp(temp, "RaceAlignments"))
		{
			Alignments = std::wstring(entry, entry + strlen(entry));
			foundit = true;
		}
		if (!_stricmp(temp, "RaceAbilityScores"))
		{
			size_t counter = 0;
			unsigned long* abinum = &AbilityScoreIncreases.Strength.Value;
			const char* tp = strchr(entry, ',');
			if(!tp) tp = strchr(entry, '\0');
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
					abinum = &AbilityScoreIncreases.Dexterity.Value;
					break;
				case 1:
					abinum = &AbilityScoreIncreases.Constitution.Value;
					break;
				case 2:
					abinum = &AbilityScoreIncreases.Intelligence.Value;
					break;
				case 3:
					abinum = &AbilityScoreIncreases.Wisdom.Value;
					break;
				case 4:
					abinum = &AbilityScoreIncreases.Charisma.Value;
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
				foundit = true;
			}
		}
		delete[] entry;
		delete[] temp;
	}
	delete[] buffer;
	return foundit;
}

char* Race::trim(char* buffer)
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

unsigned long Race::GetAbilityScore(const char* abi)
{
	if (SelectedSubRace)
	{
		if (!_stricmp(abi, "Strength") || !_stricmp(abi, "STR"))
		{
			return AbilityScoreIncreases.Strength.Value + SelectedSubRace->AbilityScoreIncreases.Strength.Value;
		}
		if (!_stricmp(abi, "Dexterity") || !_stricmp(abi, "DEX"))
		{
			return AbilityScoreIncreases.Dexterity.Value + SelectedSubRace->AbilityScoreIncreases.Dexterity.Value;
		}
		if (!_stricmp(abi, "Constitution") || !_stricmp(abi, "CON"))
		{
			return AbilityScoreIncreases.Constitution.Value + SelectedSubRace->AbilityScoreIncreases.Constitution.Value;
		}
		if (!_stricmp(abi, "Intelligence") || !_stricmp(abi, "INT"))
		{
			return AbilityScoreIncreases.Intelligence.Value + SelectedSubRace->AbilityScoreIncreases.Intelligence.Value;
		}
		if (!_stricmp(abi, "Wisdom") || !_stricmp(abi, "WIS"))
		{
			return AbilityScoreIncreases.Wisdom.Value + SelectedSubRace->AbilityScoreIncreases.Wisdom.Value;
		}
		if (!_stricmp(abi, "Charisma") || !_stricmp(abi, "CHA"))
		{
			return AbilityScoreIncreases.Charisma.Value + SelectedSubRace->AbilityScoreIncreases.Charisma.Value;
		}
	}
	else
	{
		if (!_stricmp(abi, "Strength") || !_stricmp(abi, "STR"))
		{
			return AbilityScoreIncreases.Strength.Value;
		}
		if (!_stricmp(abi, "Dexterity") || !_stricmp(abi, "DEX"))
		{
			return AbilityScoreIncreases.Dexterity.Value;
		}
		if (!_stricmp(abi, "Constitution") || !_stricmp(abi, "CON"))
		{
			return AbilityScoreIncreases.Constitution.Value;
		}
		if (!_stricmp(abi, "Intelligence") || !_stricmp(abi, "INT"))
		{
			return AbilityScoreIncreases.Intelligence.Value;
		}
		if (!_stricmp(abi, "Wisdom") || !_stricmp(abi, "WIS"))
		{
			return AbilityScoreIncreases.Wisdom.Value;
		}
		if (!_stricmp(abi, "Charisma") || !_stricmp(abi, "CHA"))
		{
			return AbilityScoreIncreases.Charisma.Value;
		}
	}
	return 0;
}

unsigned long Race::GetAbilityScore(ABILITYSCORES abi)
{
	if (SelectedSubRace)
	{
		switch (abi)
		{
		case ABILITYSCORES::Strength:
			return AbilityScoreIncreases.Strength.Value + SelectedSubRace->AbilityScoreIncreases.Strength.Value;
		case ABILITYSCORES::Dexterity:
			return AbilityScoreIncreases.Dexterity.Value + SelectedSubRace->AbilityScoreIncreases.Dexterity.Value;
		case ABILITYSCORES::Constitution:
			return AbilityScoreIncreases.Constitution.Value + SelectedSubRace->AbilityScoreIncreases.Constitution.Value;
		case ABILITYSCORES::Intelligence:
			return AbilityScoreIncreases.Intelligence.Value + SelectedSubRace->AbilityScoreIncreases.Intelligence.Value;
		case ABILITYSCORES::Wisdom:
			return AbilityScoreIncreases.Wisdom.Value + SelectedSubRace->AbilityScoreIncreases.Wisdom.Value;
		case ABILITYSCORES::Charisma:
			return AbilityScoreIncreases.Charisma.Value + SelectedSubRace->AbilityScoreIncreases.Charisma.Value;
		}
	}
	else
	{
		switch (abi)
		{
		case ABILITYSCORES::Strength:
			return AbilityScoreIncreases.Strength.Value;
		case ABILITYSCORES::Dexterity:
			return AbilityScoreIncreases.Dexterity.Value;
		case ABILITYSCORES::Constitution:
			return AbilityScoreIncreases.Constitution.Value;
		case ABILITYSCORES::Intelligence:
			return AbilityScoreIncreases.Intelligence.Value;
		case ABILITYSCORES::Wisdom:
			return AbilityScoreIncreases.Wisdom.Value;
		case ABILITYSCORES::Charisma:
			return AbilityScoreIncreases.Charisma.Value;
		}
	}
	return 0;
}