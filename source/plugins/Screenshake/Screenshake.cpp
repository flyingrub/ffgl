#include "Screenshake.h"

static PluginInstance p = Effect::createPlugin< Screenshake >( {
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
    uv = rotate2D(uv, noise.z*rotationAmount*.1);
	uv = (uv+1.)/2.;
	fragColor = texture( inputTexture, uv+noise.xy*amount*0.1 );
}
)";

Screenshake::Screenshake()
{
	include( shader::snippet_id::simplex );
	setFragmentShader( fshader );
	addParam( amountX = ParamRange::create( "amountX", 0.1f, { 0.0, 1.0 } ) );
	addParam( amountY = ParamRange::create( "amountY", 0.1f, { 0.0, 1.0 } ) );
	addParam( ParamRange::create( "rotationAmount", 0.1f, { 0.0, 1. } ) );
	addParam( ParamRange::create( "speed", 0.3f, { 0.0, 3. } ) );
	addParam( ParamBool::create( "random" ) );
}

Screenshake::~Screenshake()
{
}

void Screenshake::update()
{
	auto speedParam = std::dynamic_pointer_cast< ParamRange >( getParam( "speed" ) );
	float speed     = speedParam->getRealValue();
	relativeTime += deltaTime * speed;
	shader.Set( "relativeTime", relativeTime );
}