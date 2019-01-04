#pragma once
#include <wincodec.h>
#include <queue>
#include "graphics.h"

class Sprite
{
private:
	template<class T> void SafeRelease(T **ppT)
	{
		if (*ppT)
		{
			(*ppT)->Release();
			*ppT = NULL;
		}
	}
private:
	double LastTime = 0.0;
	double FrameSpeed = 0.33;
	D2D1_SIZE_F SpriteSize = {};
protected:
	Graphics * gfx = NULL;
	ID2D1Bitmap* bmp = NULL;
public:
	double AspectRatio = 0.0;

	Sprite(const wchar_t* filepath, Graphics* graphics);
	Sprite(char* buffer, size_t bufferlen, Graphics* graphics);
	~Sprite();
	bool InitFromMemory(char* buffer, size_t bufferlen);

	void Draw(D2D1_RECT_F dest, D2D1_RECT_F src, float transparency = 1.0f);
	void Draw(D2D1_RECT_F dest, float transparency = 1.0f);
	void Draw(D2D1_RECT_F dest, bool keepaspect = false, float transparency = 1.0f);
	void DrawFrame(D2D1_RECT_F dest, float transparency = 1.0f);
	void DrawFrame(D2D1_POINT_2F dest, float transparency = 1.0f);
	void UpdateDrawInfo(double currentTime);

	void SetFrameSpeed(double speed) { FrameSpeed = speed; }
	void AddFrame(D2D1_RECT_F frame);
	void NextFrame();

	std::queue<D2D1_RECT_F> Frames;
	void EmptyRectQueue(std::queue<D2D1_RECT_F>& q);

	D2D1_POINT_2F GetCenter()
	{
		return D2D1::Point2F(SpriteSize.width * 0.5f, SpriteSize.height * 0.5f);
	}
};