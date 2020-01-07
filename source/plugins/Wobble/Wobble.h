#pragma once
#include <FFGLSDK.h>
using namespace ffglqs;
class Wobble : public Effect
{
public:
	Wobble();
	~Wobble();
	void Update() override;

private:
	std::shared_ptr<ParamRange> speed;
	float relativeTime=0.0f;
};
