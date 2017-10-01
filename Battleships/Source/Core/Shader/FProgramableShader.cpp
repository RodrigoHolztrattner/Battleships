///////////////////////////////////////////////////////////////////////////////
// Filename: FProgramableShader.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FProgramableShader.h"

FProgramableShader::FProgramableShader()
{
	// Set the initial data
	m_VariableIndex = 0;
}

FProgramableShader::FProgramableShader(const FProgramableShader& other)
{
}

FProgramableShader::~FProgramableShader()
{
}

unsigned int FProgramableShader::GetFreeVariableIndex()
{
	// Increment the index
	m_VariableIndex++;

	return m_VariableIndex - 1;
}

void FProgramableShader::OutputStream(std::ostringstream* _stream)
{
	std::cout << _stream->str() << std::endl;
}

////////////
// GLOBAL //
////////////

// Declare the current shader variable
FProgramableShader* FProgramableShader::m_CurrentShader = nullptr;

FProgramableShader* FProgramableShader::GetCurrentShaderReference()
{
	return m_CurrentShader;
}

void FProgramableShader::SetCurrentShader(FProgramableShader* _currentShader)
{
	m_CurrentShader = _currentShader;
}