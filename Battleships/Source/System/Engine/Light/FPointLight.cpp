///////////////////////////////////////////////////////////////////////////////
// Filename: FPointLight.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FPointLight.h"
#include "..\..\..\Core\Renderable\Light\FLight.h"
#include "..\..\..\Core\Renderable\Light\FLightShader.h"

FPointLight::FPointLight()
{
	// Create the light
	FLight* light = IRenderable::Create<FLight>(this, FShaderBase::GetShader<FLightShader>());

	// Set the flipbook data
	light->SetTexture(IResource::GetResourceByName<FTexture>(FHashedString("RadialBasic.tga")));
	SetLight(light);
}

FPointLight::FPointLight(const FPointLight& other)
{
}

FPointLight::~FPointLight()
{
}

void FPointLight::Update(float _time)
{
}

void FPointLight::SetLight(FLight* _light)
{
	FActor::SetRenderable(_light);
}