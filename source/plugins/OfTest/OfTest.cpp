#include "OfTest.h"

static PluginInstance p = Source::createPlugin< OfTest >( {
	"FL20",// plugin unique ID
	"OfTest" // Plugin name
} );

OfTest::OfTest()
{
	addHueColorParam( "color" );
}

FFResult OfTest::InitGL( const FFGLViewportStruct* viewPort )
{
	ofSetupOpenGL( viewPort->width, viewPort->height, OF_WINDOW );
	ffglex::resetOpenGLState();
	return CFreeFrameGLPlugin::InitGL( viewPort );
}

FFResult OfTest::ProcessOpenGL( ProcessOpenGLStruct* inputTextures )
{
	ofBackground( 1, 0, 0 );
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetColor( { 0, 1, 1} );
	ofFill();
	ofDrawRectangle( ofGetWidth(), ofGetHeight(), 100, 100 );
	ffglex::resetOpenGLState();
	return FFResult();
}

FFResult OfTest::DeInitGL()
{
	return FFResult();
}

OfTest::~OfTest()
{
}
