///////////////////////////////////////////////////////////////////////////////
// Filename: FSpriteShader.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FSpriteShader.h"

FSpriteShader::FSpriteShader()
{
}

FSpriteShader::FSpriteShader(const FSpriteShader& other)
{
}

FSpriteShader::~FSpriteShader()
{
}

bool FSpriteShader::Initialize()
{
	bool result;

	// Compile the vertex shader
	result = CreateShaderFromFile("C:\\Users\\Rodrigo Holztrattner\\Documents\\Visual Studio 2013\\Projects\\Battleships\\Battleships\\Source\\Core\\Sprite\\FSpriteShader.vs", GL_VERTEX_SHADER, m_VertexShader);
	if (!result)
	{
		return false;
	}

	// Compile the fragment shader
	result = CreateShaderFromFile("C:\\Users\\Rodrigo Holztrattner\\Documents\\Visual Studio 2013\\Projects\\Battleships\\Battleships\\Source\\Core\\Sprite\\FSpriteShader.fs", GL_FRAGMENT_SHADER, m_FragmentShader);
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

void FSpriteShader::CreateSpriteMesh()
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

	// Bottom left.
	vertices[0].position.x = -0.5f;  // Position.
	vertices[0].position.y = -0.5f;
	vertices[0].position.z = 0.0f;

	vertices[0].texCoord.x = 0.0f;  // texCoord.
	vertices[0].texCoord.y = 0.0f;

	// Top left.
	vertices[1].position.x = -0.5f;  // Position.
	vertices[1].position.y = 0.5f;
	vertices[1].position.z = 0.0f;

	vertices[1].texCoord.x = 0.0f;  // texCoord.
	vertices[1].texCoord.y = 1.0f;

	// Top right.
	vertices[2].position.x = 0.5f;  // Position.
	vertices[2].position.y = 0.5f;
	vertices[2].position.z = 0.0f;

	vertices[2].texCoord.x = 1.0f;  // texCoord.
	vertices[2].texCoord.y = 1.0f;

	// Bottom right.
	vertices[3].position.x = 0.5f;  // Position.
	vertices[3].position.y = -0.5f;
	vertices[3].position.z = 0.0f;

	vertices[3].texCoord.x = 1.0f;  // texCoord.
	vertices[3].texCoord.y = 0.0f;

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
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(WidgetVertex), 0);

	// Specify the location and format of the color portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(WidgetVertex), (unsigned char*)NULL + (2 * sizeof(float)));

	// Generate an ID for the index buffer.
	glGenBuffers(1, &m_IndexBufferId);

	// Bind the index buffer and load the index data into it.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void FSpriteShader::Render()
{
	WMatrix4 worldMatrix, viewMatrix, projectionMatrix;

	// Set the shader program that we will use for rendering
	glUseProgram(m_ShaderProgram);

	// Bind the vertex array
	glBindVertexArray(m_VertexArrayId);

	// Build the matrices
	worldMatrix.BuildIdentity();
	viewMatrix.BuildView(WVector3(0, 0, 0), WVector3(0, 0, 0), WVector3(0, 0, 1.0f), WVector3(0, 1.0f, 0));
	projectionMatrix.BuildOrtho((3.14159265358979323846f / 4.0f), 800, 600, 0.1f, 1000.0f);

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
	glUniformMatrix4fv(location, 1, false, viewMatrix.v);

	// Set the projection matrix in the vertex shader
	location = glGetUniformLocation(m_ShaderProgram, "projectionMatrix");
	if (location == -1)
	{
		return;
	}
	glUniformMatrix4fv(location, 1, false, projectionMatrix.v);
	
	// For each widget inside the queue
	for (int i = 0; i < m_RenderQueue.Size(); i++)
	{
		WMatrix4 transformMatrix;

		// Build the transform matrix
		transformMatrix.BuildTransform(WVector3(m_RenderQueue[i]->GetWorldLocation().x, m_RenderQueue[i]->GetWorldLocation().y, 1),
			WVector3(0.0, 0.0, m_RenderQueue[i]->GetRotation()),
			WVector3(60, 30, 10));
		
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

		/*
		// Set the active texture and bind it
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (m_RenderQueue[i]->GetCurrentTexture())->GetTextureHandle());

		// Set the texture in the pixel shader to use the data from the first texture unit.
		location = glGetUniformLocation(m_ShaderProgram, "shaderTexture");
		if (location == -1)
		{
			return;
		}
		glUniform1i(location, 0);

		*/

		// Draw the sprite
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	// Clean the render queue
	m_RenderQueue.Zero();
}

void FSpriteShader::AddObject(void* _objectPtr)
{
	// Cast the object
	FSprite* sprite = (FSprite*)_objectPtr;

	// Add it to the render queue
	m_RenderQueue.Add(sprite);
}