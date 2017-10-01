////////////////////////////////////////////////////////////////////////////////
// Filename: FLightShader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FLightShader_H_
#define _FLightShader_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Containers\Array\TArray.h"
#include "..\..\Support\Math\WMath.h"
#include "..\..\Video\FShaderBase.h" // Includes the opengl files
#include "FLight.h"
#include <map>

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FLightShader
////////////////////////////////////////////////////////////////////////////////
class FLightShader : public FShaderBase
{
private:

public:
	FLightShader();
	FLightShader(const FLightShader&);
	~FLightShader();

	// Initialize the shader
	virtual bool Initialize();

	// Render all objects inside this shader
	virtual void Render(float _elapsedTime, FCamera* _camera, FGraphic* _graphicContext);

	// Add a object to be rendered
	virtual void AddObject(void* _objectPtr);

private:

	// Create the light mesh
	void CreateLightMesh();

private:

	// The render queue
	std::multimap<int, FLight*, std::greater<int> > m_RenderQueue;

	// The mesh data
	unsigned int m_VertexArrayId;
	unsigned int m_VertexBufferId;
	unsigned int m_IndexBufferId;
};

#endif
