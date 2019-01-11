#pragma once
#include <vector>
#include "graphics.h"
#include "Character.h"
#include "Keyboard.h"
#include "Classlist.h"

class Stage
{
protected:
	static Graphics* gfx;
public:
	static Keyboard KeyStatus;
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}
	virtual void Load() = 0;
	virtual void Load(std::vector<Character*> &Characters) = 0;
	virtual void Render() = 0;
	virtual void Unload() = 0;
	virtual void Update(float delta) = 0;
	static std::vector<wchar_t> GetKeysPressed()
	{
		KeyStatus.UpdateKeyStatus();
		std::vector<wchar_t> keysdown;
		for (int i = 0; i < KeyStatus.KeyStatus.size(); i++)
		{
			if (KeyStatus.GetStatus(i))
			{
				if (!KeyStatus.GetOldStatus(i))
				{
					keysdown.push_back(btowc(tolower(i)));
				}
				else if (i == VK_SHIFT)
					keysdown.push_back(i);
			}
		}
		return keysdown;
	}
};