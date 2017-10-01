////////////////////////////////////////////////////////////////////////////////
// Filename: FSpotLight.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FSpotLight_H_
#define _FSpotLight_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\..\Core\Entity\Actor\FActor.h"

// Say that the FLight class exist
class FLight;

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FSpotLight
////////////////////////////////////////////////////////////////////////////////
class FSpotLight : public FActor
{
private:

	// Actor is a friend class
	friend FActor;
	friend IEntity;

public:

	// Set the light color
	void SetColor(WVector3 _color);

protected:

	// Constructor and destructor are private and we can only share ptrs (copy-constructor is private too)
	FSpotLight();
	FSpotLight(const FSpotLight&);
	~FSpotLight();

	// Update this ship
	virtual void Update(float _time);

	// Set the light
	void SetLight(FLight* _light);

	// Return if we should keep track of this (if false, no pick or collision functions will have effect on this object)
	bool ShouldKeepTrack(){ return false; };

private:

	// The light
	FLight* m_Light;

};

#endif
