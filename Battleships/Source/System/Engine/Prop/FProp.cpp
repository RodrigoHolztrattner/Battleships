///////////////////////////////////////////////////////////////////////////////
// Filename: FProp.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FProp.h"
#include "..\..\..\Core\Renderable\Flipbook\FFlipbook.h"

FProp::FProp()
{
	// Promote this actor (allow collision check and picks)
	Promote();
}

FProp::FProp(const FProp& other)
{
}

FProp::~FProp()
{
}

void FProp::SetFlipbook(FFlipbook* _flipbook)
{
	FActor::SetRenderable(_flipbook);
}