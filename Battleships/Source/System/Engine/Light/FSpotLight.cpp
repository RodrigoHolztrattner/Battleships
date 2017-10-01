///////////////////////////////////////////////////////////////////////////////
// Filename: FSpotLight.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FSpotLight.h"
#include "..\..\..\Core\Renderable\Light\FLight.h"
#include "..\..\..\Core\Renderable\Light\FLightShader.h"

FSpotLight::FSpotLight()
{
	// Create the light
	m_Light = IRenderable::Create<FLight>(this, FShaderBase::GetShader<FLightShader>());

	// Set the flipbook data
	m_Light->SetTexture(IResource::GetResourceByName<FTexture>(FHashedString("lightCone.tga")));
	SetLight(m_Light);
}

FSpotLight::FSpotLight(const FSpotLight& other)
{
}

FSpotLight::~FSpotLight()
{
}

void FSpotLight::SetColor(WVector3 _color)
{
	m_Light->SetColor(_color);
}

void FSpotLight::Update(float _time)
{
}

void FSpotLight::SetLight(FLight* _light)
{
	FActor::SetRenderable(_light);
}