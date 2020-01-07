#pragma once
#include <FFGLSDK.h>
using namespace ffglqs;
class Alea : public Source
{
public:
	Alea();
	void Update() override;
	~Alea();

private:
	int sides = 5;
	std::shared_ptr<Param> smoothness;
	std::shared_ptr<ParamTrigger> change;
	std::shared_ptr<ParamBool> fixedSize;
	std::shared_ptr<ParamOption> select;
	std::shared_ptr<ParamRange> gainParam;
	std::shared_ptr<ParamFFT> fft;
};
