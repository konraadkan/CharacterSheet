#pragma once
#include <vector>
#include "wrapper.h"

class TextHoldingBox : public Wrapper
{
private:
	std::wstring* StringPtr = NULL;
public:
	TextHoldingBox(std::wstring* Ptr = NULL) { StringPtr = Ptr; }
	void Interact() override { bSelected = true; }
	std::wstring GetOutput() override { return *StringPtr; }
	long GetAbilityModifier(ABILITYSCORES Abi) override { return 0; }
	unsigned long GetAbilityScore(ABILITYSCORES Abi) override { return 0; }
	void UpdatePointer(std::wstring* Ptr) { StringPtr = Ptr; }
	void Backspace()
	{
		if (StringPtr->size())
			StringPtr->pop_back();
	}
	void AppendKey(wchar_t key)
	{
		if (key != VK_BACK && key != VK_RETURN)
		{
			StringPtr->push_back(key);
		}
		else
		{
			switch (key)
			{
			case VK_BACK:
				if (StringPtr->size())
					StringPtr->pop_back();
				break;
			case VK_RETURN:
				bSelected = false;
				break;
			}
		}
	}
	void AppendKeys(std::vector<wchar_t> keys)
	{
		//this was a test case, AppendKey() will generally be more useful
		bool toupper = false;
		for (auto c : keys)
		{
			if (c == VK_SHIFT || c == VK_LSHIFT || c == VK_RSHIFT)
				toupper = true;
		}
		for (auto c : keys)
		{
			if (c == VK_SHIFT || c == VK_LSHIFT || c == VK_RSHIFT) continue;
			if (c == VK_BACK) continue;
			if (c == VK_RETURN)
			{
				bSelected = false;
				continue;
			}
			if (toupper)
				StringPtr->push_back(towupper(c));
			else
				StringPtr->push_back(c);
		}
	}
};