///////////////////////////////////////////////////////////////////////////////
// Filename: FNormalShip.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FNormalShip.h"
#include "..\..\..\Core\Renderable\IRenderable.h"
#include "..\..\..\Core\Renderable\Flipbook\FFlipbookShader.h"
#include "..\..\..\Core\Video\FShaderBase.h"
#include "..\Special Effects\Dust\FDust.h"
#include "..\Special Effects\Foam\FFoam.h"
#include "..\Special Effects\Trace\FTrace.h"

FNormalShip::FNormalShip()
{
	// Set the initial data
	m_LastSmokePosition = WVector2(0, 0);
	m_LastTracePosition = WVector2(0, 0);
	m_LastFoamTime = 0;

	// Create the flipbook
	FFlipbook* shipFlipbook = IRenderable::Create<FFlipbook>(this, FShaderBase::GetShader<FFlipbookShader>());
	
	// Set the flipbook data
	shipFlipbook->AddTexture(IResource::GetResourceByName<FTexture>(FHashedString("ship.tga")));
	shipFlipbook->SetAnimationTime(1.00);

	SetFlipbook(shipFlipbook);
}

FNormalShip::FNormalShip(const FNormalShip& other)
{
}

FNormalShip::~FNormalShip()
{
}

// Update this ship
void FNormalShip::Update(float _time)
{
	// Call the base update
	FShip::Update(_time);

	// Increment the foam time
	m_LastFoamTime += _time;

	// Get the distance from the last smoke position
	float smokeDistance = sqrt(pow(m_LastSmokePosition.x - GetLocation().x, 2) + pow(m_LastSmokePosition.y - GetLocation().y, 2));
	
	// Get the distance from the last water trace position
	float traceDistance = sqrt(pow(m_LastTracePosition.x - GetLocation().x, 2) + pow(m_LastTracePosition.y - GetLocation().y, 2));

	// Check if the distance if enough
	if (smokeDistance >= 4)
	{
		// Create a smoke
		FDust* dust = FDust::Create<FDust>();

		// m_Ship->LoadSprite("dummy");
		dust->SetLocation(WVector2::PolarCoordinateWithOffset(GetLocation(), GetRotation().z, -30));
		dust->SetDepthPlane(DepthPlane::Air2);
		dust->SetCollisionFlags(0);

		// Set the new smoke location
		m_LastSmokePosition = GetLocation();
	}

	// Check if we should create a water trace
	if (traceDistance >= 12)
	{
		// Create a water trace
		FTrace* waterTrace = FTrace::Create<FTrace>();

		// m_Ship->LoadSprite("dummy");
		waterTrace->SetLocation(WVector2::PolarCoordinateWithOffset(GetLocation(), GetRotation().z, -55));
		waterTrace->SetDepthPlane(DepthPlane::Onwater);
		waterTrace->SetCollisionFlags(0);

		// Set the new foam location
		m_LastTracePosition = GetLocation();
	}

	// Check if we should create a foam
	if (m_LastFoamTime >= FoamTime)
	{
		// Create a foam
		FFoam* foam = FFoam::Create<FFoam>();

		// m_Ship->LoadSprite("dummy");
		foam->SetLocation(WVector2::PolarCoordinateWithOffset(GetLocation(), GetRotation().z, (rand() % 120) - 60));
		foam->SetDepthPlane(DepthPlane::Onwater);
		foam->SetCollisionFlags(0);

		// Zero the foam time
		m_LastFoamTime = 0;
	}
}