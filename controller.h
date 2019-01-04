#pragma once

#include <vector>
#include "Character.h"
#include "hptimer.h"
#include "Stage.h"
#include "graphics.h"

class Controller
{
protected:
	static std::vector<Character*> Characters;
public:
	static Stage* CurrentStage;
	static bool Run;
	static bool Loading;
	static HPTimer* Timer;
	static void Init(HWND hwnd);
	static void Render();
	static void Update();
	static void UpdateTimer();
	static HWND hWnd;
	static void SwitchStage(Stage* stage);
	static void Cleanup();
	static D2D1_POINT_2F p;
	static D2D1_POINT_2F GetMousePositionForCurrentDpi(LPARAM lParam, ID2D1Factory* factory)
	{
		static D2D1_POINT_2F dpi = { 96,96 };	//default dpi

		factory->GetDesktopDpi(&dpi.x, &dpi.y);

		return D2D1::Point2F(static_cast<int>(static_cast<short>(LOWORD(lParam))) * 96 / dpi.x,
			static_cast<int>(static_cast<short>(HIWORD(lParam))) * 96 / dpi.y);
	}
};