////////////////////////////////////////////////////////////////////////////////
// Filename: FFlipbookShader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FFlipbookShader_H_
#define _FFlipbookShader_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Containers\Array\TArray.h"
#include "..\..\Support\Math\WMath.h"
#include "..\..\Video\FShaderBase.h" // Includes the opengl files
#include "FFlipbook.h"
#include <map>

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FFlipbookShader
////////////////////////////////////////////////////////////////////////////////
class FFlipbookShader : public FShaderBase
{
private:

public:
	FFlipbookShader();
	FFlipbookShader(const FFlipbookShader&);
	~FFlipbookShader();

	// Initialize the shader
	virtual bool Initialize();

	// Render all objects inside this shader
	virtual void Render(float _elapsedTime, FCamera* _camera, FGraphic* _graphicContext);

	// Add a object to be rendered
	virtual void AddObject(void* _objectPtr);

private:

	// Create the sprite mesh
	void CreateSpriteMesh();

private:

	// The render queue
	std::multimap<int, FFlipbook*, std::greater<int> > m_RenderQueue;

	// The mesh data
	unsigned int m_VertexArrayId;
	unsigned int m_VertexBufferId;
	unsigned int m_IndexBufferId;
};

#endif
