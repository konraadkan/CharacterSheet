#pragma once
#include "wrapper.h"

class IncreaseDecrease : public Wrapper
{
protected:
	std::wstring Name;
public:
	IncreaseDecrease(std::wstring name) { Name = name; }
	void Interact() override {}
	std::wstring GetOutput() override { return Name; }
};