#include "StroboBeat.h"

static PluginInstance p = Effect::CreatePlugin< StroboBeat >( {
	"FL12",     // plugin unique ID
	"StroboBeat"// Plugin name
} );

static const std::string fshader = R"(
void main()
{
	vec4 tex = texture(inputTexture, i_uv);
	bool shouldBeOn = fract(phase * speed) < dutyCycle;
	shouldBeOn = reversephase ? !shouldBeOn : shouldBeOn;
	tex = mix(tex,vec4(0,0,0,1),vec4(blackframe));
	fragColor=mix(tex,color,vec4(shouldBeOn));
}
)";

StroboBeat::StroboBeat()
{
	AddHueColorParam( "color" );
	AddParam( dutyCycle = Param::Create( "dutyCycle", .5f ) );
	AddParam( speed = ParamRange::Create( "speed", .5, { 1, 64 } ) );
	AddParam( ParamBool::Create( "blackframe" ) );
	AddParam( ParamBool::Create( "reversephase" ) );
	SetFragmentShader( fshader );
}

void StroboBeat::Update()
{
	unsigned long v = (unsigned long)speed->GetValue();
	// get upper powe of two
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	float value = (float)v / 4.f;
	shader.Set( "speed",  value );
}

StroboBeat::~StroboBeat()
{
}