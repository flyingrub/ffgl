#pragma once
#include <FFGLSDK.h>
using namespace ffglqs;
class PolygonRepeat : public Source
{
public:
	PolygonRepeat();
	void Update() override;
	~PolygonRepeat();

private:
	float relativeTime         = 0;
	float relativeRotationTime = 0;
};
