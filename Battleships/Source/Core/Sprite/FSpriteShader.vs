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
	
	transformPosition.x *= transform.z;
	transformPosition.y *= transform.w;
	transformPosition.x += transform.x;
	transformPosition.y += transform.y;
	transformPosition.z = 1.0;
	
	// Set the texture coordinates
	texCoord = inputTexCoord;
	
	transformPosition = inputPosition;
	transformPosition.z = 1.0;
	
	// Calculate the position of the vertex against the world, view, and projection matrices.
	gl_Position = transformMatrix * vec4(transformPosition, 1.0f);
	gl_Position = worldMatrix * gl_Position;
	gl_Position = viewMatrix * gl_Position;
	gl_Position = projectionMatrix * gl_Position;
}