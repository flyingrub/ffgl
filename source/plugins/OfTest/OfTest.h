#pragma once
#include <ofMain.h>

#include <FFGLSDK.h>

class OfTest : public Source
{
public:
	OfTest();
	FFResult InitGL( const FFGLViewportStruct* viewPort ) override;
	FFResult ProcessOpenGL( ProcessOpenGLStruct* inputTextures ) override;
	FFResult DeInitGL() override;
	~OfTest();

private:
};
