///////////////////////////////////////////////////////////////////////////////
// Filename: FShip.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FShip.h"
#include "..\..\..\Core\Renderable\Flipbook\FFlipbook.h"
#include "..\Light\FSpotLight.h"
#include "..\Light\FPointLight.h"

FShip::FShip()
{
	// Set the initial data
	m_CurrentAcceleration = 0;
	m_ExpectedAcceleration = 0;
	m_MaximumAcceleration = 0;
	m_CurrentTurnDirection = 0;
	m_ExpectedTurnDirection = 0;
	m_LightStatus = false;

	// Create the ship lantern light
	m_LanternLight = FSpotLight::Create<FSpotLight>(this);
	m_LanternLight->SetCollisionFlags(0);

	// Create the ship headlight
	m_Headlight = FPointLight::Create<FPointLight>(this);
	m_Headlight->SetSize(WVector3(HeadlightLightSize, HeadlightLightSize, 1));
	m_Headlight->SetCollisionFlags(0);

	// Set the light
	Light();

	// Promote this actor (allow collision check and picks)
	Promote();
}

FShip::FShip(const FShip& other)
{
}

FShip::~FShip()
{
}

void FShip::ChangeTurnDirection(float _amount)
{
	// Change the turn direction
	m_ExpectedTurnDirection = _amount;
}

void FShip::ChanceAcceleration(float _amount, float _maximumAcceleration)
{
	// Change the acceleration
	m_ExpectedAcceleration += _amount;

	// Check if we are changing the maximum acceleration
	if (_maximumAcceleration != 0)
	{
		m_MaximumAcceleration = _maximumAcceleration;
	}

	// Check if we dont overlap
	if (m_ExpectedAcceleration > m_MaximumAcceleration)
	{
		m_ExpectedAcceleration = m_MaximumAcceleration;
	}
	else if (abs(m_ExpectedAcceleration) > m_MaximumAcceleration)
	{
		m_ExpectedAcceleration = -m_MaximumAcceleration;
	}
}

void FShip::Update(float _time)
{
	// Change the turn direction
	if (m_ExpectedTurnDirection - m_CurrentTurnDirection >= 0.1)
	{
		m_CurrentTurnDirection += 100 * _time;
	}
	else if (m_ExpectedTurnDirection - m_CurrentTurnDirection <= -0.1)
	{
		m_CurrentTurnDirection -= 100 * _time;
	}
	else
	{
		m_CurrentTurnDirection = m_ExpectedTurnDirection;
	}

	// Set the new rotation
	SetRotation(WVector3(GetRotation().x, GetRotation().y, GetRotation().z + m_CurrentTurnDirection * _time));

	// Change the current acceleration
	if (m_ExpectedAcceleration - m_CurrentAcceleration >= 5)
	{
		m_CurrentAcceleration += 60 * _time;
	}
	else if (m_ExpectedAcceleration - m_CurrentAcceleration <= -5)
	{
		m_CurrentAcceleration -= 60 * _time;
	}
	else
	{
		m_CurrentAcceleration = m_ExpectedAcceleration;
	}
	
	// Calc the new position
	WVector2 currentLocation = GetLocation();
	currentLocation.x += m_CurrentAcceleration * cos(GetRotation().z / 180.0 * 3.14159265359) * _time;
	currentLocation.y += m_CurrentAcceleration * sin(GetRotation().z / 180.0 * 3.14159265359) * _time;
	SetLocation(currentLocation);

	///////////
	// LIGHT //
	///////////

	// Set the lantern light position
	m_LanternLight->SetLocation(GetLocation());
	m_LanternLight->SetLocation(WVector2::PolarCoordinateWithOffset(GetLocation(), GetRotation().z, LanternLightSize / 2 + 45));

	// Set the rotation
	m_LanternLight->SetRotation(GetRotation());

	// Set the headlight position
	m_Headlight->SetLocation(WVector2(GetLocation().x, GetLocation().y));
}

void FShip::Light()
{
	// Set the new light status
	m_LightStatus = !m_LightStatus;
	if (m_LightStatus)
	{
		m_LanternLight->SetSize(WVector3(LanternLightSize, LanternLightSize, 1));
	}
	else
	{
		m_LanternLight->SetSize(WVector3(0, 0, 1));
	}
}

void FShip::SetFlipbook(FFlipbook* _flipbook)
{
	FActor::SetRenderable(_flipbook);
}