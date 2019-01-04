#pragma once
#include "JobClass.h"

class Fighter : public JobClass
{
public:
	Fighter(ABILITIES& abs, unsigned long startingLevel = 1);
	~Fighter() {}
	void IncreaseLevel(unsigned long Amount = 0) override { Level += Amount; }
	void DecreaseLevel(unsigned long Amount = 0) override { Level = (Level - Amount < 0) ? 0 : Level - Amount; }
};