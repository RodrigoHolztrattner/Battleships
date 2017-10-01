///////////////////////////////////////////////////////////////////////////////
// Filename: FWaterShader.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FWaterShader.h"
#include "..\..\Entity\Actor\FActor.h"
#include "..\..\Resource\Texture\FTexture.h"
#include "..\..\Camera\FCamera.h"

#include "..\..\Font\FFontLoader.h"

FWaterShader::FWaterShader() : FShaderBase(ShaderType::Normal)
{
	// Set the initial data
	m_CurrentTime = 0;
}

FWaterShader::FWaterShader(const FWaterShader& other) : FShaderBase(ShaderType::Normal)
{
}

FWaterShader::~FWaterShader()
{
}

bool FWaterShader::Initialize()
{
	bool result;

	// Compile the vertex shader
	result = CreateShaderFromFile("Source\\Core\\Environment\\Water\\FWaterShader.vs", GL_VERTEX_SHADER, m_VertexShader);
	if (!result)
	{
		return false;
	}

	// Compile the fragment shader
	result = CreateShaderFromFile("Source\\Core\\Environment\\Water\\FWaterShader.fs", GL_FRAGMENT_SHADER, m_FragmentShader);
	if (!result)
	{
		return false;
	}

	// Create a shader program object.
	m_ShaderProgram = glCreateProgram();

	// Attach the vertex and fragment shader to the program object.
	glAttachShader(m_ShaderProgram, m_VertexShader);
	glAttachShader(m_ShaderProgram, m_FragmentShader);

	// Bind the shader input variables.
	glBindAttribLocation(m_ShaderProgram, 0, "inputPosition");
	glBindAttribLocation(m_ShaderProgram, 1, "inputTexCoord");

	// Link the shader program.
	glLinkProgram(m_ShaderProgram);

	// Check the status of the link.
	int status;
	glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &status);
	if (status != 1)
	{
		return false;
	}

	// Create the water object
	CreateWaterMesh();

	// Get the water textures
	m_DifuseWaterTexture = FTexture::GetResourceByName<FTexture>(FHashedString("waterdiffuse.tga"));
	m_WaveWaterTexture = FTexture::GetResourceByName<FTexture>(FHashedString("waterwave.tga"));
	m_NormalWaterTexture = FTexture::GetResourceByName<FTexture>(FHashedString("waternormal.tga"));
	m_BumpWaterTexture = FTexture::GetResourceByName<FTexture>(FHashedString("waterbump.tga"));

	// Create the water tile textures
	for (int i = 0; i < 50; i++)
	{
		char indexBuffer[33];
		char textureNameBuffer[20];

		// Convert the index
		itoa(i, indexBuffer, 10);

		// Set the texture name
		strcpy(textureNameBuffer, "watertile");

		// If the index is less then 10, we need to insert a zero
		if (i < 10)
		{
			strcat(textureNameBuffer, "0");
		}

		// Copy the index
		strcat(textureNameBuffer, indexBuffer);

		// Copy the tga extension
		strcat(textureNameBuffer, ".tga");

		// Get the texture
		m_WaterTileTextures[i] = FTexture::GetResourceByName<FTexture>(FHashedString(textureNameBuffer));
	}

	return true;
}

void FWaterShader::CreateWaterMesh()
{
	struct WidgetVertex
	{
		WVector3 position;
		WVector2 texCoord;
	};
	WidgetVertex vertices[4];
	unsigned int indices[6];

	#define WaterSize			2000.0f
	#define WaterHeight			-1.0f
	#define WaterTextureRepeat	(WaterSize / 50) // 40.0f

	// Load the vertex array with data.

	// Top left.
	vertices[0].position.x = -WaterSize;  // Position.
	vertices[0].position.y = -WaterSize;
	vertices[0].position.z = WaterHeight;

	vertices[0].texCoord.x = 0.0f;  // texCoord.
	vertices[0].texCoord.y = WaterTextureRepeat;

	// Bottom left.
	vertices[1].position.x = -WaterSize;  // Position.
	vertices[1].position.y = WaterSize;
	vertices[1].position.z = WaterHeight;

	vertices[1].texCoord.x = 0.0f;  // texCoord.
	vertices[1].texCoord.y = 0.0f;

	// Bottom right.
	vertices[2].position.x = WaterSize;  // Position.
	vertices[2].position.y = WaterSize;
	vertices[2].position.z = WaterHeight;

	vertices[2].texCoord.x = WaterTextureRepeat;  // texCoord.
	vertices[2].texCoord.y = 0.0f;

	// Top right.
	vertices[3].position.x = WaterSize;  // Position.
	vertices[3].position.y = -WaterSize;
	vertices[3].position.z = WaterHeight;

	vertices[3].texCoord.x = WaterTextureRepeat;  // texCoord.
	vertices[3].texCoord.y = WaterTextureRepeat;

	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top left.
	indices[2] = 3;  // Bottom right.

	indices[3] = 3;  // Bottom right.
	indices[4] = 1;  // Top left.
	indices[5] = 2;  // Bottom right.

	//
	//
	//

	// Allocate an OpenGL vertex array object.
	glGenVertexArrays(1, &m_VertexArrayId);

	// Bind the vertex array object to store all the buffers and vertex attributes we create here.
	glBindVertexArray(m_VertexArrayId);

	// Generate an ID for the vertex buffer.
	glGenBuffers(1, &m_VertexBufferId);

	// Bind the vertex buffer and load the vertex (position and color) data into the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(WidgetVertex), vertices, GL_STATIC_DRAW);

	// Enable the two vertex array attributes.
	glEnableVertexAttribArray(0);  // Vertex position.
	glEnableVertexAttribArray(1);  // Texture coordinates.

	// Specify the location and format of the position portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(WidgetVertex), 0); // 0, 2

	// Specify the location and format of the color portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(WidgetVertex), (unsigned char*)NULL + (3 * sizeof(float))); // (2 * sizeof(float))

	// Generate an ID for the index buffer.
	glGenBuffers(1, &m_IndexBufferId);

	// Bind the index buffer and load the index data into it.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void FWaterShader::Render(float _elapsedTime, FCamera* _camera, FGraphic* _graphicContext)
{
	WMatrix4 worldMatrix,* viewMatrix,* orthoMatrix;

	// Increment the current time
	m_CurrentTime += _elapsedTime;

	// Set the shader program that we will use for rendering
	glUseProgram(m_ShaderProgram);

	// Bind the vertex array
	glBindVertexArray(m_VertexArrayId);

	// Build the matrices
	worldMatrix.BuildIdentity();
	viewMatrix = _camera->ViewMatrix(); // BuildView(WVector3(0, 0, 0), WVector3(0, 0, 0), WVector3(0, 0, 1.0f), WVector3(0, 1.0f, 0));
	orthoMatrix = _camera->OrthoMatrix(); // BuildOrtho((3.14159265358979323846f / 4.0f), 800, 600, 0.1f, 1000.0f);

	// Set the world matrix in the vertex shader
	unsigned int location;
	location = glGetUniformLocation(m_ShaderProgram, "worldMatrix");
	if (location == -1)
	{
		return;
	}
	glUniformMatrix4fv(location, 1, false, worldMatrix.v);

	// Set the view matrix in the vertex shader
	location = glGetUniformLocation(m_ShaderProgram, "viewMatrix");
	if (location == -1)
	{
		return;
	}
	glUniformMatrix4fv(location, 1, false, viewMatrix->v);

	// Set the projection matrix in the vertex shader
	location = glGetUniformLocation(m_ShaderProgram, "projectionMatrix");
	if (location == -1)
	{
		return;
	}
	glUniformMatrix4fv(location, 1, false, orthoMatrix->v);
	
	//
	//
	//

	WMatrix4 transformMatrix;

	// Build the transform matrix
	transformMatrix.BuildTransform(WVector3(0, 0, 0), WVector3(0, 0, 0), WVector3(1, 1, 1));

	// transformMatrix.BuildIdentity();

	// Set the transform matrix inside the shader
	location = glGetUniformLocation(m_ShaderProgram, "transformMatrix");
	if (location == -1)
	{
		return;
	}
	glUniformMatrix4fv(location, 1, false, transformMatrix.v);

	//
	//
	//
	// Set the time value inside the shader
	location = glGetUniformLocation(m_ShaderProgram, "time");
	if (location == -1)
	{
		// return;
	}
	glUniform1f(location, m_CurrentTime);

	//
	//
	//

	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set the water tile index
	int timedIndex = (int)(m_CurrentTime * 10);
	int waterTileIndex = (timedIndex % 50);

	// Set the diffuse texture
	if (!m_WaterTileTextures[waterTileIndex]->SetShaderTexture(m_ShaderProgram, GL_TEXTURE0, 0, "diffuseTexture"))
	{
		return;
	}

	/*
	// Set the wave texture
	if (!m_WaveWaterTexture->SetShaderTexture(m_ShaderProgram, GL_TEXTURE1, 1, "waveTexture"))
	{
		// return;
	}
	*/

	// Set the normal texture
	if (!m_NormalWaterTexture->SetShaderTexture(m_ShaderProgram, GL_TEXTURE1, 1, "normalTexture"))
	{
//		return;
	}

	// Set the bump texture
	if (!m_BumpWaterTexture->SetShaderTexture(m_ShaderProgram, GL_TEXTURE2, 2, "bumpTexture"))
	{
//		return;
	}

	//////////////////////
	// DEFERRED TEXTURE //
	//////////////////////

	// Set the active texture and bind it
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _graphicContext->GetDeferredTexture());

	// Set the texture in the pixel shader to use the data from the first texture unit.
	location = glGetUniformLocation(m_ShaderProgram, "lightTexture");
	if (location == -1)
	{
		return;
	}
	glUniform1i(location, 3);

	//

	// Draw the sprite
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void FWaterShader::AddObject(void* _objectPtr)
{
}