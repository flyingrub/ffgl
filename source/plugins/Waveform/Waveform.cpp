#include "Waveform.h"
using namespace ffglex;

static CFFGLPluginInfo PluginInfo(
	PluginFactory< Waveform >,// Create method
	"RS01",                        // Plugin unique ID
	"Gradient Example",            // Plugin name
	2,                             // API major version number
	1,                             // API minor version number
	1,                             // Plugin major version number
	000,                           // Plugin minor version number
	FF_SOURCE,                     // Plugin type
	"Sample FFGL Gradients plugin",// Plugin description
	"Resolume FFGL Example"        // About
);

Waveform::Waveform()
{
}

Waveform::~Waveform()
{
}

FFResult Waveform::InitGL(const FFGLViewportStruct * vp)
{
	return FFResult();
}

FFResult Waveform::ProcessOpenGL(ProcessOpenGLStruct * pGL)
{
	return FFResult();
}

FFResult Waveform::DeInitGL()
{
	return FFResult();
}

FFResult Waveform::SetFloatParameter(unsigned int dwIndex, float value)
{
	return FFResult();
}

float Waveform::GetFloatParameter(unsigned int index)
{
	return 0.0f;
}
