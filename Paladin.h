#pragma once
#include "JobClass.h"

class Paladin : public JobClass
{
public:
	Paladin(ABILITIES& abs, unsigned long startingLevel = 1);
	~Paladin() {}
	void IncreaseLevel(unsigned long Amount = 0) override { Level += Amount; }
	void DecreaseLevel(unsigned long Amount = 0) override { Level = (Level - Amount < 0) ? 0 : Level - Amount; }
};