#pragma once
#include "JobClass.h"

class Sorcerer : public JobClass
{
public:
	Sorcerer(ABILITIES& abs, unsigned long startingLevel = 1);
	~Sorcerer() {}
	void IncreaseLevel(unsigned long Amount = 0) override { Level += Amount; }
	void DecreaseLevel(unsigned long Amount = 0) override { Level = (Level - Amount < 0) ? 0 : Level - Amount; }
};