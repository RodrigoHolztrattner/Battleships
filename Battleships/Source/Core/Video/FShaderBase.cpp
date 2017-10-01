///////////////////////////////////////////////////////////////////////////////
// Filename: FShaderBase.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FShaderBase.h"
#include <Windows.h>

// Namespace std (just for cpp)
using namespace std;

FShaderBase::FShaderBase(ShaderType _shaderType)
{
	// Set the shader type
	m_ShaderType = _shaderType;

	// Register this shader
	RegisterShader(this);

	// Set the initial data
	m_FragmentShader = -1;
	m_VertexShader = -1;
	m_ShaderProgram = -1;
}

FShaderBase::FShaderBase(const FShaderBase& other)
{
}

FShaderBase::~FShaderBase()
{
}

bool FShaderBase::CreateShaderFromFile(char* _shaderPath, unsigned int _shaderType, unsigned int& _shader)
{
	ifstream fin;
	int fileSize;
	char input;
	char* buffer;

	// Open the shader source file.
	fin.open(_shaderPath);
	
	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}

	// Initialize the size of the file.
	fileSize = 0;

	// Read the first element of the file.
	fin.get(input);

	// Count the number of elements in the text file.
	while (!fin.eof())
	{
		fileSize++;
		fin.get(input);
	}

	// Close the file for now.
	fin.close();

	// Initialize the buffer to read the shader source file into.
	buffer = new char[fileSize + 1];
	if (!buffer)
	{
		return false;
	}

	// Open the shader source file again.
	fin.open(_shaderPath);

	// Read the shader text file into the buffer as a block.
	fin.read(buffer, fileSize);

	// Close the file.
	fin.close();

	// Null terminate the buffer.
	buffer[fileSize] = '\0';

	// Create the shader
	_shader = glCreateShader(_shaderType);

	// Copy the shader source code strings into the shader
	glShaderSource(_shader, 1, &buffer, NULL);

	// Release the temporary buffer
	delete[] buffer;
	buffer = 0;

	// Compile the shader
	glCompileShader(_shader);

	// Check the shader status
	int status;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		// Output a shader error
		OutputShaderErrorMessage(_shader, _shaderPath);

		return false;
	}

	return true;
}

void FShaderBase::Shutdown()
{
	// Detach the vertex and fragment shaders from the program.
	glDetachShader(m_ShaderProgram, m_VertexShader);
	glDetachShader(m_ShaderProgram, m_FragmentShader);

	// Delete the vertex and fragment shaders.
	glDeleteShader(m_VertexShader);
	glDeleteShader(m_FragmentShader);

	// Delete the shader program.
	glDeleteProgram(m_ShaderProgram);
}

void FShaderBase::OutputShaderErrorMessage(unsigned int _shader, char* _filename)
{
	int logSize, i;
	char* infoLog;
	ofstream fout;
	wchar_t newString[512];
	unsigned int error, convertedChars;


	// Get the size of the string containing the information log for the failed shader compilation message.
	glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	// Create a char buffer to hold the info log.
	infoLog = new char[logSize];
	if (!infoLog)
	{
		return;
	}

	// Now retrieve the info log.
	glGetShaderInfoLog(_shader, logSize, NULL, infoLog);

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i<logSize; i++)
	{
		fout << infoLog[i];
	}

	// Close the file.
	fout.close();

	// Convert the shader filename to a wide character string.
	error = mbstowcs_s(&convertedChars, newString, 512, _filename, 512);
	if (error != 0)
	{
		return;
	}

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(GetActiveWindow(), L"Error compiling shader.  Check shader-error.txt for message.", newString, MB_OK);

	return;
}

void FShaderBase::OutputLinkerErrorMessage(unsigned int _shaderProgram)
{
	int logSize, i;
	char* infoLog;
	ofstream fout;


	// Get the size of the string containing the information log for the failed shader compilation message.
	glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	// Create a char buffer to hold the info log.
	infoLog = new char[logSize];
	if (!infoLog)
	{
		return;
	}

	// Now retrieve the info log.
	glGetProgramInfoLog(_shaderProgram, logSize, NULL, infoLog);

	// Open a file to write the error message to.
	fout.open("linker-error.txt");

	// Write out the error message.
	for (i = 0; i<logSize; i++)
	{
		fout << infoLog[i];
	}

	// Close the file.
	fout.close();
	
	// Pop a message up on the screen to notify the user to check the text file for linker errors.
	MessageBox(GetActiveWindow(), L"Error compiling linker.  Check linker-error.txt for message.", L"Linker Error", MB_OK);

	return;
}

////////////
// GLOBAL //
////////////

// <GLOBAL> The global shader array
TArray<FShaderBase*> FShaderBase::m_ShaderDeferredArray;
TArray<FShaderBase*> FShaderBase::m_ShaderArray;

void FShaderBase::RenderDeferredShaders(float _time, FCamera* _camera, FGraphic* _graphicContext)
{
	// For each shader
	for (int i = 0; i < m_ShaderDeferredArray.Size(); i++)
	{
		// Render all objects inside this shader
		m_ShaderDeferredArray[i]->Render(_time, _camera, _graphicContext);
	}
}

void FShaderBase::RenderShaders(float _time, FCamera* _camera, FGraphic* _graphicContext)
{
	// For each shader
	for (int i = 0; i < m_ShaderArray.Size(); i++)
	{
		// Render all objects inside this shader
		m_ShaderArray[i]->Render(_time, _camera, _graphicContext);
	}
}