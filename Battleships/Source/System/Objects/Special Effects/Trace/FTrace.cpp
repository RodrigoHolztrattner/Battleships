///////////////////////////////////////////////////////////////////////////////
// Filename: FTrace.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FTrace.h"
#include "..\..\..\Core\Renderable\Flipbook\FFlipbook.h"
#include "..\..\..\..\Core\Video\FShaderBase.h"
#include "..\..\..\..\Core\Renderable\Flipbook\FFlipbookShader.h"

FTrace::FTrace()
{
	///////////////////
	// CONFIGURATION //
	///////////////////

	// Calc the maximum expiration time
	m_MaximumExpirationTime = RandomFloat(MinimumExpirationTime, MaximumExpirationTime);

	// Set the current expiration time
	m_CurrentExpirationTime = m_MaximumExpirationTime;

	// Get a random initial size
	m_InitialSize = WVector2(RandomFloat(MinimumSize, MaximumSize), RandomFloat(MinimumSize, MaximumSize));

	// Set the initial size
	SetSize(WVector3(m_InitialSize.x, m_InitialSize.y, 1));

	// Set a random rotation
	SetRotation(WVector3(0, 0, rand() / 100.0f));

	//////////////
	// FLIPBOOK //
	//////////////

	// Create the smoke flipbook
	m_DustFlipbook = IRenderable::Create<FFlipbook>(this, FShaderBase::GetShader<FFlipbookShader>());

	// Set the flipbook data
	m_DustFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("waterTrace.tga")));
	m_DustFlipbook->SetAnimationTime(m_MaximumExpirationTime);

	FActor::SetRenderable(m_DustFlipbook);

	// No collision
	SetCollisionFlags(0);
}

FTrace::FTrace(const FTrace& other)
{
}

FTrace::~FTrace()
{
}

void FTrace::Update(float _time)
{
	// Decrement the time
	m_CurrentExpirationTime -= _time;

	// Set the flipbook alpha
	m_DustFlipbook->SetAlpha(m_CurrentExpirationTime / m_MaximumExpirationTime * 0.15f);
	m_DustFlipbook->SetColor(WVector3(1, 1, 1));

	// Set the size
	float sizeFactor = (1.0 - (m_CurrentExpirationTime / m_MaximumExpirationTime));
	SetSize(WVector3(m_InitialSize.x + GrowSize * sizeFactor, m_InitialSize.y + GrowSize * sizeFactor, 1));

	// Check if the time is over
	if (m_CurrentExpirationTime <= 0)
	{
		// Release this actor
		Release();
	}
}
