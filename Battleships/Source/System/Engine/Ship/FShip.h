////////////////////////////////////////////////////////////////////////////////
// Filename: FShip.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FShip_H_
#define _FShip_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\..\Core\Entity\Actor\FActor.h"

// Say that the Flipbook class exist
class FFlipbook;

// We know the spot light and the point light classes
class FSpotLight;
class FPointLight;

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FShip
////////////////////////////////////////////////////////////////////////////////
class FShip : public FActor
{
private:

	// Actor is a friend class
	friend FActor;

	// The lantern and headlight light sizes
	static const unsigned int LanternLightSize = 600;
	static const unsigned int HeadlightLightSize = 150;

public:

	// Change the acceleration
	void ChanceAcceleration(float _amount, float _maximumAcceleration = 0);

	// Return the current acceleration
	float GetAcceleration()
	{
		return m_CurrentAcceleration;
	}

	// Change the turn direction
	void ChangeTurnDirection(float _amount);

	// Change the light status
	void Light();

protected:

	// Constructor and destructor are private and we can only share ptrs (copy-constructor is private too)
	FShip();
	FShip(const FShip&);
	virtual ~FShip();

	// Update this ship
	virtual void Update(float _time);

	// Set the ship flipbook
	void SetFlipbook(FFlipbook* _flipbook);

	// Return if we should keep track of this (if false, no pick or collision functions will have effect on this object)
	bool ShouldKeepTrack(){ return true; };

private:

	// The current and expected turn direction
	float m_CurrentTurnDirection;
	float m_ExpectedTurnDirection;

	// The current (this will move out ship into the facing direction) and maximum accelerations
	float m_CurrentAcceleration;
	float m_ExpectedAcceleration;
	float m_MaximumAcceleration;

	// The lantern light and the light status
	FSpotLight* m_LanternLight;
	bool m_LightStatus;

	// The headlight
	FPointLight* m_Headlight;
};

#endif
