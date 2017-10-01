////////////////////////////////////////////////////////////////////////////////
// Filename: color.ps
////////////////////////////////////////////////////////////////////////////////
#version 400


/////////////////////
// INPUT VARIABLES //
/////////////////////
in vec2 texCoord;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
out vec4 outputColor;

///////////////////////
// UNIFORM VARIABLES //
///////////////////////
uniform sampler2D shaderTexture;
uniform sampler2D lightTexture;
uniform vec4 color;

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	vec4 textureColor;
	vec4 lightColor;

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = texture(shaderTexture, texCoord);
	
	// Multiply by the color
	textureColor *= color;
	
	// Sample the light texture
	lightColor = texture(lightTexture, gl_FragCoord.xy);	
	
	// Set the correct fragment screen coordinate
	vec2 fragScreenCoord = gl_FragCoord.xy;
	vec2 texelSize = 1.0 / vec2(textureSize(lightTexture, 0));
	fragScreenCoord *= texelSize;
	
	// Sample the light texture
	lightColor = texture(lightTexture, fragScreenCoord);	
	
	// Multiply by the light color
	textureColor *= lightColor + 0.2;
	
	outputColor = textureColor;
}