#include "Screenshake.h"

static PluginInstance p = Effect::CreatePlugin< Screenshake >( {
	"FL10",      // plugin unique ID
	"Screenshake"// Plugin name
} );

static const std::string fshader = R"(
uniform float relativeTime;

vec2 rotate2D(vec2 _uv, float _angle){
    _uv =  mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle)) * _uv;
    return _uv;
}

void main()
{
	vec2 amount = vec2(amountX, amountY);
	vec2 uv = i_uv*2.-1.;
   	vec3 p3 = vec3(0,0, relativeTime)*8.0+8.0;
    vec3 noise = vec3(simplex3d(p3),simplex3d(p3+10.),simplex3d(p3+20.));
	if (random) noise = random3(p3+1000.)*2.-1.;
    uv = rotate2D(uv, noise.z*rotationAmount*.1);
	uv = (uv+1.)/2.;
	fragColor = texture( inputTexture, uv+noise.xy*amount*0.1 );
}
)";

Screenshake::Screenshake()
{
	Include( shader::snippet_id::simplex );
	SetFragmentShader( fshader );
	AddParam( amountX = ParamRange::Create( "amountX", 0.1f, { 0.0, 1.0 } ) );
	AddParam( amountY = ParamRange::Create( "amountY", 0.1f, { 0.0, 1.0 } ) );
	AddParam( ParamRange::Create( "rotationAmount", 0.1f, { 0.0, 1. } ) );
	AddParam( ParamRange::Create( "speed", 0.3f, { 0.0, 3. } ) );
	AddParam( ParamBool::Create( "random" ) );
}

Screenshake::~Screenshake()
{
}

void Screenshake::Update()
{
	auto speedParam = std::dynamic_pointer_cast< ParamRange >( GetParam( "speed" ) );
	float speed     = speedParam->GetValue();
	relativeTime += deltaTime * speed;
	shader.Set( "relativeTime", relativeTime );
}