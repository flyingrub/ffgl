#pragma once
#include <FFGLSDK.h>
#include <string>


class Waveform : public CFreeFrameGLPlugin
{
public:
	Waveform();
	~Waveform();

	//CFreeFrameGLPlugin
	FFResult InitGL(const FFGLViewportStruct* vp) override;
	FFResult ProcessOpenGL(ProcessOpenGLStruct* pGL) override;
	FFResult DeInitGL() override;

	FFResult SetFloatParameter(unsigned int dwIndex, float value) override;

	float GetFloatParameter(unsigned int index) override;

	const char* GetShortName() override
	{
		static const char* sname = "Waveform";
		return sname;
	}

private:
	float m_MixVal;

	ffglex::FFGLShader shader;   //!< Utility to help us compile and link some shaders into a program.
	ffglex::FFGLScreenQuad quad; //!< Utility to help us render a full screen quad.
};
