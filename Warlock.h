#pragma once
#include "JobClass.h"

class Warlock : public JobClass
{
public:
	Warlock(ABILITIES& abs, unsigned long startingLevel = 1);
	~Warlock() {}
	void IncreaseLevel(unsigned long Amount = 0) override { Level += Amount; }
	void DecreaseLevel(unsigned long Amount = 0) override { Level = (Level - Amount < 0) ? 0 : Level - Amount; }
};