#pragma once
#include <string>
#include <vector>
#include "enums_and_structs.h"
#include "wrapper.h"
#include "Barbarian.h"
#include "Bard.h"
#include "Cleric.h"
#include "Druid.h"
#include "Fighter.h"
#include "Monk.h"
#include "Paladin.h"
#include "Ranger.h"
#include "Rogue.h"
#include "Sorcerer.h"
#include "Warlock.h"
#include "Wizard.h"
#include "TextDisplayBox.h"
#include "IncreaseDecrease.h"
#include "databox2.h"

struct ClassNameID
{
	std::wstring Name;
	CLASS ClassID;
	ClassNameID(std::wstring s, CLASS id)
	{
		Name = s;
		ClassID = id;
	}
};

class ClassContainer : public Wrapper
{
public:
	std::vector<TextHoldingBox> ClassListBox;
	std::vector<ClassNameID> ClassList;
	std::vector<CLASS> ClassID;
	std::vector<DataBox2> Increase;
	std::vector<DataBox2> Decrease;
	ClassNameID* SelectedClass = NULL;
	ClassContainer()
	{
		ClassList.push_back(ClassNameID(L"Barbarian", CLASS::Barbarian));
		ClassList.push_back(ClassNameID(L"Bard", CLASS::Bard));
		ClassList.push_back(ClassNameID(L"Cleric", CLASS::Cleric));
		ClassList.push_back(ClassNameID(L"Druid", CLASS::Druid));
		ClassList.push_back(ClassNameID(L"Fighter", CLASS::Fighter));
		ClassList.push_back(ClassNameID(L"Monk", CLASS::Monk));
		ClassList.push_back(ClassNameID(L"Paladin", CLASS::Paladin));
		ClassList.push_back(ClassNameID(L"Ranger", CLASS::Ranger));
		ClassList.push_back(ClassNameID(L"Rogue", CLASS::Rogue));
		ClassList.push_back(ClassNameID(L"Sorcerer", CLASS::Sorcerer));
		ClassList.push_back(ClassNameID(L"Warlock", CLASS::Warlock));
		ClassList.push_back(ClassNameID(L"Wizard", CLASS::Wizard));

		for (auto& c : ClassList)
		{
			ClassListBox.push_back(&c.Name);
			std::wstring tn = c.Name;
			tn.append(L"Increase");
			Increase.push_back(DataBox2(D2D1::RectF(), tn.c_str(), L"+", NULL, 1.0f, false, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
			tn.clear(); tn = c.Name;
			tn.append(L"Decrease");
			Decrease.push_back(DataBox2(D2D1::RectF(), tn.c_str(), L"-", NULL, 1.0f, false, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
		}
	}
public:
	void Interact() override { bSelected ^= true; }
	std::wstring GetOutput() override { return (SelectedClass) ? SelectedClass->Name : L"Choose Class"; }
	long GetAbilityModifier(ABILITYSCORES Abi) override { return 0; }
	unsigned long GetAbilityScore(ABILITYSCORES Abi) override { return 0; }
	void SetClass(CLASS ClassID)
	{
		for (auto& c : ClassList)
		{
			if (c.ClassID == ClassID)
				SelectedClass = &c;
		}
	}
	void Draw(D2D1_RECT_F dest, Graphics* gfx, D2D1_COLOR_F color, DWRITE_TEXT_ALIGNMENT alignment, DWRITE_PARAGRAPH_ALIGNMENT p_alignment) override
	{
		if (bSelected)
		{
			float dist = dest.bottom - dest.top;
			gfx->FillRect(D2D1::RectF(dest.left, dest.top, dest.right, dest.top + (ClassList.size() + 1) * dist), D2D1::ColorF(0.86f, 0.86f, 0.86f));
			gfx->DrawRect(D2D1::RectF(dest.left, dest.top, dest.right, dest.top + (ClassList.size() + 1) * dist), D2D1::ColorF(0.0f, 0.0f, 0.0f), 5.0f);
			for (size_t i = 0; i < ClassList.size(); i++)
			{
				gfx->OutputText(ClassList[i].Name.c_str(), D2D1::RectF(dest.left, dest.top + (i + 1) * dist, dest.right, dest.bottom + (i + 1) * dist), color, alignment, p_alignment);
				Increase[i].SetArea(D2D1::RectF(dest.right - 100.0f, dest.top + (i + 1) *dist, dest.right - 50.0f, dest.bottom + (i + 1) * dist));
				Decrease[i].SetArea(D2D1::RectF(dest.right - 50.0f, dest.top + (i + 1) *dist, dest.right, dest.bottom + (i + 1) * dist));
				Increase[i].Draw(gfx);
				Decrease[i].Draw(gfx);
			}
		}
		
		gfx->OutputText(GetOutput().c_str(), dest, color, alignment, p_alignment);
	}
	void OutsideBox(D2D1_POINT_2F p, D2D1_RECT_F dest) override
	{
		if (bSelected)
		{
			bool in = false;
			D2D1_RECT_F t = D2D1::RectF(dest.left, dest.top, dest.right, dest.bottom);
			float gap = dest.bottom - dest.top;
			for (size_t i = 0; i < ClassList.size(); i++)
			{
				if (p.x >= dest.left && p.x <= dest.right)
				{
					if (p.y >= (t.top + (i + 1) * gap) && p.y <= (t.bottom + (i + 1) * gap))
					{
						in = true;
						break;
					}
				}
			}
			if (in)
			{
				for (size_t i = 0 ; i < Increase.size(); i++)
				{
					if (Increase[i].PointInRect(p))
					{
						SelectedClass = &ClassList[i];
						IncreaseFlag = true;
					}
					if (Decrease[i].PointInRect(p))
					{
						SelectedClass = &ClassList[i];
						DecreaseFlag = true;
					}
				}
			}
			else bSelected = false;
		}
	}
};