#include "Scanline.h"

static PluginInstance p = Effect::CreatePlugin< Scanline >( {
	"FL06",   // plugin unique ID
	"Scanline"// Plugin name
} );

static const std::string fshader = R"(
void main()
{
	vec4 color = texture(inputTexture, i_uv);
	//The inputTexture contains premultiplied colors, so we need to unpremultiply first to apply our effect on straight colors.
	if (color.a > 0.0)
		color.rgb /= color.a;

	float count = resolution.y * density;
	vec3 col = color.rgb;
	vec2 sl = vec2(sin(i_uv.y * count), cos(i_uv.y * count));
	vec3 scanlines = vec3(sl.x, sl.y, sl.x);

	col += col * scanlines * opacityScanline;
	col += col * vec3(random()) * opacityNoise;
    col += col * sin(110.0*time) * flickering;

	
	//The plugin has to output premultiplied colors, this is how we're premultiplying our straight color while also
	//ensuring we aren't going out of the LDR the video engine is working in.
	color.rgb = clamp(col * color.a, vec3(0.0), vec3(color.a));
	fragColor = color;
}
)";

Scanline::Scanline()
{
	Include( shader::snippet_id::random );
	SetFragmentShader( fshader );
	AddParam( ParamRange::Create( "density", 0.5f, { 0.0f, 2.0f } ) );
	AddParam( ParamRange::Create( "opacityScanline", 0.4f, { 0.0f, 2.0f } ) );
	AddParam( ParamRange::Create( "opacityNoise", 0.6f, { 0.0f, 4.0f } ) );
	AddParam( ParamRange::Create( "flickering", 0.3f, { 0.0f, 0.1f } ) );
}
Scanline::~Scanline()
{
}
