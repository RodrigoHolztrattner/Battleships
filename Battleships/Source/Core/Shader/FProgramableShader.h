////////////////////////////////////////////////////////////////////////////////
// Filename: FProgramableShader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FProgramableShader_H_
#define _FProgramableShader_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include <sstream>
#include <string>
#include <iostream>

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FProgramableShader
////////////////////////////////////////////////////////////////////////////////
class FProgramableShader
{
private:

public:
	FProgramableShader();
	FProgramableShader(const FProgramableShader&);
	~FProgramableShader();

	// Output a stream of data from a intrinsic
	void OutputStream(std::ostringstream* _stream);

	// Call a new index for a new variable name
	unsigned int GetFreeVariableIndex();

private:

	// The counter for new variable indexes
	unsigned int m_VariableIndex;

public:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> Return a reference to the shader that are being build
	static FProgramableShader* GetCurrentShaderReference();

	// <GLOBAL> Set the current shader
	static void SetCurrentShader(FProgramableShader* _currentShader);

private:

	////////////
	// GLOBAL //
	////////////

	// The current shader that are being build
	static FProgramableShader* m_CurrentShader;
};

#endif
