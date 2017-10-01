////////////////////////////////////////////////////////////////////////////////
// Filename: FNormalShip.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FNormalShip_H_
#define _FNormalShip_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Engine\Ship\FShip.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FNormalShip
////////////////////////////////////////////////////////////////////////////////
class FNormalShip : public FShip
{
private:

	// The time that we should create a foam
	const float FoamTime = 0.2f;

	// Ship and Entity are friend classes
	friend FShip;
	friend IEntity;

public:

	// Update this ship
	virtual void Update(float _time);

protected:

	// Constructor and destructor are private and we can only share ptrs (copy-constructor is private too)
	FNormalShip();
	FNormalShip(const FNormalShip&);
	~FNormalShip();

private:

	// The last time that we created a foam
	float m_LastFoamTime;

	// The last position that we created an smoke effect
	WVector2 m_LastSmokePosition;

	// The last position that we created an water trace effect
	WVector2 m_LastTracePosition;
};

#endif
