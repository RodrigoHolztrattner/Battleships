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
uniform sampler2D diffuseTexture;
// uniform sampler2D waveTexture;
uniform sampler2D normalTexture;
uniform sampler2D bumpTexture;
uniform sampler2D lightTexture;
uniform float time;

#define eyeVector 		vec3(0.0, 0.0, -1.0)

#define specPerturb 	1.0 // ? Colocar como 1 inicialmente
#define specPower		5.0 // Specular power

#define xWaveLength		1.0 // ? Colocar como 1 inicialmente
#define xWindForce 		1.0 // ? Colocar como 1

#define xWaveHeight 	1.0 // Alura da onda ? 

#define normalVector 	vec3(0.0, 0.0, -1.0) // Vertice

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	outputColor = vec4(0.1, 0.2, 0.5, 1.0);
	vec2 textureCoordinates;
	float currentTime;
	vec4 lightColor;
	
	// Normalize the time
	currentTime = time / 10.0;
	
	// Normalize the texture coordinates
	textureCoordinates = texCoord;
	
	//////////////////
	// PERTURBATION //
	//////////////////
	
	vec2 bumpSamplingPos;
	vec2 moveVector = vec2(-1.0, -1.0);
	bumpSamplingPos = textureCoordinates/xWaveLength + currentTime*xWindForce*moveVector;
	vec4 bumpColor = texture(bumpTexture, bumpSamplingPos);
	vec2 perturbation = xWaveHeight * (bumpColor.xy - 0.5);
	perturbation = textureCoordinates + currentTime*xWindForce*moveVector;
	
	/////////////
	// DIFFUSE //
	/////////////
	
	outputColor = texture(diffuseTexture, perturbation);
	
	// Set the correct fragment screen coordinate
	vec2 fragScreenCoord = gl_FragCoord.xy;
	vec2 texelSize = 1.0 / vec2(textureSize(lightTexture, 0));
	fragScreenCoord *= texelSize;
	
	// Sample the light texture
	lightColor = texture(lightTexture, fragScreenCoord);	
	
	// Multiply by the light color
	outputColor *= lightColor + 0.2;
	
	return;
	
	//////////
	// WAVE //
	//////////
	
	#define WaveConstant 1.8
	
	moveVector = vec2(-0.7, -0.5);
	bumpSamplingPos = textureCoordinates/xWaveLength + currentTime*xWindForce*moveVector;
	outputColor *= texture(diffuseTexture, bumpSamplingPos) * WaveConstant;
	
	moveVector = vec2(-0.4, -0.5);
	bumpSamplingPos = textureCoordinates/xWaveLength + currentTime*xWindForce*moveVector;
	outputColor *= texture(diffuseTexture, bumpSamplingPos) * WaveConstant;
	
	moveVector = vec2(-0.2, -0.6);
	bumpSamplingPos = textureCoordinates/xWaveLength + currentTime*xWindForce*moveVector;
	outputColor *= texture(diffuseTexture, bumpSamplingPos) * WaveConstant;
	
	////////////
	// NORMAL //
	////////////
	
	moveVector = vec2(-1.0, -1.0);
	bumpSamplingPos = textureCoordinates/xWaveLength + currentTime*xWindForce*moveVector;
	vec4 normal = texture(normalTexture, bumpSamplingPos);

	// float2 perturbatedTexCoords = ProjectedTexCoords + perturbation;
	// Usar perturbatedTexCoords para a textura normal da agua ?

	
	//////////////
	// SPECULAR //
	//////////////
	
	vec4 speccolor;
	vec3 lightSourceDir = normalize(vec3(1.0,1.0,-0.5));
	vec3 halfvec = normalize(eyeVector+lightSourceDir+vec3(perturbation.x*specPerturb,perturbation.y*specPerturb,0.0));

	
	vec3 temp = vec3(0.0, 0.0, 0.0);
	temp.x = pow(dot(halfvec,normalVector * normal.xyz),specPower);
	speccolor = vec4(0.98,0.97,0.7,0.6);
	speccolor = speccolor*temp.x;
	speccolor = vec4(speccolor.x*speccolor.w,speccolor.y*speccolor.w,speccolor.z*speccolor.w,0);
	outputColor = outputColor + speccolor * 0.0005;
	//outputColor = clamp(outputColor, 0.0, 1.0);
	
	/////////////
	// FRESNEL //
	/////////////
	
	// Multiply by the light color
	outputColor *= lightColor + 0.2;
}

/*
void main(void)
{
	outputColor = vec4(0.1, 0.2, 0.5, 1.0);
	vec2 textureCoordinates;
	float currentTime;
	
	// Normalize the time
	currentTime = time / 10.0;
	
	// Normalize the texture coordinates
	textureCoordinates = texCoord;
	
	///////////
	// WAVES //
	///////////
	vec2 bumpSamplingPos;
	
	vec2 moveVector = vec2(-1.0, -1.0);
	bumpSamplingPos = textureCoordinates/xWaveLength + currentTime*xWindForce*moveVector;
	vec4 bumpColor = texture(bumpTexture, bumpSamplingPos);
	
	vec2 perturbation = xWaveHeight * (bumpColor.xy - 0.5);

	
	
	moveVector = vec2(-2.7, -1.0);
	bumpSamplingPos = textureCoordinates/xWaveLength + currentTime*xWindForce*moveVector;
	outputColor *= texture(bumpTexture, bumpSamplingPos);
	
	moveVector = vec2(-0.0, -1.5);
	bumpSamplingPos = textureCoordinates/xWaveLength + currentTime*xWindForce*moveVector;
	outputColor *= texture(normalTexture, bumpSamplingPos);
	
	// float2 perturbatedTexCoords = ProjectedTexCoords + perturbation;
	// Usar perturbatedTexCoords para a textura normal da agua ?
	
	//////////
	// DULL //
	//////////
	
	
	vec4 dullColor = vec4(0.1f, 0.1f, 0.2f, 1.0f);
	float dullBlendFactor = xdullBlendFactor;
	outputColor = (dullBlendFactor*dullColor + (1-dullBlendFactor)*combinedColor);
	
	
	//////////////
	// SPECULAR //
	//////////////
	
	vec4 speccolor;
	vec3 lightSourceDir = normalize(vec3(1.0,1.0,-0.5));
	vec3 halfvec = normalize(eyeVector+lightSourceDir+vec3(perturbation.x*specPerturb,perturbation.y*specPerturb,0.0));

	
	vec3 temp = vec3(0.0, 0.0, 0.0);
	temp.x = pow(dot(halfvec,normalVector),specPower);
	speccolor = vec4(0.98,0.97,0.7,0.6);
	speccolor = speccolor*temp.x;
	speccolor = vec4(speccolor.x*speccolor.w,speccolor.y*speccolor.w,speccolor.z*speccolor.w,0);
	outputColor = outputColor + speccolor;
	
	/////////////
	// FRESNEL //
	/////////////
	
	
	float fresnelTerm = 0.5;
	float xDrawMode = 1.0;
	
	//Hardness factor – user input
	fresnelTerm = fresnelTerm * xDrawMode;

	//just to be sure that the value is between 0 and 1;
	fresnelTerm = fresnelTerm < 0? 0 : fresnelTerm;
	fresnelTerm = fresnelTerm > 1? 1 : fresnelTerm;

	// creating the combined color
	vec4 combinedColor = refractiveColor*(1-fresnelTerm) + reflectiveColor*(fresnelTerm);
	
}
*/
/*

void main(void)
{
	vec4 textureColor;

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
//	textureColor = texture(shaderTexture, texCoord);
	textureColor = vec4(0.5, 0.3, 1.0, 1.0);

	textureColor.r = mod(texCoord.x, 0.5);;
	textureColor.g = mod(texCoord.y, 0.5);
	textureColor.b = 0.0;
	textureColor.a = 1.0;

	
	outputColor = textureColor;
}



// https://habibs.wordpress.com/lake/

*/