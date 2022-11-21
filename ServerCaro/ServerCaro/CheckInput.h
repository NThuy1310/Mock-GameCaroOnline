#pragma once
#include"CheckedException.h"
#include"GameProperties.h"

class CheckInput
{
public:
	CheckInput();
	~CheckInput();

	static bool checkInvalidPoint(int, int, shared_ptr<GameProperties>);

};