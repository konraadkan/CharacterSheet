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
	static void Update(UINT msg, WPARAM wParam, LPARAM lParam);
	static void EmptyMessages();
	static void UpdateTimer();
	static HWND hWnd;
	static MSG msg;
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
	static D2D1_RECT_F GetWindowSize()
	{
		if (!hWnd) return {};
		RECT r = {};
		GetWindowRect(hWnd, &r);
		r.right -= r.left;
		r.left = 0;
		r.bottom -= r.top;
		r.top = 0;
		return D2D1::RectF((float)r.left, (float)r.top, (float)r.right, (float)r.bottom);
	}
};