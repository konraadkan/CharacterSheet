#pragma once
#include "JobClass.h"

class Ranger : public JobClass
{
public:
	Ranger(ABILITIES& abs, unsigned long startingLevel = 1);
	~Ranger() {}
	void IncreaseLevel(unsigned long Amount = 0) override { Level += Amount; }
	void DecreaseLevel(unsigned long Amount = 0) override { Level = (Level - Amount < 0) ? 0 : Level - Amount; }
};