#pragma once
#include <FFGLSDK.h>
class Wobble : public Effect
{
public:
	Wobble();
	~Wobble();
	void update() override;

private:
	ParamRange::Ptr speed;
	ParamRange::Ptr size;
	ParamRange::Ptr strengh;
	ParamOption::Ptr mode;
	float relativeTime=0.0f;
};
