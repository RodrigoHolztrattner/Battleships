///////////////////////////////////////////////////////////////////////////////
// Filename: FFlipbookShader.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FFlipbookShader.h"
#include "..\..\Entity\Actor\FActor.h"
#include "..\..\Camera\FCamera.h"

FFlipbookShader::FFlipbookShader() : FShaderBase(ShaderType::Normal)
{
}

FFlipbookShader::FFlipbookShader(const FFlipbookShader& other) : FShaderBase(ShaderType::Normal)
{
}

FFlipbookShader::~FFlipbookShader()
{
}

bool FFlipbookShader::Initialize()
{
	bool result;

	// Compile the vertex shader
	result = CreateShaderFromFile("Source\\Core\\Renderable\\Flipbook\\FFlipbookShader.vs", GL_VERTEX_SHADER, m_VertexShader);
	if (!result)
	{
		return false;
	}

	// Compile the fragment shader
	result = CreateShaderFromFile("Source\\Core\\Renderable\\Flipbook\\FFlipbookShader.fs", GL_FRAGMENT_SHADER, m_FragmentShader);
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

	// Create the widget object
	CreateSpriteMesh();

	return true;
}

void FFlipbookShader::CreateSpriteMesh()
{
	struct WidgetVertex
	{
		WVector3 position;
		WVector2 texCoord;
	};
	WidgetVertex vertices[4];
	unsigned int indices[6];

	// WE NEED TO MAKE THE POSITIONS AND COORDINATES 3D //

	// Load the vertex array with data.

	// Top left.
	vertices[0].position.x = -0.5f;  // Position.
	vertices[0].position.y = -0.5f;
	vertices[0].position.z = 0.0f;

	vertices[0].texCoord.x = 0.0f;  // texCoord.
	vertices[0].texCoord.y = 1.0f;

	// Bottom left.
	vertices[1].position.x = -0.5f;  // Position.
	vertices[1].position.y = 0.5f;
	vertices[1].position.z = 0.0f;

	vertices[1].texCoord.x = 0.0f;  // texCoord.
	vertices[1].texCoord.y = 0.0f;

	// Bottom right.
	vertices[2].position.x = 0.5f;  // Position.
	vertices[2].position.y = 0.5f;
	vertices[2].position.z = 0.0f;

	vertices[2].texCoord.x = 1.0f;  // texCoord.
	vertices[2].texCoord.y = 0.0f;

	// Top right.
	vertices[3].position.x = 0.5f;  // Position.
	vertices[3].position.y = -0.5f;
	vertices[3].position.z = 0.0f;

	vertices[3].texCoord.x = 1.0f;  // texCoord.
	vertices[3].texCoord.y = 1.0f;

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

void FFlipbookShader::Render(float _elapsedTime, FCamera* _camera, FGraphic* _graphicContext)
{
	WMatrix4 worldMatrix,* viewMatrix,* orthoMatrix;

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

	// Enable blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// For each widget inside the queue
	for (auto it = m_RenderQueue.begin(); it != m_RenderQueue.end(); it++)
	{
		WMatrix4 transformMatrix;
		FFlipbook* flipbook = it->second;

		// Get the actor linked to this flipbook
		FActor* owner = flipbook->GetOwner();
		
		// Build the transform matrix
		transformMatrix = owner->GetTransformMatrix();
		
		// transformMatrix.BuildIdentity();

		// Set the transform matrix inside the shader
		location = glGetUniformLocation(m_ShaderProgram, "transformMatrix");
		if (location == -1)
		{
			return;
		}
		glUniformMatrix4fv(location, 1, false, transformMatrix.v);

		///////////
		// DEPTH //
		///////////
		// glEnable(GL_DEPTH_TEST);
		// glDepthFunc(GL_LESS);

		// Set the depth inside the shader
		location = glGetUniformLocation(m_ShaderProgram, "depth");
		if (location == -1)
		{
			return;
		}
		glUniform1f(location, 4);

		/////////////
		// TEXTURE //
		/////////////

		// Set the active texture and bind it
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, flipbook->Texture()->GetHandle());

		// Set the texture in the pixel shader to use the data from the first texture unit.
		location = glGetUniformLocation(m_ShaderProgram, "shaderTexture");
		if (location == -1)
		{
			return;
		}
		glUniform1i(location, 0);

		//////////////////////
		// DEFERRED TEXTURE //
		//////////////////////

		// Set the active texture and bind it
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _graphicContext->GetDeferredTexture());

		// Set the texture in the pixel shader to use the data from the first texture unit.
		location = glGetUniformLocation(m_ShaderProgram, "lightTexture");
		if (location == -1)
		{
			return;
		}
		glUniform1i(location, 1);
		
		///////////
		// COLOR //
		///////////

		// Set the color inside the shader
		location = glGetUniformLocation(m_ShaderProgram, "color");
		if (location == -1)
		{
			return;
		}
		glUniform4f(location, flipbook->Color().x, flipbook->Color().y, flipbook->Color().z, flipbook->Alpha());
		
		////////////
		// RENDER //
		////////////

		// Draw the sprite
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	// Clean the render queue
	m_RenderQueue.clear();
}

void FFlipbookShader::AddObject(void* _objectPtr)
{
	// Cast the object
	FFlipbook* sprite = (FFlipbook*)_objectPtr;

	// Insert into the map
	m_RenderQueue.insert(std::pair<int, FFlipbook*>(sprite->GetOwner()->GetDepthPlane(), sprite));
}