#pragma once
#include "JobClass.h"

class Monk : public JobClass
{
public:
	Monk(ABILITIES& abs, unsigned long startingLevel = 1);
	~Monk() {}
	void IncreaseLevel(unsigned long Amount = 0) override { Level += Amount; }
	void DecreaseLevel(unsigned long Amount = 0) override { Level = (Level - Amount < 0) ? 0 : Level - Amount; }
};