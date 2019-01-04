#include "Sprite.h"
#include <string>

Sprite::Sprite(const wchar_t* filepath, Graphics* graphics)
{
	gfx = graphics;
	FILE* file = NULL;
	errno_t err = _wfopen_s(&file, filepath, L"rb");
	if (!err)
	{
		fseek(file, 0, SEEK_END);
		size_t bufferlen = ftell(file);
		fseek(file, 0, SEEK_SET);
		char* buffer = new char[bufferlen];
		fread(buffer, bufferlen, 1, file);
		fclose(file);
		InitFromMemory(buffer, bufferlen);
		delete[] buffer;
		buffer = NULL;
	}	
}

Sprite::Sprite(char* buffer, size_t bufferlen, Graphics* graphics)
{
	gfx = graphics;
	InitFromMemory(buffer, bufferlen);
}

bool Sprite::InitFromMemory(char* buffer, size_t bufferlen)
{
	if (!gfx) return false;
	bmp = NULL;
	HRESULT hr = NULL;
	unsigned long MaxBitmapSize = gfx->GetMaxBitmapSize();

	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&wicFactory);
	if (hr != S_OK)
	{
		MessageBoxW(NULL, L"Failed to create wicFactory.", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//create stream
	IWICStream* pIWICStream = NULL;
	hr = wicFactory->CreateStream(&pIWICStream);
	if (hr != S_OK)
	{
		MessageBoxW(NULL, L"Failed to create stream.", L"Error", MB_OK | MB_ICONERROR);
		wicFactory->Release();
		return false;
	}
	pIWICStream->InitializeFromMemory(reinterpret_cast<BYTE*>(buffer), (DWORD)bufferlen);
	if (hr != S_OK)
	{
		MessageBoxW(NULL, L"Failed to initialize from memory.", L"Error", MB_OK | MB_ICONERROR);
		SafeRelease(&pIWICStream);
		SafeRelease(&wicFactory);
		return false;
	}

	//create decoder
	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromStream(pIWICStream, NULL, WICDecodeMetadataCacheOnLoad, &wicDecoder);
	if (hr != S_OK)
	{
		MessageBoxW(NULL, L"Failed to create wic decoder.", L"Error", MB_OK | MB_ICONERROR);
		SafeRelease(&pIWICStream);
		SafeRelease(&wicFactory);
		SafeRelease(&pIWICStream);
		return false;
	}

	//read frame from image
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);	//get first frame from the image. ignoring any following frames
	if (hr != S_OK)
	{
		MessageBoxW(NULL, L"Failed to get frame from image.", L"Error", MB_OK | MB_ICONERROR);
		SafeRelease(&wicDecoder);
		SafeRelease(&pIWICStream);
		SafeRelease(&wicFactory);
		SafeRelease(&pIWICStream);
		return false;
	}
	unsigned int framewidth, frameheight;
	wicFrame->GetSize(&framewidth, &frameheight);
	if ((framewidth > MaxBitmapSize) || (frameheight > MaxBitmapSize))
	{
		std::wstring errmsg = L"Failed to load. Bitmap size is ";
		errmsg.append(std::to_wstring(framewidth));
		errmsg.append(L" x ");
		errmsg.append(std::to_wstring(frameheight));
		errmsg.append(L". Maximum supported size is ");
		errmsg.append(std::to_wstring(MaxBitmapSize));
		errmsg.append(L" x ");
		errmsg.append(std::to_wstring(MaxBitmapSize));
		errmsg.push_back('.');
		MessageBoxW(NULL, errmsg.c_str(), L"Error", MB_OK | MB_ICONERROR);
		gfx = NULL;
		bmp = NULL;
		SafeRelease(&wicFactory);
		SafeRelease(&wicDecoder);
		SafeRelease(&wicFrame);
		SafeRelease(&pIWICStream);
		return false;
	}

	//create converter
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);
	if (hr != S_OK)
	{
		MessageBoxW(NULL, L"Failed to create format converter.", L"Error", MB_OK | MB_ICONERROR);
		gfx = NULL;
		bmp = NULL;
		SafeRelease(&wicFactory);
		SafeRelease(&wicDecoder);
		SafeRelease(&wicFrame);
		SafeRelease(&pIWICStream);
		return false;
	}

	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);
	if (hr != S_OK)
	{
		MessageBoxW(NULL, L"Failed to initialize converter.", L"Error", MB_OK | MB_ICONERROR);
		gfx = NULL;
		bmp = NULL;
		SafeRelease(&wicFactory);
		SafeRelease(&wicDecoder);
		SafeRelease(&wicFrame);
		SafeRelease(&wicConverter);
		SafeRelease(&pIWICStream);
		return false;
	}

	hr = gfx->GetCompatibleTarget()->CreateBitmapFromWicBitmap(wicConverter, NULL, &bmp);
	if (hr != S_OK)
	{
		MessageBoxW(NULL, L"Failed to create bitmap from wic.", L"Error", MB_OK | MB_ICONERROR);
		gfx = NULL;
		bmp = NULL;
		SafeRelease(&wicFactory);
		SafeRelease(&wicDecoder);
		SafeRelease(&wicFrame);
		SafeRelease(&wicConverter);
		SafeRelease(&pIWICStream);
		return false;
	}
	SpriteSize.height = bmp->GetSize().height;
	SpriteSize.width = bmp->GetSize().width;

	AspectRatio = SpriteSize.width / SpriteSize.height;

	SafeRelease(&wicConverter);
	SafeRelease(&wicFrame);
	SafeRelease(&wicDecoder);
	SafeRelease(&pIWICStream);
	SafeRelease(&wicFactory);
	AddFrame(D2D1::RectF(0.0f, 0.0f, SpriteSize.width, SpriteSize.height));	//default frame
	return true;
}

Sprite::~Sprite()
{
	SafeRelease(&bmp);
}

void Sprite::Draw(D2D1_RECT_F dest, D2D1_RECT_F src, float transparency)
{
	if (!bmp) return;
	gfx->GetCompatibleTarget()->DrawBitmap(
		bmp,
		dest,
		transparency,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		src
	);
}

void Sprite::DrawFrame(D2D1_POINT_2F dest, float transparency)
{
	if (!bmp) return;
	if (!gfx) return;
	if (Frames.empty()) return;
	D2D1_RECT_F truedest = {};
	truedest.left = dest.x;
	truedest.top = dest.y;
	truedest.right = truedest.left + Frames.front().right - Frames.front().left;
	truedest.bottom = truedest.top + Frames.front().bottom - Frames.front().top;
	gfx->GetCompatibleTarget()->DrawBitmap(
		bmp,
		truedest,
		transparency,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		Frames.front()
	);
	gfx->DrawRect(truedest);
}

void Sprite::Draw(D2D1_RECT_F dest, bool keepaspect, float transparency)
{
	if (!keepaspect)
	{
		Draw(dest, transparency);
		return;
	}
	D2D1_RECT_F truedest = {};
	truedest.left = dest.left;
	truedest.top = dest.top;
	truedest.bottom = dest.bottom;
	truedest.right = dest.bottom * (float)AspectRatio;
	Draw(truedest, transparency);
}

void Sprite::Draw(D2D1_RECT_F dest, float transparency)
{
	if (!bmp) return;
	gfx->GetCompatibleTarget()->DrawBitmap(
		bmp,
		dest,
		transparency,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(0.0f, 0.0f, SpriteSize.width, SpriteSize.height)
	);
}

void Sprite::DrawFrame(D2D1_RECT_F dest, float transparency)
{
	if (!bmp) return;
	if (Frames.empty()) return;
	Draw(dest, Frames.front(), transparency);
}

void Sprite::UpdateDrawInfo(double currentTime)
{
	if (!Frames.size())
	{
		AddFrame({ 0.0f,0.0f,SpriteSize.width,SpriteSize.height });
	}

	if (currentTime - LastTime >= FrameSpeed)
	{
		LastTime = currentTime;
		NextFrame();
	}
}

void Sprite::AddFrame(D2D1_RECT_F frame)
{
	Frames.push(frame);
}

void Sprite::NextFrame()
{
	D2D1_RECT_F temp = Frames.front();
	Frames.pop();
	Frames.push(temp);
}

void Sprite::EmptyRectQueue(std::queue<D2D1_RECT_F>& q)
{
	std::queue<D2D1_RECT_F> empty;
	std::swap(q, empty);
}