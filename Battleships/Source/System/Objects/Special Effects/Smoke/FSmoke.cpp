///////////////////////////////////////////////////////////////////////////////
// Filename: FSmoke.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FSmoke.h"
#include "..\..\..\Core\Renderable\Flipbook\FFlipbook.h"
#include "..\..\..\..\Core\Video\FShaderBase.h"
#include "..\..\..\..\Core\Renderable\Flipbook\FFlipbookShader.h"

FSmoke::FSmoke()
{
	// Create the smoke flipbook
	FFlipbook* smokeFlipbook = IRenderable::Create<FFlipbook>(this, FShaderBase::GetShader<FFlipbookShader>());

	// Set the flipbook data
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke0.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke1.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke2.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke3.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke4.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke5.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke6.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke7.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke8.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke9.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke10.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke11.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke12.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke13.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke14.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke15.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke16.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke17.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke18.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke19.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke20.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke21.tga")));
	smokeFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("smoke22.tga")));
	smokeFlipbook->SetAnimationTime(1.50);

	FActor::SetRenderable(smokeFlipbook);

	// No collision
	SetCollisionFlags(0);
}

FSmoke::FSmoke(const FSmoke& other)
{
}

FSmoke::~FSmoke()
{
}

void FSmoke::Update(float _time)
{
}

void FSmoke::RenderableAnimationExpired(IRenderable* _who)
{
	// Release this actor
	Release();
}