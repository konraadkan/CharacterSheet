#pragma once
#include <vector>
#include "graphics.h"
#include "Character.h"

class Stage
{
protected:
	static Graphics* gfx;
public:
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}
	virtual void Load() = 0;
	virtual void Load(std::vector<Character*> &Characters) = 0;
	virtual void Render() = 0;
	virtual void Unload() = 0;
	virtual void Update(float delta) = 0;;
};