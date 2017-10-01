////////////////////////////////////////////////////////////////////////////////
// Filename: FWaterShader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FWaterShader_H_
#define _FWaterShader_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Containers\Array\TArray.h"
#include "..\..\Support\Math\WMath.h"
#include "..\..\Video\FShaderBase.h" // Includes the opengl files

/////////////
// DEFINES //
/////////////

// We know the texture class
class FTexture;

////////////////////////////////////////////////////////////////////////////////
// Class name: FWaterShader
////////////////////////////////////////////////////////////////////////////////
class FWaterShader : public FShaderBase
{
private:

public:
	FWaterShader();
	FWaterShader(const FWaterShader&);
	~FWaterShader();

	// Initialize the shader
	virtual bool Initialize();

	// Render all objects inside this shader
	virtual void Render(float _elapsedTime, FCamera* _camera, FGraphic* _graphicContext);

	// Add a object to be rendered
	virtual void AddObject(void* _objectPtr);

private:

	// Create the water mesh
	void CreateWaterMesh();

private:

	// The mesh data
	unsigned int m_VertexArrayId;
	unsigned int m_VertexBufferId;
	unsigned int m_IndexBufferId;

	// The water textures
	FTexture* m_WaterTileTextures[50];
	FTexture* m_DifuseWaterTexture;
	FTexture* m_WaveWaterTexture;
	FTexture* m_NormalWaterTexture;
	FTexture* m_BumpWaterTexture;

	// The bump water texture
	

	// The current time
	float m_CurrentTime;
};

#endif
