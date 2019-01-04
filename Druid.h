#pragma once
#include "JobClass.h"

class Druid : public JobClass
{
public:
	Druid(ABILITIES& abs, unsigned long startingLevel = 1);
	~Druid() {}
	void IncreaseLevel(unsigned long Amount = 0) override { Level += Amount; }
	void DecreaseLevel(unsigned long Amount = 0) override { Level = (Level - Amount < 0) ? 0 : Level - Amount; }
};