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
uniform sampler2D fontTexture;
uniform vec4 glyphCoordinate;

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	vec4 textureColor;
	
	if(texCoord.y >= 0.9)
	{
		outputColor = vec4(0, 0, 0, 0);
		return;
	}
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = texture(fontTexture, mix(glyphCoordinate.xy, glyphCoordinate.zw, texCoord));
//	textureColor = vec4(0.5, 0.3, 1.0, 1.0);

	textureColor.a = (textureColor.r + textureColor.g + textureColor.b) / 3.0;
	
	
	/*
	
	b = a
	
	*/
	
	outputColor = textureColor;
}