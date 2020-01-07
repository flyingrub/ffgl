#pragma once
#include <FFGLSDK.h>
using namespace ffglqs;

class StroboBeat : public Effect
{
public:
	StroboBeat();
	void Update() override;
	~StroboBeat();
	std::shared_ptr < Param > dutyCycle;
	std::shared_ptr < ParamRange > speed;
};
