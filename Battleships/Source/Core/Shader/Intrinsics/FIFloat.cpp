///////////////////////////////////////////////////////////////////////////////
// Filename: FIFloat.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FIFloat.h"
#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include "..\FProgramableShader.h"

FIFloat::FIFloat()
{
	// Call the creation string method
	CreationString();
}

FIFloat::FIFloat(const FIFloat& other)
{
}

FIFloat::~FIFloat()
{
}

void FIFloat::CreationString()
{
	std::ostringstream buffer;

	// Set the variable name
	sprintf(m_VariableName, "var%i", FProgramableShader::GetCurrentShaderReference()->GetFreeVariableIndex());

	// Set the buffer
	buffer << "float " << m_VariableName << ";";
	
	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);
}

FIFloat& FIFloat::operator=(float arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "=" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat& FIFloat::operator=(FIFloat arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "=" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator+(const float& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "+" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator+(const FIFloat& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "+" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator+=(const float& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "+=" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator+=(const FIFloat& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "+=" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator-(const float& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "-" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator-(const FIFloat& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "-" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator-=(const float& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "-=" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator-=(const FIFloat& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "-=" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator*(const float& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "*" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator*(const FIFloat& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "*" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator*=(const float& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "*=" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator*=(const FIFloat& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "*=" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator/(const float& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "/" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator/(const FIFloat& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "/" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator/=(const float& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "/=" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

FIFloat FIFloat::operator/=(const FIFloat& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "/=" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return *this;
}

bool FIFloat::operator< (const float& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "<" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return true;
}

bool FIFloat::operator> (const float& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << ">" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return true;
}
bool FIFloat::operator<=(const float& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "<=" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return true;
}
bool FIFloat::operator>=(const float& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << ">=" << arg << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return true;
}

bool FIFloat::operator< (const FIFloat& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "<" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return true;
}
bool FIFloat::operator> (const FIFloat& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << ">" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return true;
}
bool FIFloat::operator<=(const FIFloat& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << "<=" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return true;
}
bool FIFloat::operator>=(const FIFloat& arg)
{
	std::ostringstream buffer;

	// Set the buffer
	buffer << m_VariableName << ">=" << arg.m_VariableName << ";";

	// Output the stream
	FProgramableShader::GetCurrentShaderReference()->OutputStream(&buffer);

	return true;
}