#include "Subraces.h"

Subrace::Subrace(std::wstring name, std::wstring race)
{
	Name = name;
	BaseRace = race;
}

char* Subrace::trim(char* buffer)
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

bool Subrace::FillTrait(const char* Buffer)
{
	bool foundit = false;
	
	const char* ptr = strchr(Buffer, '=');
	if (ptr)
	{
		char* temp = new char[ptr - Buffer + 1];
		temp[ptr - Buffer] = '\0';
		memcpy(temp, Buffer, ptr - Buffer);
		temp = trim(temp);

		char* entry = new char[(Buffer + strlen(Buffer) - ptr)];
		entry[(Buffer + strlen(Buffer) - ptr) - 1] = '\0';
		memcpy(entry, ptr + 1, (Buffer + strlen(Buffer) - ptr) - 1);
		entry = trim(entry);

		if (!_stricmp(temp, "SubraceTraitName"))
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
				if (!_stricmp(temp, "SubraceTraitRace"))
				{
					Traits.back().Race = std::wstring(entry, entry + strlen(entry));
					foundit = true;
				}
				if (!_stricmp(temp, "SubraceTraitDescription"))
				{
					Traits.back().Description = std::wstring(entry, entry + strlen(entry));
					foundit = true;
				}
				if (!_stricmp(temp, "SubraceVisionType"))
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
				if (!_stricmp(temp, "SubraceVisionDistance"))
				{
					if (Perceptions.size())
					{
						Perceptions.back().Distance = atoi(entry);
						foundit = true;
					}
				}
			}
		}
		delete[] entry;
		delete[] temp;
	}

	return foundit;
}