///////////////////////////////////////////////////////////////////////////////
// Filename: FLighthouse.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FLighthouse.h"
#include "..\..\Engine\Light\FSpotLight.h"
#include "..\..\Engine\Light\FPointLight.h"
#include "..\..\..\Core\Renderable\Flipbook\FFlipbook.h"
#include "..\..\..\Core\Renderable\Flipbook\FFlipbookShader.h"

FLighthouse::FLighthouse()
{
	// Create the light
	m_Light = FSpotLight::Create<FSpotLight>(this);
	m_Light->SetRotation(WVector3(0, 0, 0));
	m_Light->SetSize(WVector3(1600, 400, 1));
	m_Light->SetColor(WVector3(1.0, 1.0, 1.0));
	m_Light->SetCollisionFlags(0);

	// Create the flipbook
	FFlipbook* lighthouseFlipbook = IRenderable::Create<FFlipbook>(this, FShaderBase::GetShader<FFlipbookShader>());

	// Set the flipbook data
	lighthouseFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("lighthouse.tga")));
	lighthouseFlipbook->SetAnimationTime(1.00);
	lighthouseFlipbook->CollisionStatus(true);
	SetFlipbook(lighthouseFlipbook);

	// Create the ship headlight
	m_SelfLight = FPointLight::Create<FPointLight>(this);
	m_SelfLight->SetSize(WVector3(300, 300, 1));
	m_SelfLight->SetCollisionFlags(0);
}

FLighthouse::FLighthouse(const FLighthouse& other)
{
}

FLighthouse::~FLighthouse()
{
}


void FLighthouse::Update(float _time)
{
	// Set the rotation and position for all lights
	m_Light->SetRotation(WVector3(0, 0, m_Light->GetRotation().z + _time * 10.0f));
	m_Light->SetLocation(WVector2::PolarCoordinateWithOffset(GetLocation(), m_Light->GetRotation().z, m_Light->GetSize().x/2.0f + 20));
	m_SelfLight->SetLocation(GetLocation());
}