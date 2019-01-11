#pragma once
#include "Stage.h"
#include "sprite.h"
#include "databox2.h"
#include "RerollInteraction.h"
#include "classlist.h"
#include "controller.h"

class InitialStage : public Stage
{
private:
	std::vector<Character*>* Characters;
	Character* SelectedCharacter = NULL;
	void ShowDropDown(D2D1_RECT_F area);
	template<class T, class A> void ShowDD(std::vector<T, A>const& vec, D2D1_RECT_F area);
	std::vector<DataBox2> DataBoxes;
	void BuildForm();
	bool bShowDropDown = false;
	bool bButtonUp = true;
	bool keydown = false;
	bool twoseconds = false;
	double ctime = 0.0;
	double ptime = 0.0;
	Sprite* CharacterSheet = NULL;
	float scale = 1.0f;
	float ScalingSpeed = 0.33f;
	float TranslationSpeed = 250.0f;
	D2D1_SIZE_F Translation = {};
	void UpdateDataBoxes();
	D2D1_POINT_2F* p = NULL;
	D2D1_POINT_2F pTransformed = {};
	D2D1_POINT_2F pCenter = D2D1::Point2F(Controller::GetWindowSize().right * 0.5f, Controller::GetWindowSize().bottom * 0.5f);
	RerollInteraction* Reroll = NULL;
	TextHoldingBox* CharacterNameBox = NULL;
	TextHoldingBox* PlayerNameBox = NULL;
	ClassContainer* ClassOptions = NULL;
public:
	InitialStage(Graphics* graphics = NULL, D2D1_POINT_2F* P = NULL);
	~InitialStage();
	void Load() override;
	void Load(std::vector<Character*>& characters) override;
	void Render() override;
	void Unload() override;
	void Update(float delta) override;
};