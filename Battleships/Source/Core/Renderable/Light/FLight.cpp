///////////////////////////////////////////////////////////////////////////////
// Filename: FLight.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FLight.h"
#include "..\..\Entity\Actor\FActor.h"

FLight::FLight(FActor* _owner, FShaderBase* _shader) : IRenderable(_owner, _shader)
{
	// Set the initial data
	m_Alpha = 1.0f;
	m_Color = WVector3(1, 1, 1);
}

FLight::FLight(const FLight& other) : IRenderable(other)
{
}

FLight::~FLight()
{
}

void FLight::Release()
{
	// Call the base release
	IRenderable::Release();

	// Release the texture
	m_Texture->Release();
}

void FLight::SetTexture(FTexture* _texture)
{
	// Set the new texture
	m_Texture = _texture;
}

void FLight::Update(float _time)
{
}

FTexture* FLight::Texture()
{
	return m_Texture;
}