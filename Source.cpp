#include <Windows.h>
#include <iostream>
#include <cstdio>
#include "Character.h"
#include "controller.h"
#include "InitialStage.h"
#include "Sprite.h"
#define MYCLASSNAME "dndthing"
#define MYWINDOWNAME "window"

static float WINDOW_WIDTH = 1920.0f;
static float WINDOW_HEIGHT = 1080.0f;

LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_QUIT || msg == WM_DESTROY)
	{
		Controller::Run = false;
		Controller::Cleanup();
		PostQuitMessage(0);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPWSTR cmd, int iCmdShow)
{
	WNDCLASSEX wndClass = {};
	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = wndProc;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszClassName = MYCLASSNAME;
	RegisterClassEx(&wndClass);

	RECT rect = { 0, 0, (long)WINDOW_WIDTH, (long)WINDOW_HEIGHT };
	RECT desktop = {};

	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);

	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, true, WS_EX_OVERLAPPEDWINDOW);
	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, MYCLASSNAME, MYWINDOWNAME, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, (desktop.right / 2) - ((long)WINDOW_WIDTH / 2), (desktop.bottom / 2) - ((long)WINDOW_HEIGHT / 2), rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	MSG msg = {};

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	Graphics* gfx = new Graphics();
	if (!gfx->Init(hWnd))
	{
		delete gfx;
		MessageBoxW(NULL, L"Failed to initialize graphics class.", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}
	Controller::Init(hWnd);
	Controller::SwitchStage(new InitialStage(gfx, &Controller::p));

	while (Controller::Run)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT || msg.message == WM_DESTROY)
				Controller::Run = false;
		}
		else
		{
			Controller::Update();

			gfx->BeginDraw();
			Controller::Render();
			gfx->EndDraw();

			Controller::UpdateTimer();
		}
		Controller::p = Controller::GetMousePositionForCurrentDpi(msg.lParam, gfx->GetFactory());
	}
	Controller::Cleanup();
	delete gfx;
	return 0;
}

/************ old test main
int main()
{
	std::cout << "This is a temporary way to simply view things are working correctly.\nWill eventually add graphics, hopefully.\n";

	Character* c = new Character();

	c->GenerateAbilityScores();
	c->IncreaseLevel(CLASS::Barbarian, 7);
	/*c->IncreaseLevel(CLASS::Monk);
	c->IncreaseLevel(CLASS::Paladin);
	c->IncreaseLevel(CLASS::Barbarian);
	c->IncreaseLevel(CLASS::Other);*/

	/*c->Classes[0]->SetAbilityPointers(c->AbilityScores);

	std::cout << "\n\n" << c->GetAbilityScores().Strength << ' ' << c->GetAbilityScores().Dexterity << ' ' << c->GetAbilityScores().Constitution << ' ' << c->GetAbilityScores().Intelligence << ' ' << c->GetAbilityScores().Wisdom << ' ' << c->GetAbilityScores().Charisma << '\n';
	//c->Classes[0]->Features[0].Update(6);
	for (auto& t : c->Skills)
		std::wcout << t.Name.c_str() << ": " << c->GetSkillModifier(t.ID) << '\n';
	if (c->Classes[0]->Features.size())
		for (auto f : c->Classes[0]->Features)
		{
			std::wcout.flush();
			f.OutputDetails(); std::cout << std::endl;
		}

	std::cout << "Total Levels: " << c->GetLevels() << std::endl;
	for (auto& a : c->Classes)
		a->ShowStuff();
	std::cout << "\n\nMaxHP: " << c->GetMaximumHP() << " conmod: " << c->GetAbilityModifier(ABILITYSCORES::Constitution) << '\n';
	delete c;
	system("Pause");
	return 0;
}*/