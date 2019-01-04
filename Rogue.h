#pragma once
#include "JobClass.h"

class Rogue : public JobClass
{
public:
	Rogue(ABILITIES& abs, unsigned long startingLevel = 1);
	~Rogue() {}
	void IncreaseLevel(unsigned long Amount = 0) override { Level += Amount; }
	void DecreaseLevel(unsigned long Amount = 0) override { Level = (Level - Amount < 0) ? 0 : Level - Amount; }
};