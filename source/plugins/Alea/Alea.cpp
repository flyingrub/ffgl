#include "Alea.h"

static PluginInstance p = Source::CreatePlugin< Alea >( {
	"FL01",// plugin unique ID
	"ALEA" // Plugin name
} );

static const std::string fshader = R"(
#define PI 3.14159265359
#define TWO_PI 6.28318530718
uniform float sides;
uniform float audioVolume;

vec2 rotate2D(vec2 _uv, float _angle){
    _uv =  mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle)) * _uv;
    return _uv;
}

float polygon(vec2 _uv, float size, float width, float sides) {
	// Angle and radius from the current pixel
	float a = atan(_uv.x,_uv.y)+PI;
	float r = TWO_PI/float(sides);

	// Shaping function that modulate the distance
	float d = cos(floor(.5+a/r)*r-a)*length(_uv);

	return 1.-smoothstep(size+width,size+width+0.005,d)-1.+smoothstep(size,size+0.005,d);
}

void main()
{
    vec2 uv = i_uv*2.-1.;
	uv.x *= resolution.x/resolution.y;
    uv = rotate2D(uv, time*0.1 +  audioVolume);

    float size = iSize/10. + iSize * audioVolume;
    float width = iSize/40. + iSize * audioVolume * .5;
    float rgbShift = iShiftAmount * audioVolume * .1;

	float colorR = polygon(uv-vec2(rgbShift,0), size, width, sides);
    float colorG = polygon(uv, size, width, sides);
    float colorB = polygon(uv+vec2(rgbShift,0), size, width, sides);
    fragColor = vec4(colorR, colorG, colorB, 1) * color;
}
)";

Alea::Alea()
{
	SetFragmentShader( fshader );
	AddHueColorParam( "color" );
	AddParam( Param::Create( "iSize", .6f ) );
	AddParam( Param::Create( "iShiftAmount", 0.5f ) );
	AddParam( smoothness = Param::Create( "smoothness", 0.9f ) );
	AddParam( change = ParamTrigger::Create( "change" ) );
	AddParam( fixedSize = ParamBool::Create( "fixedSize" ) );
	AddParam( select = ParamOption::Create( "select", { { "Global" }, { "Bass" }, { "Med" }, { "High" } } ) );
	AddParam( ParamText::Create( "test" ) );
	AddParam( gainParam = ParamRange::Create( "gainParam", 0.5, { -42, 42 } ) );
	AddParam( ParamRange::CreateInteger( "testInteger", 15, { -1000, 1000 } ) );
	AddParam( fft = ParamFFT::Create( "FFT" ) );
}

void Alea::Update()
{
	audioParams[ fft ].SetSmoothness( smoothness->GetValue() );
	audioParams[ fft ].SetGain( gainParam->GetValue() );

	if( change->GetValue() )
	{
		sides = random.GetRandomInt( 4, 10 );
	}

	if( fixedSize->GetValue() == 1)
	{
		shader.Set( "audioVolume", 1.0f );
	}
	else if( select->GetValue() == 1 )
	{
		shader.Set( "audioVolume", audioParams[ fft ].GetBass() );
	}
	else if( select->GetValue() == 2 )
	{
		shader.Set( "audioVolume", audioParams[ fft ].GetMed() );
	}
	else if( select->GetValue() == 3 )
	{
		shader.Set( "audioVolume", audioParams[ fft ].GetHigh() );
	}
	else if( select->GetValue() == 3 )
	{
		shader.Set( "audioVolume", audioParams[ fft ].GetVolume() );
	}

	shader.Set( "sides", (float)sides );
}

Alea::~Alea()
{
}
