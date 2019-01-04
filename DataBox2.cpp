#include "DataBox2.h"

DataBox2::DataBox2(D2D1_RECT_F dest,const wchar_t* name, const wchar_t* data, Wrapper* w, float scale, bool hideborder, DWRITE_TEXT_ALIGNMENT align, DWRITE_PARAGRAPH_ALIGNMENT p_align)
{
	Area.left = dest.left;
	Area.top = dest.top;
	Area.right = dest.right;
	Area.bottom = dest.bottom;
	this->scale = scale;
	invScale = 1 / scale;
	alignment = align;
	p_alignment = p_align;
	output = std::wstring(data, data + wcslen(data));
	Name = std::wstring(name, name + wcslen(name));
	bHideBorder = hideborder;
	wrapper = w;
}

DataBox2::~DataBox2()
{

}

void DataBox2::Draw(Graphics* gfx, D2D1_COLOR_F color)
{
	if (output.empty()) return;
	D2D1_MATRIX_3X2_F otransform;

	if (bHighlight)
	{
		gfx->FillRect(Area, D2D1::ColorF(0.66f, 0.66f, 0.66f, 0.8f));
	}

	D2D1_RECT_F trueArea;
	trueArea.left = Area.left;
	trueArea.top = Area.top;
	trueArea.right = trueArea.left + (Area.right - Area.left) * invScale;
	trueArea.bottom = trueArea.top + (Area.bottom - Area.top) * invScale;
	gfx->GetCompatibleTarget()->GetTransform(&otransform);
	gfx->GetCompatibleTarget()->SetTransform(otransform * D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale, scale), D2D1::Point2F(Area.left, Area.top)));
	if (wrapper)
		gfx->OutputText(wrapper->GetOutput().c_str(), trueArea, color, alignment, p_alignment);
	else
		gfx->OutputText(output.c_str(), trueArea, color, alignment, p_alignment);
	gfx->GetCompatibleTarget()->SetTransform(otransform);
	
	if (!bHideBorder)
	{
		gfx->DrawRect(Area);
	}	
}

bool DataBox2::PointInRect(D2D1_POINT_2F p)
{
	if (p.x < Area.left) return false;
	if (p.x > Area.right) return false;
	if (p.y < Area.top) return false;
	if (p.y > Area.bottom) return false;
	return true;
}

void DataBox2::Interact()
{
	if (wrapper) wrapper->Interact();
}