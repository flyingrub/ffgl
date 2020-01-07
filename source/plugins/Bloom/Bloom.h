#pragma once
#include <FFGLSDK.h>
using namespace ffglqs;
using namespace ffglex;

class Bloom : public Effect
{
public:
	Bloom();
	FFResult Init() override;
	FFResult Render( ProcessOpenGLStruct* inputTextures ) override;
	void Clean() override;
	~Bloom();

private:
	std::shared_ptr < ParamRange > threshold;
	std::shared_ptr < ParamRange > radius;
	std::shared_ptr < ParamRange > intensity;
	std::shared_ptr < ParamBool > hq;
	std::shared_ptr < ParamBool > antiFlicker;
	std::shared_ptr < ParamRange > jitter;
	FFGLShader downSampleFilter;
	FFGLShader upSampleFilter;
	FFGLShader final;
};
