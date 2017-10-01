////////////////////////////////////////////////////////////////////////////////
// Filename: FShaderBase.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FShaderBase_H_
#define _FShaderBase_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include <fstream>
#include "FGraphic.h"
#include "..\Containers\Array\TArray.h"

// We know the camera class
class FCamera;

/////////////
// DEFINES //
/////////////



////////////////////////////////////////////////////////////////////////////////
// Class name: FShaderBase
////////////////////////////////////////////////////////////////////////////////
class FShaderBase
{
protected:

	// The type of shader
	enum ShaderType
	{
		Deferred,
		Normal
	};

	// The type of shader
	ShaderType m_ShaderType;

public:
	FShaderBase(ShaderType _shaderType);
	FShaderBase(const FShaderBase&);
	~FShaderBase();

	// Initialize the shader
	virtual bool Initialize() = 0;

	// Render all objects inside this shader
	virtual void Render(float _elapsedTime, FCamera* _camera, FGraphic* _graphicContext) = 0;

	// Shutdown this shader
	virtual void Shutdown();

	// Add a object to be rendered
	virtual void AddObject(void* _objectPtr) = 0;

	// Return the shader type
	ShaderType GetShaderType()
	{
		return m_ShaderType;
	}

protected:

	// Load a shader source file
	bool CreateShaderFromFile(char* _shaderPath, unsigned int _shaderType, unsigned int& _shader);

	// Output the error messages
	void OutputShaderErrorMessage(unsigned int _shader, char* _filename);
	void OutputLinkerErrorMessage(unsigned int _shaderProgram);

public:

	////////////
	// GLOBAL //
	////////////

	// Return a shader by type
	template <typename ShaderClass>
	static FShaderBase* GetShader()
	{
		static FShaderBase* shader = nullptr;

		// Check if the shader already exist
		if (shader == nullptr)
		{
			// Create the shader
			shader = new ShaderClass;

			// Initialize the shader
			if (!shader->Initialize())
			{
				// ERROR //

				// Delete the shader object
				delete shader;

				// Set a null ptr for the shader
				return shader = nullptr;
			}
		}

		return shader;
	}

	// <GLOBAL> Register an shader inside the global array
	static void RegisterShader(FShaderBase* _shader)
	{
		// Check the shader type
		if (_shader->GetShaderType() == ShaderType::Deferred)
		{
			m_ShaderDeferredArray.Add(_shader);
		}
		else if (_shader->GetShaderType() == ShaderType::Normal)
		{
			m_ShaderArray.Add(_shader);
		}
	}

	// <GLOBAL> Render all shaders inside the global array
	static void RenderDeferredShaders(float _time, FCamera* _camera, FGraphic* _graphicContext);

	// <GLOBAL> Render all shaders who does not participate the deferred rendering
	static void RenderShaders(float _time, FCamera* _camera, FGraphic* _graphicContext);

	// <GLOBAL> Return a reference to the shader array
	static TArray<FShaderBase*>* GetEntitiesReference()
	{
		return &m_ShaderArray;
	}

protected:

	// The vertex and pixel shaders
	unsigned int m_VertexShader;
	unsigned int m_FragmentShader;

	// The shader program
	unsigned int m_ShaderProgram;

private:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> The global deferred shader array
	static TArray<FShaderBase*> m_ShaderDeferredArray;

	// <GLOBAL> The global shader array
	static TArray<FShaderBase*> m_ShaderArray;
};

#endif
