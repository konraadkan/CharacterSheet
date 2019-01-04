#pragma once
#include "wrapper.h"
#include "abilities.h"

struct Descending
{
	template<class T>
	bool operator()(T const &a, T const &b) const { return a > b; }
};

class RerollInteraction : public Wrapper
{
private:
	ABILITIES* AbiPtr;
	void GenerateAbilities();
public:
	bool ScoresGenerated = false;
	void Interact() override;
	std::wstring GetOutput() override;
	long GetAbilityModifier(ABILITYSCORES Abi) override;
	unsigned long GetAbilityScore(ABILITYSCORES Abi) override;
public:
	RerollInteraction(ABILITIES* ptr)
	{
		AbiPtr = ptr;
	}
	~RerollInteraction() { AbiPtr = NULL; }
public:
	void UpdatePtrAdr(ABILITIES* ptr)
	{
		AbiPtr = ptr;
	}
};