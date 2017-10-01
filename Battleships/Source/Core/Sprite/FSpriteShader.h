////////////////////////////////////////////////////////////////////////////////
// Filename: FSpriteShader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FSpriteShader_H_
#define _FSpriteShader_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Containers\Array\TArray.h"
#include "..\Support\Math\WMath.h"
#include "..\Video\FShaderBase.h" // Includes the opengl files
#include "FSprite.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FSpriteShader
////////////////////////////////////////////////////////////////////////////////
class FSpriteShader : public FShaderBase
{
private:

public:
	FSpriteShader();
	FSpriteShader(const FSpriteShader&);
	~FSpriteShader();

	// Initialize the shader
	virtual bool Initialize();

	// Render all objects inside this shader
	virtual void Render();

	// Add a object to be rendered
	virtual void AddObject(void* _objectPtr);

private:

	// Create the sprite mesh
	void CreateSpriteMesh();

private:

	// The render queue
	TArray<FSprite*> m_RenderQueue;

	// The mesh data
	unsigned int m_VertexArrayId;
	unsigned int m_VertexBufferId;
	unsigned int m_IndexBufferId;
};

#endif
