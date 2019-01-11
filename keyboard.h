#pragma once
#include <Windows.h>
#include <vector>

struct Key
{
	long KeyID = 0;
	bool up = true;
	Key(long id = 0, bool up = true)
	{
		KeyID = id;
		this->up = up;
	}
};

struct Keyboard
{
	std::vector<Key> KeyStatus;
	std::vector<Key> OldKeyStatus;
	Keyboard()
	{
		for (long i = 0; i < 0xFE; i++)
		{
			KeyStatus.push_back(Key(i, true));
			OldKeyStatus.push_back(Key(i, true));
		}
	}
	void UpdateKeyStatus()
	{
		if (KeyStatus.empty()) return;

		for (size_t i = 0; i < KeyStatus.size(); i++)
		{
			OldKeyStatus[i].up = KeyStatus[i].up;
			KeyStatus[i].up = (GetKeyState((int)i) < 0);
		}
	}
	bool GetStatus(long key)
	{
		return KeyStatus[key].up;
	}
	bool GetOldStatus(long key)
	{
		return OldKeyStatus[key].up;
	}
};