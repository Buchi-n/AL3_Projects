#pragma once
#include <Input.h>

class Player 
{
public:
	void Inisialize();
	void Update();
	void Draw();

private:
	Input* input_ = nullptr;
};
