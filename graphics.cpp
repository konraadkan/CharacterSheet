#include "Graphics.h"

Graphics::Graphics()
{
	m_Factory = NULL;
	m_RenderTarget = NULL;
	m_Brush = NULL;
}

Graphics::~Graphics()
{
	if (m_Factory) m_Factory->Release();
	if (m_RenderTarget) m_RenderTarget->Release();
	if (m_WriteFactory) m_WriteFactory->Release();
	if (m_WriteFormat) m_WriteFormat->Release();
	if (m_Brush) m_Brush->Release();
	if (m_WriteFormatSmall) m_WriteFormatSmall->Release();
	if (pCompatibleTarget) pCompatibleTarget->Release();
}

bool Graphics::Init(HWND hWnd)
{
	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Factory);
	if (result != S_OK) return false;

	RECT rect;
	GetClientRect(hWnd, &rect);

	result = m_Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rect.right, rect.bottom), D2D1_PRESENT_OPTIONS_NONE), &m_RenderTarget);
	if (result != S_OK) return false;

	result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&m_WriteFactory));
	if (result != S_OK) return false;

	result = m_WriteFactory->CreateTextFormat(L"Arial", NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 64.0f, L"en-us", &m_WriteFormat);
	if (result != S_OK) return false;

	result = m_WriteFactory->CreateTextFormat(L"Arial", NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 32.0f, L"en-us", &m_WriteFormatSmall);
	if (result != S_OK) return false;

	result = m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f), &m_Brush);
	if (result != S_OK) return false;

	result = m_RenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(2550.0f,3300.0f), &pCompatibleTarget);
	if (result != S_OK) return false;
	return true;
}

void Graphics::ClearScreen(D2D1_COLOR_F color)
{
	m_RenderTarget->Clear(color);
	pCompatibleTarget->Clear(color);
}

bool Graphics::DrawCircle(D2D1_POINT_2F center, float radius, D2D1_COLOR_F color, float thickness)
{
	if (!m_Brush) return false;
	m_Brush->SetColor(color);
	//m_RenderTarget->DrawEllipse(D2D1::Ellipse(center, radius, radius), m_Brush, thickness);
	pCompatibleTarget->DrawEllipse(D2D1::Ellipse(center, radius, radius), m_Brush, thickness);
	return true;
}

bool Graphics::FillCircle(D2D1_POINT_2F center, float radius, D2D1_COLOR_F color)
{
	if (!m_Brush) return false;
	m_Brush->SetColor(color);
	//m_RenderTarget->FillEllipse(D2D1::Ellipse(center, radius, radius), m_Brush);
	pCompatibleTarget->FillEllipse(D2D1::Ellipse(center, radius, radius), m_Brush);
	return true;
}

bool Graphics::DrawLine(D2D1_POINT_2F p1, D2D1_POINT_2F p2, D2D1_COLOR_F color, float thickness)
{
	if (!m_Brush) return false;
	m_Brush->SetColor(color);
	//m_RenderTarget->DrawLine(p1, p2, m_Brush, thickness);
	pCompatibleTarget->DrawLine(p1, p2, m_Brush, thickness);
	return true;
}

bool Graphics::DrawRect(D2D1_RECT_F area, D2D1_COLOR_F color, float thickness)
{
	if (!m_Brush) return false;
	m_Brush->SetColor(color);
	//m_RenderTarget->DrawRectangle(area, m_Brush, thickness);
	pCompatibleTarget->DrawRectangle(area, m_Brush, thickness);
	return true;
}


bool Graphics::FillRect(D2D1_RECT_F area, D2D1_COLOR_F color)
{
	if (!m_Brush) return false;
	m_Brush->SetColor(color);
	//m_RenderTarget->FillRectangle(area, m_Brush);
	pCompatibleTarget->FillRectangle(area, m_Brush);
	return true;
}

bool Graphics::OutputText(const wchar_t* text, D2D1_RECT_F targetArea, D2D1_COLOR_F color, DWRITE_TEXT_ALIGNMENT alignment, DWRITE_PARAGRAPH_ALIGNMENT p_alignment)
{
	if (!m_Brush) return false;
	m_Brush->SetColor(color);

	DWRITE_PARAGRAPH_ALIGNMENT p = m_WriteFormat->GetParagraphAlignment();
	m_WriteFormat->SetParagraphAlignment(p_alignment);
	m_WriteFormat->SetTextAlignment(alignment);

	//m_RenderTarget->DrawTextA(text, lstrlenW(text), m_WriteFormat, targetArea, m_Brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
	pCompatibleTarget->DrawTextA(text, lstrlenW(text), m_WriteFormat, targetArea, m_Brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);

	m_WriteFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	m_WriteFormat->SetParagraphAlignment(p);
	return true;
}

bool Graphics::OutputTextRenderTarget(const wchar_t* text, D2D1_RECT_F targetArea, D2D1_COLOR_F color, DWRITE_TEXT_ALIGNMENT alignment, DWRITE_PARAGRAPH_ALIGNMENT p_alignment)
{
	if (!m_Brush) return false;
	m_Brush->SetColor(color);

	DWRITE_PARAGRAPH_ALIGNMENT p = m_WriteFormat->GetParagraphAlignment();
	m_WriteFormat->SetParagraphAlignment(p_alignment);
	m_WriteFormat->SetTextAlignment(alignment);

	m_RenderTarget->DrawTextA(text, lstrlenW(text), m_WriteFormat, targetArea, m_Brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
	//pCompatibleTarget->DrawTextA(text, lstrlenW(text), m_WriteFormat, targetArea, m_Brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);

	m_WriteFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	m_WriteFormat->SetParagraphAlignment(p);
	return true;
}

bool Graphics::OutputTextSmall(const wchar_t* text, D2D1_RECT_F targetArea, D2D1_COLOR_F color, DWRITE_TEXT_ALIGNMENT alignment, DWRITE_PARAGRAPH_ALIGNMENT p_alignment)
{
	if (!m_Brush) return false;
	m_Brush->SetColor(color);

	DWRITE_PARAGRAPH_ALIGNMENT p = m_WriteFormat->GetParagraphAlignment();
	m_WriteFormatSmall->SetParagraphAlignment(p_alignment);
	m_WriteFormatSmall->SetTextAlignment(alignment);

	//m_RenderTarget->DrawTextA(text, lstrlenW(text), m_WriteFormatSmall, targetArea, m_Brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
	pCompatibleTarget->DrawTextA(text, lstrlenW(text), m_WriteFormatSmall, targetArea, m_Brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);

	m_WriteFormatSmall->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	m_WriteFormatSmall->SetParagraphAlignment(p);
	return true;
}