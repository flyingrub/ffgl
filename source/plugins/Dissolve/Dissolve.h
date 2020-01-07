#pragma once
#include <FFGLSDK.h>
using namespace ffglqs;
class Dissolve : public Effect
{
public:
	Dissolve();
	void Update() override;
	~Dissolve();

private:
	float relativeTime = 0;
};
