#pragma once
#include "JobClass.h"

class Bard : public JobClass
{
public:
	Bard(ABILITIES& abs, unsigned long startingLevel = 1);
	~Bard() {}
	void IncreaseLevel(unsigned long Amount = 0) override { Level += Amount; }
	void DecreaseLevel(unsigned long Amount = 0) override { Level = (Level - Amount < 0) ? 0 : Level - Amount; }
};