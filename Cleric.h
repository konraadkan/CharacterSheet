#pragma once
#include "JobClass.h"

class Cleric : public JobClass
{
public:
	Cleric(ABILITIES& abs, unsigned long startingLevel = 1);
	~Cleric() {}
	void IncreaseLevel(unsigned long Amount = 0) override { Level += Amount; }
	void DecreaseLevel(unsigned long Amount = 0) override { Level = (Level - Amount < 0) ? 0 : Level - Amount; }
};