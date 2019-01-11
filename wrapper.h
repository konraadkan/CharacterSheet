#pragma once
#include <string>
#include <D2D1_1.h>
#include "graphics.h"

enum class ABILITYSCORES
{
	Strength,
	Dexterity,
	Constitution,
	Intelligence,
	Wisdom,
	Charisma,
	AbilityError
};

class Wrapper
{
private:
	Wrapper* Child = NULL;
public:
	bool IncreaseFlag = false;
	bool DecreaseFlag = false;
	D2D1_COLOR_F SelectedColor = D2D1::ColorF(0.0f, 0.0f, 0.0f);
	D2D1_COLOR_F DefaultColor = D2D1::ColorF(0.0f, 0.0f, 0.0f);
	bool bSelected = false;
	virtual void OutsideBox(D2D1_POINT_2F p, D2D1_RECT_F dest) { bSelected = false; }
	virtual void Interact() = 0;
	virtual std::wstring GetOutput() = 0;
	virtual long GetAbilityModifier(ABILITYSCORES Abi) { return 0; }
	virtual unsigned long GetAbilityScore(ABILITYSCORES Abi) { return 0; }
	virtual void Draw(D2D1_RECT_F dest, Graphics* gfx, D2D1_COLOR_F color = D2D1::ColorF(0.0f, 0.0f, 0.0f), DWRITE_TEXT_ALIGNMENT alignment = DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT p_alignment = DWRITE_PARAGRAPH_ALIGNMENT_NEAR)
	{
		gfx->OutputText(GetOutput().c_str(), dest, color, alignment, p_alignment);
	}
};