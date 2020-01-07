#pragma once
#include <FFGLSDK.h>
using namespace ffglqs;
class Screenshake : public Effect
{
public:
	Screenshake();
	~Screenshake();
	void Update() override;

private:
	float relativeTime = 0;
	std::shared_ptr<ParamRange> amountX, amountY;
};
