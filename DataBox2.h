#pragma once
#include <string>
#include "graphics.h"
#include "wrapper.h"

class DataBox2
{
private:
	bool bHideBorder = false;
	bool bHighlight = false;
	D2D1_RECT_F Area;
	float scale = 1.0f;
	float invScale = 1.0f;
	std::wstring output;
	std::wstring Name;
	DWRITE_TEXT_ALIGNMENT alignment = DWRITE_TEXT_ALIGNMENT_LEADING;
	DWRITE_PARAGRAPH_ALIGNMENT p_alignment = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;	
public:
	DataBox2(D2D1_RECT_F dest, const wchar_t* name, const wchar_t* data, Wrapper* w = NULL, float scale = 1.0f, bool hideborder = false, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT p_align = DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	~DataBox2();
	void Draw(Graphics* gfx = NULL, D2D1_COLOR_F color = D2D1::ColorF(0.0f, 0.0f, 0.0f));
	void Toggle() { bHighlight ^= true; }
	void Interact();
	bool PointInRect(D2D1_POINT_2F p);
	Wrapper* wrapper = NULL;
};