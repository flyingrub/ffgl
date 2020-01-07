#include "Dissolve.h"

static PluginInstance p = Effect::CreatePlugin< Dissolve >( {
	"FL09",   // plugin unique ID
	"Dissolve"// Plugin name
} );

static const std::string fshader = R"(
#define pixel_width 3./resolution.y
uniform float relativeTime;

float fractal_noise(vec3 m) {
    float start = 0.5;
	vec4 coef = vec4(start,start/2.,start/4.,start/8.);
	coef.yzw *= 1.-smoothness;
    return fractal_noise(m,coef);
}

void main()
{
	vec2 p = i_uv;
	vec3 p3 = vec3(p*zoom, relativeTime)*8.0+8.0;
    
	float red = fractal_noise(p3)*.5+.5;
	red = smoothstep(pixel_width,0.,red-amount);
    
    p3 = p3+spaced;
    float blue = fractal_noise(p3)*.5+.5;
    blue = smoothstep(pixel_width,0.,blue-amount);
   
    p3 = p3+spaced;
    float green = fractal_noise(p3)*.5+.5;
	green = smoothstep(pixel_width,0.,green-amount);

    vec3 color = texture(inputTexture,i_uv).rgb;
	vec3 col = vec3(red,green,blue)*color;
	
	fragColor = vec4(vec3(col),1.0);
}
)";

Dissolve::Dissolve()
{
	Include( shader::snippet_id::simplex );
	AddParam( ParamRange::Create( "zoom", 0.5f, { 0.0f, 2.0f } ) );
	AddParam( ParamRange::Create( "speed", 0.5f, { 0.0f, 0.2f } ) );
	AddParam( ParamRange::Create( "amount", 0.5f, { 0.0f, 1.0f } ) );
	AddParam( ParamRange::Create( "spaced", 0.5f, { 0.0f, .01f } ) );
	AddParam( ParamRange::Create( "smoothness", 0.5f, { 0.0f, 1.0f } ) );
	SetFragmentShader( fshader );
}

void Dissolve::Update()
{
	auto speedParam = std::dynamic_pointer_cast< ParamRange >( GetParam( "speed" ) );
	float speed     = speedParam->GetValue();
	relativeTime += deltaTime * speed;
	shader.Set( "relativeTime", relativeTime );
}

Dissolve::~Dissolve()
{
}