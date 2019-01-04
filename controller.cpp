#include "controller.h"

bool Controller::Run = true;
bool Controller::Loading = false;
HPTimer* Controller::Timer = NULL;
HWND Controller::hWnd = NULL;
Stage* Controller::CurrentStage = NULL;
std::vector<Character*> Controller::Characters;
D2D1_POINT_2F Controller::p = {};


void Controller::Init(HWND hwnd)
{
	hWnd = hwnd;
	Timer = new HPTimer();
	Run = true;
	Loading = false;
	Characters.push_back(new Character());
}

void Controller::Render()
{
	if (Loading) return;
	if (CurrentStage) CurrentStage->Render();
}

void Controller::Update()
{
	if (CurrentStage) CurrentStage->Update((float)Timer->GetTimeDelta());
}

void Controller::UpdateTimer()
{
	if (Timer) Timer->Update();
}

void Controller::SwitchStage(Stage* stage)
{
	Loading = true;
	if (CurrentStage)
	{
		CurrentStage->Unload();
		delete CurrentStage;
	}
	CurrentStage = stage;
	CurrentStage->Load(Controller::Characters);
	Loading = false;
}

void Controller::Cleanup()
{
	if (CurrentStage)
	{
		CurrentStage->Unload();
		CurrentStage = NULL;
	}
	if (Timer)
	{
		delete Timer;
		Timer = NULL;
	}
	while (Characters.size())
	{
		if (Characters.back()) delete Characters.back();
		Characters.back() = NULL;
		Characters.pop_back();
	}
}