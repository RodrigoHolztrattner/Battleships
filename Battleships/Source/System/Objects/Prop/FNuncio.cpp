///////////////////////////////////////////////////////////////////////////////
// Filename: FNuncio.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FNuncio.h"
#include "..\..\Engine\Light\FSpotLight.h"
#include "..\..\Engine\Light\FPointLight.h"
#include "..\..\..\Core\Renderable\Flipbook\FFlipbook.h"
#include "..\..\..\Core\Renderable\Flipbook\FFlipbookShader.h"

FNuncio::FNuncio()
{
	// Create the flipbook
	FFlipbook* lighthouseFlipbook = IRenderable::Create<FFlipbook>(this, FShaderBase::GetShader<FFlipbookShader>());

	// Set the flipbook data
	lighthouseFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("Nuncio.tga")));
	lighthouseFlipbook->SetAnimationTime(1.00);
	SetFlipbook(lighthouseFlipbook);
}

FNuncio::FNuncio(const FNuncio& other)
{
}

FNuncio::~FNuncio()
{
}


void FNuncio::Update(float _time)
{
}