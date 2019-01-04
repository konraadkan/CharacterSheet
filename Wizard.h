#pragma once
#include "JobClass.h"

class Wizard : public JobClass
{
public:
	Wizard(ABILITIES& abs, unsigned long startingLevel = 1);
	~Wizard() {}
	void IncreaseLevel(unsigned long Amount = 0) override { Level += Amount; }
	void DecreaseLevel(unsigned long Amount = 0) override { Level = (Level - Amount < 0) ? 0 : Level - Amount; }
};