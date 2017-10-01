////////////////////////////////////////////////////////////////////////////////
// Filename: color.vs
////////////////////////////////////////////////////////////////////////////////

#version 400

/////////////////////
// INPUT VARIABLES //
/////////////////////
in vec3 inputPosition;
in vec2 inputTexCoord;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
out vec2 texCoord;

///////////////////////
// UNIFORM VARIABLES //
///////////////////////

// Matrices
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Transform 2D
uniform vec4 transform;
uniform mat4 transformMatrix;

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	// Transform the initial position
	vec3 transformPosition = inputPosition;
	
	// Set the z coordinate
	transformPosition.z = 1.0;
	
	// Set the texture coordinates
	texCoord = inputTexCoord;
	// texCoord.xy = texCoord.yx;
	
	transformPosition = inputPosition;
	transformPosition.z = 1;
	
	// Calculate the position of the vertex against transform matrix
	gl_Position = transformMatrix * vec4(transformPosition, 1.0f);
	
	// Translate the position to the original widget area
	gl_Position.x += transform.z / 2.0;
	gl_Position.y += transform.w / 2.0;
	
	// Calculate the position of the vertex against the world, view, and projection matrices.
	gl_Position = worldMatrix * gl_Position;
	gl_Position = viewMatrix * gl_Position;
	gl_Position = projectionMatrix * gl_Position;
}