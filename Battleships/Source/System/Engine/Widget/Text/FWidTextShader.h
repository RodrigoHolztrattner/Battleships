////////////////////////////////////////////////////////////////////////////////
// Filename: FWidTextShader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FWidTextShader_H_
#define _FWidTextShader_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\Core\Containers\Array\TArray.h"
#include "..\..\..\..\Core\Support\Math\WMath.h"
#include "..\..\..\..\Core\Video\FShaderBase.h" // Includes the opengl files
#include "FWidText.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FWidTextShader
////////////////////////////////////////////////////////////////////////////////
class FWidTextShader : public FShaderBase
{
private:

public:
	FWidTextShader();
	FWidTextShader(const FWidTextShader&);
	~FWidTextShader();

	// Initialize the shader
	virtual bool Initialize();

	// Render all objects inside this shader
	virtual void Render(float _elapsedTime, FCamera* _camera, FGraphic* _graphicContext);

	// Add a object to be rendered
	virtual void AddObject(void* _objectPtr);

private:

	// Create the view mesh
	void CreateViewMesh();

private:

	// The render queue
	TArray<FWidText*> m_RenderQueue;

	// The mesh data
	unsigned int m_VertexArrayId;
	unsigned int m_VertexBufferId;
	unsigned int m_IndexBufferId;
};

#endif
