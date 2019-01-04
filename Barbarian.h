#pragma once
#include "JobClass.h"

class Barbarian : public JobClass
{
public:	
	Barbarian(ABILITIES& abs, unsigned long startingLevel = 1);
	~Barbarian() {}
	void IncreaseLevel(unsigned long Amount = 0) override { Level += Amount; }
	void DecreaseLevel(unsigned long Amount = 0) override { Level = (Level - Amount < 0) ? 0 : Level - Amount; }
};