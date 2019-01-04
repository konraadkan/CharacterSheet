#include "InitialStage.h"

InitialStage::InitialStage(Graphics* graphics, D2D1_POINT_2F* P)
{
	Init(graphics);
	CharacterSheet = new Sprite(L"Character_Sheet.png", graphics);
	p = P;
}

InitialStage::~InitialStage()
{
	Unload();
}

void InitialStage::Load()
{
	Characters = NULL;
}

void InitialStage::Load(std::vector<Character*>& characters)
{
	Characters = &characters;
	SelectedCharacter = Characters->front();
	if (Reroll) delete Reroll;
	Reroll = new RerollInteraction(&SelectedCharacter->AbilityScores);
	SelectedCharacter->SetRace(L"Elf");
	SelectedCharacter->SetSubrace(L"High Elf");
	SelectedCharacter->AbilityScores.SetRace(SelectedCharacter->CharacterRace);
	SelectedCharacter->AbilityScores.SetSubRace(SelectedCharacter->CharacterRace->SelectedSubRace);
}

void InitialStage::Render()
{
	gfx->GetCompatibleTarget()->BeginDraw();
	gfx->ClearScreen(D2D1::ColorF(1.0f, 1.0f, 1.0f));
	CharacterSheet->DrawFrame(D2D1::Point2F(0.0f, 0.0f));
	BuildForm();
	gfx->GetCompatibleTarget()->EndDraw();

	ID2D1Bitmap* tbitmap = NULL;
	gfx->GetCompatibleTarget()->GetBitmap(&tbitmap);
	if (tbitmap)
	{//D2D1::SizeF(2550.0f,3300.0f) is the size of the image being used as the backdrop
		gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale, scale), D2D1::Point2F(1920.0f *0.5f, 1080.0f *0.5f)) * D2D1::Matrix3x2F::Translation(Translation));
		D2D1::Matrix3x2F transform;

		gfx->GetRenderTarget()->GetTransform(&transform);
		transform.Invert();
		pTransformed = transform.TransformPoint(*p);

		gfx->GetRenderTarget()->DrawBitmap(tbitmap, D2D1::RectF(0.0f, 0.0f, 2550.0f, 3300.0f), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0.0f, 0.0f, 2550.0f, 3300.0f));
		gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
		tbitmap->Release();
	}
}

void InitialStage::Unload()
{
	if (CharacterSheet) delete CharacterSheet;
	CharacterSheet = NULL;
	if (Reroll) delete Reroll;
	Reroll = NULL;
}

void InitialStage::Update(float delta)
{
	//pTransformed holds the mouse x, y coords 
	if (GetKeyState(VK_LBUTTON) < 0)
	{
		if (bButtonUp)
		{
			for (auto& c : DataBoxes)
			{
				if (c.PointInRect(pTransformed))
					c.Interact();
				if (Reroll->ScoresGenerated)
				{
					Reroll->ScoresGenerated = false;
					if (SelectedCharacter)
						if (SelectedCharacter->Classes.size()) SelectedCharacter->Classes.front()->UpdateAbilityScores(SelectedCharacter->AbilityScores);
				}
			}
			bShowDropDown ^= true;
			bButtonUp = false;
		}
	}
	else bButtonUp = true;
	if (GetKeyState(VK_ADD) < 0) scale += ScalingSpeed * delta;
	if (GetKeyState(VK_SUBTRACT) < 0) scale = (scale - ScalingSpeed * delta <= 0.0f) ? ScalingSpeed * delta : scale - ScalingSpeed * delta;
	if (GetKeyState(VK_LEFT) < 0) Translation.width -= delta * TranslationSpeed;
	if (GetKeyState(VK_RIGHT) < 0) Translation.width += delta * TranslationSpeed;
	if (GetKeyState(VK_UP) < 0) Translation.height -= delta * TranslationSpeed;
	if (GetKeyState(VK_DOWN) < 0) Translation.height += delta * TranslationSpeed;
	if (GetKeyState(VK_RBUTTON) < 0)
	{
		if (Characters->size())
		{
			if (SelectedCharacter)
			{
				if (SelectedCharacter->Classes.empty())
				{
					SelectedCharacter->Classes.push_back(new Barbarian(SelectedCharacter->AbilityScores));
					SelectedCharacter->GenerateAbilityScores(SelectedCharacter->Classes.front()->GetClassID());
					SelectedCharacter->Classes.front()->UpdateAbilityScores(SelectedCharacter->AbilityScores);
					UpdateDataBoxes();
				}
			}
		}
	}
}

template<class T, class A> void InitialStage::ShowDD(std::vector<T, A>const& vec, D2D1_RECT_F area)
{
	D2D1_SIZE_F dist;
	dist.width = area.right - area.left;
	dist.height = area.bottom - area.top;
	float i = 1;
	for (auto q : vec)
	{
		D2D1_RECT_F tarea = D2D1::RectF(area.left, area.top + i * dist.height, area.right, area.bottom + i * dist.height);
		
		gfx->FillRect(tarea, D2D1::ColorF(0.66f, 0.66f, 0.66f, 1.0f));
		gfx->OutputText(q->m_GetClassName().c_str(), tarea, D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		gfx->DrawRect(D2D1::RectF(area.left, area.top + i * dist.height, area.right, area.bottom + i * dist.height), D2D1::ColorF(.7f, .8f, .7f));
		i++;
	}
}

void InitialStage::ShowDropDown(D2D1_RECT_F area)
{
	D2D1_SIZE_F dist;
	dist.width = area.right - area.left;
	dist.height = area.bottom - area.top;
	if (Characters)
	{
		if (Characters->size())
		{
			if (SelectedCharacter)
			{
				float i = 1;
				for (auto r : SelectedCharacter->Races)
				{
					gfx->FillRect(D2D1::RectF(area.left, area.top + i * dist.height, area.right, area.bottom + i * dist.height), D2D1::ColorF(0.66f, 0.66f, 0.66f, 1.0f));
					gfx->OutputText(r->Name.c_str(), D2D1::RectF(area.left, area.top + i * dist.height, area.right, area.bottom + i * dist.height), D2D1::ColorF(0.0f,0.0f,0.0f,1.0f),DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					gfx->DrawRect(D2D1::RectF(area.left, area.top + i * dist.height, area.right, area.bottom + i * dist.height), D2D1::ColorF(.7f, .8f, .7f));
					i++;
				}
				gfx->DrawRect(area);
			}
		}
		else
		{
			Characters->push_back(new Character());
			Characters->front()->SetRace(L"Elf");
			Characters->front()->SetSubrace(L"High Elf");
			SelectedCharacter = Characters->front();
			if (Reroll) delete Reroll;
			Reroll = new RerollInteraction(&SelectedCharacter->AbilityScores);
			SelectedCharacter->AbilityScores.SetRace(SelectedCharacter->CharacterRace);
			SelectedCharacter->AbilityScores.SetSubRace(SelectedCharacter->CharacterRace->SelectedSubRace);
		}
	}
}

void InitialStage::UpdateDataBoxes()
{
	if (!SelectedCharacter) return;
	if (DataBoxes.size())
	{
		std::vector<DataBox2> e;
		std::swap(DataBoxes, e);
	}
	if (SelectedCharacter->Classes.size())
	{
		DataBoxes.push_back(DataBox2(D2D1::RectF(1125.0f, 195.0f, 1517.0f, 263.0f), L"ClassLevelBox", SelectedCharacter->Classes.front()->m_GetClassName().c_str(), SelectedCharacter->Classes.front()));
	}
	if (SelectedCharacter->CharacterRace)
	{
		DataBoxes.push_back(DataBox2(D2D1::RectF(1125.0f, 307.0f, 1517.0f, 372.0f), L"RaceBox", SelectedCharacter->CharacterRace->m_GetClassName().c_str(), SelectedCharacter->CharacterRace));
		if (SelectedCharacter->CharacterRace->SelectedSubRace)
			DataBoxes.push_back(DataBox2(D2D1::RectF(1204.0f, 375.0f, 1517.0f, 414.0f), L"SubRaceBox", SelectedCharacter->CharacterRace->SelectedSubRace->m_GetClassName().c_str(), SelectedCharacter->CharacterRace->SelectedSubRace, 0.5f, false, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR));
	}

	DataBoxes.push_back(DataBox2(D2D1::RectF(168.0f, 521.0f, 306.0f, 585.0f), L"Reroll", L"Reroll", Reroll, 0.66f, false, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	
	DataBoxes.push_back(DataBox2(D2D1::RectF(168.0f, 641.0f, 306.0f, 755.0f), L"StrengthBox", SelectedCharacter->GetAbilityScoreW(ABILITYSCORES::Strength).c_str(), &SelectedCharacter->AbilityScores.Strength, 1.0f, false, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	DataBoxes.push_back(DataBox2(D2D1::RectF(180.0f, 780.0f, 290.0f, 830.0f), L"StrengthModBox", SelectedCharacter->GetAbilityModifierW(ABILITYSCORES::Strength).c_str(), &SelectedCharacter->AbilityScores.StrMod, 0.75f, true, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));

	DataBoxes.push_back(DataBox2(D2D1::RectF(168.0f, 940.0f, 306.0f, 1054.0f), L"DexterityBox", SelectedCharacter->GetAbilityScoreW(ABILITYSCORES::Dexterity).c_str(), &SelectedCharacter->AbilityScores.Dexterity, 1.0f, false, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	DataBoxes.push_back(DataBox2(D2D1::RectF(180.0f, 1080.0f, 290.0f, 1130.0f), L"DexterityModBox", SelectedCharacter->GetAbilityModifierW(ABILITYSCORES::Dexterity).c_str(), &SelectedCharacter->AbilityScores.DexMod, 0.75f, true, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));

	DataBoxes.push_back(DataBox2(D2D1::RectF(168.0f, 1237.0f, 306.0f, 1351.0f), L"ConsitutionBox", SelectedCharacter->GetAbilityScoreW(ABILITYSCORES::Constitution).c_str(), &SelectedCharacter->AbilityScores.Constitution, 1.0f, false, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	DataBoxes.push_back(DataBox2(D2D1::RectF(180.0f, 1377.0f, 290.0f, 1427.0f), L"ConstitutionModBox", SelectedCharacter->GetAbilityModifierW(ABILITYSCORES::Constitution).c_str(), &SelectedCharacter->AbilityScores.ConMod, 0.75f, true, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));

	DataBoxes.push_back(DataBox2(D2D1::RectF(168.0f, 1538.0f, 306.0f, 1652.0f), L"IntelligenceBox", SelectedCharacter->GetAbilityScoreW(ABILITYSCORES::Intelligence).c_str(), &SelectedCharacter->AbilityScores.Intelligence, 1.0f, false, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	DataBoxes.push_back(DataBox2(D2D1::RectF(180.0f, 1678.0f, 290.0f, 1728.0f), L"IntelligenceModBox", SelectedCharacter->GetAbilityModifierW(ABILITYSCORES::Intelligence).c_str(), &SelectedCharacter->AbilityScores.IntMod, 0.75f, true, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));

	DataBoxes.push_back(DataBox2(D2D1::RectF(168.0f, 1837.0f, 306.0f, 1950.0f), L"WisdomBox", SelectedCharacter->GetAbilityScoreW(ABILITYSCORES::Wisdom).c_str(), &SelectedCharacter->AbilityScores.Wisdom, 1.0f, false, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	DataBoxes.push_back(DataBox2(D2D1::RectF(180.0f, 1977.0f, 290.0f, 2027.0f), L"WisdomModBox", SelectedCharacter->GetAbilityModifierW(ABILITYSCORES::Wisdom).c_str(), &SelectedCharacter->AbilityScores.WisMod, 0.75f, true, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));

	DataBoxes.push_back(DataBox2(D2D1::RectF(168.0f, 2133.0f, 306.0f, 2247.0f), L"CharismaBox", SelectedCharacter->GetAbilityScoreW(ABILITYSCORES::Charisma).c_str(), &SelectedCharacter->AbilityScores.Charisma, 1.0f, false, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	DataBoxes.push_back(DataBox2(D2D1::RectF(180.0f, 2273.0f, 290.0f, 2323.0f), L"CharismaModBox", SelectedCharacter->GetAbilityModifierW(ABILITYSCORES::Charisma).c_str(), &SelectedCharacter->AbilityScores.ChaMod, 0.75f, true, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));

	//example using Interact
	/*
	Wrapper* w = SelectedCharacter->CharacterRace;
	DataBoxes.front().w = w;
	DataBoxes.front().w->Interact();*/
}

void InitialStage::BuildForm()
{
	if (DataBoxes.empty())
		UpdateDataBoxes();
	if (DataBoxes.empty())
		return;

	for (auto& b : DataBoxes)
	{
		b.Draw(gfx);
	}
	/*
	struct DataBox
	{
		float scale = 1.0f;
		D2D1_RECT_F area;
		std::wstring text;
		DWRITE_TEXT_ALIGNMENT alignment = DWRITE_TEXT_ALIGNMENT_LEADING;
		DWRITE_PARAGRAPH_ALIGNMENT p_alignment = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
		void Draw(D2D1_COLOR_F color = D2D1::ColorF(0.0f,0.0f,0.0f))
		{
			D2D1_MATRIX_3X2_F otransform;
			gfx->GetCompatibleTarget()->GetTransform(&otransform);
			gfx->GetCompatibleTarget()->SetTransform(otransform * D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale, scale), D2D1::Point2F((area.right + area.left) *0.5f, (area.bottom + area.top) * 0.5f)));
			gfx->OutputText(text.c_str(), area, color, alignment, p_alignment);
			gfx->GetCompatibleTarget()->SetTransform(otransform);
		}
		DataBox(D2D1_RECT_F dest, const wchar_t* string, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT p_align = DWRITE_PARAGRAPH_ALIGNMENT_NEAR, float scale = 1.0f)
		{
			this->scale = scale;
			alignment = align;
			p_alignment = p_align;
			area.top = dest.top;
			area.left = dest.left;
			area.right = dest.right;
			area.bottom = dest.bottom;
			text = std::wstring(string, string + wcslen(string));
		}
	};
	std::vector<D2D1_RECT_F> SelectBoxes;
	std::vector<DataBox> DB;
	D2D1_RECT_F ClassLevelBox = D2D1::RectF(1125.0f, 195.0f, 1517.0f, 263.0f);
	SelectBoxes.push_back(ClassLevelBox);
	//if(SelectedCharacter) if (SelectedCharacter->Classes.size())
	//	DB.push_back(DataBox(ClassLevelBox, SelectedCharacter->Classes.front()->m_GetClassName().c_str()));
	D2D1_RECT_F RaceBox = D2D1::RectF(1125.0f, 307.0f, 1517.0f, 372.0f);
	SelectBoxes.push_back(RaceBox);
	//if (SelectedCharacter) if (SelectedCharacter->CharacterRace)
	//	DB.push_back(DataBox(RaceBox, SelectedCharacter->CharacterRace->m_GetClassName().c_str()));
	D2D1_RECT_F SubRaceBox = D2D1::RectF(1204.0f, 375.0f, 1517.0f, 414.0f);
	SelectBoxes.push_back(SubRaceBox);
	//if (SelectedCharacter) if (SelectedCharacter->CharacterRace) if (SelectedCharacter->CharacterRace->SelectedSubRace)
	//	DB.push_back(DataBox(SubRaceBox, SelectedCharacter->CharacterRace->SelectedSubRace->m_GetClassName().c_str()));
	D2D1_RECT_F StrengthBox = D2D1::RectF(168.0f, 641.0f, 306.0f, 755.0f);
	SelectBoxes.push_back(StrengthBox);
	if (SelectedCharacter)
		DB.push_back(DataBox(StrengthBox, std::to_wstring(SelectedCharacter->GetAbilityScores().Strength).c_str(), DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	D2D1_RECT_F StrengthModBox = D2D1::RectF(180.0f, 780.0f, 290.0f, 830.0f);
	if (SelectedCharacter)
	{
		std::wstring o = L"+";
		o.append(std::to_wstring(SelectedCharacter->GetAbilityModifier(ABILITYSCORES::Strength)).c_str());
		DB.push_back(DataBox(StrengthModBox, o.c_str(), DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 0.75f));
	}
	SelectBoxes.push_back(StrengthModBox);
	D2D1_RECT_F DexterityBox = D2D1::RectF(168.0f, 940.0f, 306.0f, 1054.0f);
	D2D1_RECT_F DexterityModBox = D2D1::RectF(180.0f, 1080.0f, 290.0f, 1130.0f);
	if (SelectedCharacter)
	{
		std::wstring o = L"+";
		o.append(std::to_wstring(SelectedCharacter->GetAbilityModifier(ABILITYSCORES::Dexterity)).c_str());
		DB.push_back(DataBox(DexterityModBox, o.c_str(), DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 0.75f));
	}
	SelectBoxes.push_back(DexterityBox);
	SelectBoxes.push_back(DexterityModBox);
	if (SelectedCharacter)
		DB.push_back(DataBox(DexterityBox, std::to_wstring(SelectedCharacter->GetAbilityScores().Dexterity).c_str(), DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	D2D1_RECT_F ConstitutionBox = D2D1::RectF(168.0f, 1237.0f, 306.0f, 1351.0f);
	D2D1_RECT_F ConstitutionModBox = D2D1::RectF(180.0f, 1377.0f, 290.0f, 1427.0f);
	if (SelectedCharacter)
	{
		std::wstring o = L"+";
		o.append(std::to_wstring(SelectedCharacter->GetAbilityModifier(ABILITYSCORES::Constitution)).c_str());
		DB.push_back(DataBox(ConstitutionModBox, o.c_str(), DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 0.75f));
	}
	SelectBoxes.push_back(ConstitutionBox);
	SelectBoxes.push_back(ConstitutionModBox);
	if (SelectedCharacter)
		DB.push_back(DataBox(ConstitutionBox, std::to_wstring(SelectedCharacter->GetAbilityScores().Constitution).c_str(), DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	D2D1_RECT_F IntelligenceBox = D2D1::RectF(168.0f, 1538.0f, 306.0f, 1652.0f);
	SelectBoxes.push_back(IntelligenceBox);
	D2D1_RECT_F WisdomBox = D2D1::RectF(168.0f, 1837.0f, 306.0f, 1950.0f);
	if (SelectedCharacter)
		DB.push_back(DataBox(IntelligenceBox, std::to_wstring(SelectedCharacter->GetAbilityScores().Intelligence).c_str(), DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	SelectBoxes.push_back(WisdomBox);
	if (SelectedCharacter)
		DB.push_back(DataBox(WisdomBox, std::to_wstring(SelectedCharacter->GetAbilityScores().Wisdom).c_str(), DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	D2D1_RECT_F CharismaBox = D2D1::RectF(168.0f, 2133.0f, 306.0f, 2247.0f);
	if (SelectedCharacter)
		DB.push_back(DataBox(CharismaBox, std::to_wstring(SelectedCharacter->GetAbilityScores().Charisma).c_str(), DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	SelectBoxes.push_back(CharismaBox);

	for (auto& r : SelectBoxes)
	{
		gfx->FillRect(r, D2D1::ColorF(0.0f, 0.0f, 1.0f, 0.25f));
		gfx->DrawRect(r);
	}
	for (auto& w : DB)
		w.Draw();
	*/
	if (Characters)
	{
		if (Characters->size())
		{
			if (SelectedCharacter)
			{
				if (SelectedCharacter->Classes.size())
				{
					//gfx->OutputText(SelectedCharacter->Classes.front()->m_GetClassName().c_str(), ClassLevelBox);
				}
				if (SelectedCharacter->CharacterRace && !bShowDropDown)
				{
					//gfx->OutputText(SelectedCharacter->CharacterRace->Name.c_str(), RaceBox);
					//if (SelectedCharacter->CharacterRace->SelectedSubRace)
					//	gfx->OutputTextSmall(SelectedCharacter->CharacterRace->SelectedSubRace->Name.c_str(), SubRaceBox, D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					//else
					//	gfx->OutputTextSmall(L"Select Subrace", SubRaceBox, D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				}
				else
				{
				//	gfx->OutputText(L"Select Race", RaceBox);
				}
			}
			if (bShowDropDown)
			{
				//ShowDD(Characters->front()->Races, RaceBox);
				//if (Characters->front()->Classes.size()) ShowDD(Characters->front()->Classes, ClassLevelBox);
			}
		}
	}
	/*
	gfx->FillRect(SubRaceBox, D2D1::ColorF(0.0f, 0.0f, 1.0f, 0.25f));
	gfx->DrawRect(SubRaceBox);
	gfx->FillRect(RaceBox, D2D1::ColorF(0.0f, 0.0f, 1.0f, 0.25f));
	gfx->DrawRect(RaceBox);*/
	/*
	gfx->OutputText(L"Race: ", D2D1::RectF(0, 0, 150, 32));
	gfx->OutputText(L"Subrace: ", D2D1::RectF(0, 33, 150, 65));
	if (bShowDropDown) ShowDropDown(D2D1::RectF(150, 0, 300, 32));
	else if (Characters)
	{
		if (Characters->size())
		{
			if (SelectedCharacter)
			{
				if (SelectedCharacter->CharacterRace)
				{
					gfx->OutputTextSmall(SelectedCharacter->CharacterRace->Name.c_str(), D2D1::RectF(150, 0, 300, 32));
					if (SelectedCharacter->CharacterRace->SelectedSubRace)
					{
						gfx->OutputTextSmall(SelectedCharacter->CharacterRace->SelectedSubRace->Name.c_str(), D2D1::RectF(150, 33, 300, 65));
					}
					else
					{
						gfx->OutputTextSmall(L"Select Subrace", D2D1::RectF(150, 33, 250, 65));
					}
				}
			}
			else
			{
				gfx->OutputTextSmall(L"Select Race", D2D1::RectF(150, 0, 250, 32));
			}
		}
		else
		{
			gfx->OutputTextSmall(L"Select Race", D2D1::RectF(150, 0, 300, 32));
			gfx->OutputTextSmall(L"Select Subrace", D2D1::RectF(150, 33, 300, 65));
		}
	}
/*	gfx->FillRect(D2D1::RectF(150, 0, 250, 32), D2D1::ColorF(.66f,.66f,.66f,.5f));
	gfx->DrawRect(D2D1::RectF(150, 0, 250, 32));*/
	/*gfx->DrawLine(D2D1::Point2F(150, 32), D2D1::Point2F(300, 32));
	gfx->DrawLine(D2D1::Point2F(150, 65), D2D1::Point2F(300, 65));*/
}