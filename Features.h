#pragma once
#include<string>
#include<vector>

class Feature
{
protected:
	wchar_t* trim(wchar_t* buffer)
	{
		if (!buffer) return NULL;
		size_t startpoint = 0;
		size_t endpoint = wcslen(buffer);
		for (size_t i = 0; i < wcslen(buffer); i++)
		{
			if (buffer[i] == '\n' || buffer[i] == '\r' || buffer[i] == '\0' || buffer[i] == ' ')
			{
				startpoint = i + 1;
			}
			else
				break;
		}
		for (size_t i = wcslen(buffer); i > 0; i--)
		{
			if (buffer[i] == '\n' || buffer[i] == '\r' || buffer[i] == '\0' || buffer[i] == ' ')
			{
				endpoint = i;
			}
			else
				break;
		}
		wchar_t* newbuffer = new wchar_t[endpoint - startpoint + 1];
		newbuffer[endpoint - startpoint] = L'\0';
		memcpy(newbuffer, buffer + startpoint * sizeof(char), sizeof(wchar_t)*(endpoint - startpoint));
		delete[] buffer;
		return newbuffer;
	}
public:
	CLASS ClassID;
	std::wstring Name;
	std::wstring Description;
	std::wstring Duration;
	std::wstring Action;
	std::wstring Class;
	std::wstring Overrides;
	unsigned long iDurationTurns = 0;
	unsigned long MinimumLevel = 0;
	unsigned long NumberUses = 0;
	std::vector<unsigned long> UpgradeLevels;
	void OutputDetails()
	{
		std::wcout << Name.c_str() << std::endl;
		std::wcout << Class.c_str() << std::endl;
		std::wcout << Action.c_str() << std::endl;
		if (Duration.size())
		{
			std::wcout << L"Duration      : " << Duration.c_str() << L':';
			std::wcout << iDurationTurns << L" turns\n";
		}
		std::wcout << L"Level         : " << (long)MinimumLevel << std::endl;
		std::wcout << L"Uses          : " << (long)NumberUses << std::endl;
		std::wcout << L"Upgrade Levels: ";
		for (size_t i = 0; i < UpgradeLevels.size(); i++)
			std::wcout << UpgradeLevels[i] << ',';
		std::wcout << L"\nOverrides     : " << Overrides << std::endl;
		std::wcout << std::endl << Description.c_str() << std::endl;
	}
	void Update(unsigned long level)
	{
		wchar_t* temp = new wchar_t[Overrides.size() + 1];
		temp[Overrides.size()] = L'\0';
		memcpy(temp, &Overrides[0], sizeof(wchar_t) * Overrides.size());
		temp = trim(temp);
		wchar_t* ptr = wcschr(temp, L'=');

		if (ptr)
		{
			wchar_t* OverrideTarget = new wchar_t[ptr - temp + 1];
			OverrideTarget[ptr - temp] = L'\0';
			memcpy(OverrideTarget, temp, (ptr - temp) * sizeof(wchar_t));
			OverrideTarget = trim(OverrideTarget);

			wchar_t* entry = new wchar_t[(temp + wcslen(temp) - ptr)];
			entry[(temp + wcslen(temp) - ptr) - 1] = '\0';
			memcpy(entry, ptr + 1, sizeof(wchar_t) * ((temp + wcslen(temp) - ptr) - 1));
			entry = trim(entry);

			unsigned long LevelTier = 0;
			for (size_t i = 0; i < UpgradeLevels.size(); i++)
			{
				if (level >= UpgradeLevels[i])
					LevelTier = (unsigned long)(i + 1);
			}

			if (LevelTier)
			{
				std::vector<std::wstring> OverrideDetails;
				wchar_t* tmp = wcschr(entry, ',');
				wchar_t* otmp = entry;
				while (tmp)
				{
					std::wstring wt(otmp, tmp);
					OverrideDetails.push_back(wt);
					otmp = tmp + 1;
					tmp = wcschr(otmp, ',');
				}
				if (!tmp) OverrideDetails.push_back(otmp);
				if (!_wcsicmp(OverrideTarget, L"FeatureDuration"))
				{
					Duration.clear();
					Duration = OverrideDetails[LevelTier - 1];
				}
				if (!_wcsicmp(OverrideTarget, L"FeatureAction"))
				{
					Action.clear();
					Action = OverrideDetails[LevelTier - 1];
				}
				if (!_wcsicmp(OverrideTarget, L"FeatureDurationI"))
				{
					iDurationTurns = _wtoi(OverrideDetails[LevelTier - 1].c_str());
				}
				if (!_wcsicmp(OverrideTarget, L"FeatureNumberUses"))
				{
					NumberUses = _wtoi(OverrideDetails[LevelTier - 1].c_str());
				}
			}
			delete[] entry;
			delete[] OverrideTarget;
		}
		delete[] temp;
	}
};