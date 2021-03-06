#include "Wobble.h"

static PluginInstance p = Effect::CreatePlugin< Wobble >( {
	"FL15",            // plugin unique ID
	"Wobble"// Plugin name
} );

static const std::string fshader = R"(
uniform float relativeTime;
void main()
{
	vec2 p = i_uv *2.-1.;
	vec2 offset = vec2(cos(length(p * size) + relativeTime), sin(length(p * size) + relativeTime));
	if (mode == 1.)
    	offset = vec2(cos(length(p * size + relativeTime)), sin(length(p * size + relativeTime)));
	if (mode == 2.)
    	offset = vec2(sin(( p.x * p.y ) * size + relativeTime), cos(( p.x * p.y ) * size + relativeTime));
	if (mode == 3.)
    	offset = vec2(sin( i_uv.x * size + relativeTime),cos( i_uv.y * size + relativeTime));
    if (mode == 4.)
		offset = vec2(sin( p.x * size + relativeTime), cos( p.y * size + relativeTime));
	fragColor = texture( inputTexture, i_uv+ strength*offset );
}
)";

Wobble::Wobble()
{
	SetFragmentShader( fshader );
	AddParam( speed = ParamRange::Create( "speed", .5f, { 0.1, 5. } ) );
	AddParam( ParamRange::Create( "size", 1.f, { .7, 5. } ) );
	AddParam( ParamRange::Create( "strength", 0.05f, { 0.001, .1 } ) );
	AddParam( ParamOption::Create( "mode", {
		{ "1" }, { "2" }, { "3" }, { "4" }, { "5" }
	}));
}

Wobble::~Wobble()
{
}

void Wobble::Update()
{
	auto speedParam = std::dynamic_pointer_cast< ParamRange >( GetParam( "speed" ) );
	float speed     = speedParam->GetValue();
	relativeTime += deltaTime * speed;
	shader.Set( "relativeTime", relativeTime );
}
